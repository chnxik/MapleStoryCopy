#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"

#include "CLevel.h"
#include "CActor.h"

#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlatform.h"

CCollisionMgr::CCollisionMgr()
    : m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::tick()
{
    for (UINT iRow = 0; iRow < (UINT)LAYER::END; ++iRow)
    {
        for (UINT iCol = iRow; iCol < (UINT)LAYER::END; ++iCol)
        {
            if (!(m_matrix[iRow] & (1 << iCol)))
                continue;

            // iRow 레이어와 iCol 레이어는 서로 충돌검사를 진행한다.
            CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
        }
    }
}

void CCollisionMgr::CollisionBtwLayer(LAYER _left, LAYER _right)
{
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

    const vector<CActor*>& vecLeft = pCurLevel->GetLayer(_left);
    const vector<CActor*>& vecRight = pCurLevel->GetLayer(_right);

    for (size_t i = 0; i < vecLeft.size(); ++i)
    {
        // 충돌체가 없는 경우
        if (nullptr == vecLeft[i]->GetCollider())
            continue;

        size_t j = 0;
        if (_left == _right) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
        {
            j = i;
        }

        for (; j < vecRight.size(); ++j)
        {
            CCollider* LCol = vecLeft[i]->GetCollider();
            CCollider* RCol = vecRight[j]->GetCollider();

            // 충돌체를 보유하고 있지 않거나, 충돌을 진행시킬 두 대상이 동일한 오브젝트인 경우
            if (nullptr == RCol || vecLeft[i] == vecRight[j])
                continue;

            if (_right == (LAYER)5)
                int a = 0;

            // 두 충돌체의 아이디를 조합
            CollisionID ID = {};
            ID.LeftID = LCol->GetID();
            ID.RightID = RCol->GetID();

            // 일반 Collision 충돌 이력 검사 iterator
            map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
            if (iter == m_mapPrevInfo.end())
            {
                m_mapPrevInfo.insert(make_pair(ID.id, false));
                iter = m_mapPrevInfo.find(ID.id);
            }

            // Platform 충돌 모니터링 iterator
            map<UINT_PTR, bool>::iterator MntrnIter = m_mapMntrn.find(ID.id); 
            if (MntrnIter == m_mapMntrn.end())
            {
                m_mapMntrn.insert(make_pair(ID.id, true));
                MntrnIter = m_mapMntrn.find(ID.id);
            }

            bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

            // =========================
            // === Platform 충돌 검사 ===
            // =========================

            if (_left == LAYER::PLATFORM)
            {
                CPlatform* pPlatform = dynamic_cast<CPlatform*>(LCol->GetOwner());  // 플랫폼 객체 포인터를 얻어온다.
                
                Vec2 vActPos  = RCol->GetGrndPt();  // 객체 GrndPos
                Vec2 vPStrt = pPlatform->GetLdot(); // 플랫폼 왼쪽
                Vec2 vPEnd = pPlatform->GetRdot();  // 플랫폼 오른쪽
                
                // 검사 대상이 Dead 상태인가
                if (!bDead)
                {
                    Vec2 vActVel = RCol->GetOwner()->GetRigidbody()->GetVelocity();
                    float fChckPos = GetVerticalPos(vActPos, vPStrt, pPlatform->GetGradient());

                    // 가로 범위 안에 있다.
                    if (vPStrt.x <= vActPos.x && vActPos.x <= vPEnd.x)
                    {

                        if (i == 8)
                            int a = 0;

                        // 이전 충돌상태
                        if (iter->second)
                        {
                            // 라인 충돌 범위 판정
                            if (CheckLineCollision(vActPos.y, fChckPos))
                            {
                                // 충돌중이다.
                                LCol->OnOverlap(RCol);
                                RCol->OnOverlap(LCol);
                            }
                            else
                            {
                                // 충돌에서 벗어났다.
                                LCol->EndOverlap(RCol);
                                RCol->EndOverlap(LCol);
                                iter->second = false;
                                MntrnIter->second = false;
                            }
                        }

                        // 이전 충돌상태 아니었다.
                        else
                        {
                            // 충돌주시상태다
                            if (MntrnIter->second)
                            {
                                Vec2 PlfGra = pPlatform->GetGradient();
                                short dbg = GetDegree(pPlatform->GetGradient(), vActVel);

                                if (dbg > 0)
                                    int a = 0;

                                // 객체 운동방향이 플랫폼을 향한다
                                if (0 >= GetDegree(pPlatform->GetGradient(),vActVel))
                                {
                                    // 라인 충돌 판정
                                    if (CheckLineCollision(vActPos.y, fChckPos))
                                    {
                                        iter->second = true;        // 이전 충돌 상태
                                        MntrnIter->second = false;  // 충돌 주시 해제
                                        LCol->BeginOverlap(RCol);   // 충돌 시작
                                        RCol->BeginOverlap(LCol);   // 충돌 시작
                                    }
                                }
                                else
                                {
                                    int a = 0;
                                }
                            }

                            // 충돌주시상태 아니다
                            else
                            {
                                // 충돌 주시 범위다
                                if (CheckMntrnTrgt(vActPos.y, fChckPos))
                                {
                                    MntrnIter->second = true;  // 충돌 주시 설정
                                    iter->second = false;
                                }
                            }
                        }
                    }

                    // 가로범위 안에 없다.
                    else
                    {
                        if (MntrnIter->second)
                            MntrnIter->second = false;

                        if (iter->second)
                        {
                            iter->second = false;
                            LCol->EndOverlap(RCol);
                            RCol->EndOverlap(LCol);
                        }
                    }
                }

                // 검사 대상이 Dead 상태이다.
                else
                {
                    if (MntrnIter->second)
                        MntrnIter->second = false;

                    if (iter->second)
                    {
                        iter->second = false;
                        LCol->EndOverlap(RCol);
                        RCol->EndOverlap(LCol);
                    }
                }
            }

            // ==================
            // === 충돌체 검사 ===
            // ==================
            
            else
            {
            

                if (CollisionBtwCollider(LCol, RCol))
                {
                    

                    // 이전 겹침
                    if (iter->second)
                    {
                        if (bDead)
                        {
                            LCol->EndOverlap(RCol);
                            RCol->EndOverlap(LCol);
                        }
                        else
                        {
                            LCol->OnOverlap(RCol);
                            RCol->OnOverlap(LCol);
                        }
                    }

                    // 이전 겹치지 않음
                    else
                    {
                        if (!bDead)
                        {
                           

                            LCol->BeginOverlap(RCol);
                            RCol->BeginOverlap(LCol);
                            iter->second = true;
                        }
                    }
                }

                // 현재 겹치지 않음
                else
                {
                    // 이전 충돌
                    if (iter->second)
                    {
                        LCol->EndOverlap(RCol);
                        RCol->EndOverlap(LCol);
                        iter->second = false;
                    }
                }
            }
        }
    }
}

