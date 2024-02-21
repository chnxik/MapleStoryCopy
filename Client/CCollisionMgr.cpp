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

            // iRow ���̾�� iCol ���̾�� ���� �浹�˻縦 �����Ѵ�.
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
        // �浹ü�� ���� ���
        if (nullptr == vecLeft[i]->GetCollider())
            continue;

        size_t j = 0;
        if (_left == _right) // Left, Right ���� ���̾��� ���, ���� �˻縦 ���ϱ� ����
        {
            j = i;
        }

        for (; j < vecRight.size(); ++j)
        {
            CCollider* LCol = vecLeft[i]->GetCollider();
            CCollider* RCol = vecRight[j]->GetCollider();

            // �浹ü�� �����ϰ� ���� �ʰų�, �浹�� �����ų �� ����� ������ ������Ʈ�� ���
            if (nullptr == RCol || vecLeft[i] == vecRight[j])
                continue;

            if (_right == (LAYER)5)
                int a = 0;

            // �� �浹ü�� ���̵� ����
            CollisionID ID = {};
            ID.LeftID = LCol->GetID();
            ID.RightID = RCol->GetID();

            // �Ϲ� Collision �浹 �̷� �˻� iterator
            map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
            if (iter == m_mapPrevInfo.end())
            {
                m_mapPrevInfo.insert(make_pair(ID.id, false));
                iter = m_mapPrevInfo.find(ID.id);
            }

            // Platform �浹 ����͸� iterator
            map<UINT_PTR, bool>::iterator MntrnIter = m_mapMntrn.find(ID.id); 
            if (MntrnIter == m_mapMntrn.end())
            {
                m_mapMntrn.insert(make_pair(ID.id, true));
                MntrnIter = m_mapMntrn.find(ID.id);
            }

            bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

            // =========================
            // === Platform �浹 �˻� ===
            // =========================

            if (_left == LAYER::PLATFORM)
            {
                CPlatform* pPlatform = dynamic_cast<CPlatform*>(LCol->GetOwner());  // �÷��� ��ü �����͸� ���´�.
                
                Vec2 vActPos  = RCol->GetGrndPt();  // ��ü GrndPos
                Vec2 vPStrt = pPlatform->GetLdot(); // �÷��� ����
                Vec2 vPEnd = pPlatform->GetRdot();  // �÷��� ������
                
                // �˻� ����� Dead �����ΰ�
                if (!bDead)
                {
                    Vec2 vActVel = RCol->GetOwner()->GetRigidbody()->GetVelocity();
                    float fChckPos = GetVerticalPos(vActPos, vPStrt, pPlatform->GetGradient());

                    // ���� ���� �ȿ� �ִ�.
                    if (vPStrt.x <= vActPos.x && vActPos.x <= vPEnd.x)
                    {

                        if (i == 8)
                            int a = 0;

                        // ���� �浹����
                        if (iter->second)
                        {
                            // ���� �浹 ���� ����
                            if (CheckLineCollision(vActPos.y, fChckPos))
                            {
                                // �浹���̴�.
                                LCol->OnOverlap(RCol);
                                RCol->OnOverlap(LCol);
                            }
                            else
                            {
                                // �浹���� �����.
                                LCol->EndOverlap(RCol);
                                RCol->EndOverlap(LCol);
                                iter->second = false;
                                MntrnIter->second = false;
                            }
                        }

                        // ���� �浹���� �ƴϾ���.
                        else
                        {
                            // �浹�ֽû��´�
                            if (MntrnIter->second)
                            {
                                Vec2 PlfGra = pPlatform->GetGradient();
                                short dbg = GetDegree(pPlatform->GetGradient(), vActVel);

                                if (dbg > 0)
                                    int a = 0;

                                // ��ü ������� �÷����� ���Ѵ�
                                if (0 >= GetDegree(pPlatform->GetGradient(),vActVel))
                                {
                                    // ���� �浹 ����
                                    if (CheckLineCollision(vActPos.y, fChckPos))
                                    {
                                        iter->second = true;        // ���� �浹 ����
                                        MntrnIter->second = false;  // �浹 �ֽ� ����
                                        LCol->BeginOverlap(RCol);   // �浹 ����
                                        RCol->BeginOverlap(LCol);   // �浹 ����
                                    }
                                }
                                else
                                {
                                    int a = 0;
                                }
                            }

                            // �浹�ֽû��� �ƴϴ�
                            else
                            {
                                // �浹 �ֽ� ������
                                if (CheckMntrnTrgt(vActPos.y, fChckPos))
                                {
                                    MntrnIter->second = true;  // �浹 �ֽ� ����
                                    iter->second = false;
                                }
                            }
                        }
                    }

                    // ���ι��� �ȿ� ����.
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

                // �˻� ����� Dead �����̴�.
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
            // === �浹ü �˻� ===
            // ==================
            
            else
            {
            

                if (CollisionBtwCollider(LCol, RCol))
                {
                    

                    // ���� ��ħ
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

                    // ���� ��ġ�� ����
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

                // ���� ��ġ�� ����
                else
                {
                    // ���� �浹
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
            // �浹ü�� ���� ���
            if (nullptr == vecLeft[i]->GetCollider())
                continue;

            size_t j = 0;
            if ((LAYER)lRow == (LAYER)rCol) // Left, Right ���� ���̾��� ���, ���� �˻縦 ���ϱ� ����
            {
                j = i;
            }

            for (; j < vecRight.size(); ++j)
            {
                CCollider* LCol = vecLeft[i]->GetCollider();
                CCollider* RCol = vecRight[j]->GetCollider();

                // �浹ü�� �����ϰ� ���� �ʰų�, �浹�� �����ų �� ����� ������ ������Ʈ�� ���
                if (nullptr == RCol || vecLeft[i] == vecRight[j])
                    continue;

                if (iRow == 5)
                    int a = 0;

                // �� �浹ü�� ���̵� ����
                CollisionID ID = {};
                ID.LeftID = LCol->GetID();
                ID.RightID = RCol->GetID();

                // �Ϲ� Collision �浹 �̷� �˻� iterator
                map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
                if (iter == m_mapPrevInfo.end())
                {
                    m_mapPrevInfo.insert(make_pair(ID.id, false));
                    iter = m_mapPrevInfo.find(ID.id);
                }

                // Platform �浹 ����͸� iterator
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