bool CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
    Vec2 vLeftPos = _pLeft->GetFinalPos();
    Vec2 vLeftScale = _pLeft->GetScale();

    Vec2 vRightPos = _pRight->GetFinalPos();
    Vec2 vRightScale = _pRight->GetScale();

    if (fabsf(vLeftPos.x - vRightPos.x) > (vLeftScale.x / 2.f + vRightScale.x / 2.f))
        return false;

    if (fabsf(vLeftPos.y - vRightPos.y) > (vLeftScale.y / 2.f + vRightScale.y / 2.f))
        return false;

    return true;
}



void CCollisionMgr::LayerCheck(LAYER _left, LAYER _right)
{
    UINT iRow = (UINT)_left;
    UINT iCol = (UINT)_right;

    if (iRow > iCol)
    {
        UINT iTemp = iCol;
        iCol = iRow;
        iRow = iTemp;
    }

    m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionClear(LAYER _LAYER)
{
    UINT iCol = (UINT)_LAYER;
    
    for (UINT iRow = 0; iRow < (UINT)LAYER::END; ++iRow)
    {
        UINT lRow = iRow;
        UINT rCol = iCol;

        if (lRow > rCol)
        {
            UINT iTemp = lRow;
            lRow = rCol;
            rCol = iTemp;
        }

        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

        const vector<CActor*>& vecLeft = pCurLevel->GetLayer((LAYER)lRow);
        const vector<CActor*>& vecRight = pCurLevel->GetLayer((LAYER)rCol);

        for (size_t i = 0; i < vecLeft.size(); ++i)
        {
            // 충돌체가 없는 경우
            if (nullptr == vecLeft[i]->GetCollider())
                continue;

            size_t j = 0;
            if ((LAYER)lRow == (LAYER)rCol) // Left, Right 동일 레이어인 경우, 이중 검사를 피하기 위함
            {
                j = i;
            }

            for (; j < vecRight.size(); ++j)
            {
                CCollider* LCol = vecLeft[i]->GetCollider();
                CCollider* RCol = vecRight[j]->GetCollider();

                // 충돌체를 보유하고 있지 않거나, 충돌을 진행시킬 두 대상이 동일한 오브젝트인 경우
                if (nullptr == RCol || vecLeft[i] == vecRight[j])
                    continue;

                if (iRow == 5)
                    int a = 0;

                // 두 충돌체의 아이디를 조합
                CollisionID ID = {};
                ID.LeftID = LCol->GetID();
                ID.RightID = RCol->GetID();

                // 일반 Collision 충돌 이력 검사 iterator
                map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
                if (iter == m_mapPrevInfo.end())
                {
                    m_mapPrevInfo.insert(make_pair(ID.id, false));
                    iter = m_mapPrevInfo.find(ID.id);
                }

                // Platform 충돌 모니터링 iterator
                map<UINT_PTR, bool>::iterator MntrnIter = m_mapMntrn.find(ID.id);
                if (MntrnIter == m_mapMntrn.end())
                {
                    m_mapMntrn.insert(make_pair(ID.id, true));
                    MntrnIter = m_mapMntrn.find(ID.id);
                }

                if ((LAYER)iRow == LAYER::PLATFORM)
                {
                    if (MntrnIter->second)
                        MntrnIter->second = false;
                }
                
                if (iter->second)
                {
                    iter->second = false;
                    LCol->EndOverlap(RCol);
                    RCol->EndOverlap(LCol);
                }
            }
        }
    }
}
