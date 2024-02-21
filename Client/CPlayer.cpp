#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CResMgr.h"
#include "CBattleMgr.h"
#include "CPlayerMgr.h"

#include "CLevel.h"
#include "CPortal.h"
#include "CMap.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayerStandRight.h"
#include "CPlayerInvenWin.h"

#include "CPlatform.h"
#include "CMob.h"
#include "CFiledItem.h"

#include "DoubleJump.h"

CPlayer::CPlayer()
	: m_pState(nullptr)
	, m_pPlatform(nullptr)
	, m_pLiftObj(nullptr)
	, m_pSound{}
	, m_bAlert(false)
	, m_fAlertAcc(0.f)
	, m_fInvincibleAcc(0.f)
	, m_bInvincible(false)
	, m_arrtSkill{}
	, m_pTomb(nullptr)
	, m_pDeadMessage(nullptr)
	, m_bPlayerDead(false)
{
	SetInterface();
	SetAnimation();
	Keyinit();
}

CPlayer::~CPlayer()
{
}

bool CPlayer::IsEarth()
{
	if(m_pPlatform == nullptr)
		return false;

	if (m_pPlatform->IsEarth())
		return true;
	else
		return false;
}


void CPlayer::SetDir(eDir _dir)
{
	CActor::SetDir(_dir);
}

void CPlayer::tick()
{
	if (!m_bPlayerDead)
	{
		if (m_bAlert)
		{
			m_fAlertAcc += DT;
			if (5.f < m_fAlertAcc)
				m_bAlert = false;
		}

		if (m_bInvincible)
		{
			m_fInvincibleAcc += DT;
			if (5.f < m_fInvincibleAcc)
				m_bInvincible = false;
		}

		if (m_pTargetItem != nullptr)
		{
			if (!(m_pTargetItem->IsGetable()))
				m_pTargetItem = nullptr;
			else
			{
				if (ISTAP(KEY::Z))
				{
					if (CPlayerMgr::GetInst()->GetInvenWin()->GetItemCnt() < 8)
					{
						CPlayerMgr::GetInst()->GetInvenWin()->AddItem(m_pTargetItem->GetItem());
						m_pSound[(UINT)SOUND_ETC::GETITEM]->SetPosition(0);
						m_pSound[(UINT)SOUND_ETC::GETITEM]->Play(false);
						m_pTargetItem = nullptr;
					}
				}

			}
		}

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
		CMap* pCurMap = pCurLevel->GetCurMap();

		if (pCurMap)
		{
			if (pCurMap->GetScale().y < GetPos().y)
			{
				if (pCurLevel->GetPortal(PORTAL::PORTAL1) != nullptr)
				{
					GetRigidbody()->SetVelocity(Vec2(0, 0));
					Vec2 vPos = pCurLevel->GetPortal(PORTAL::PORTAL1)->GetSpawnPos();
					SetPos(vPos);
				}
			}
		}

		CoolTime();
		m_pState->KeyInput(this);
		m_pState->Update(this);
	}

	if (ISTAP(KEY::F3))
	{
		int Exp = m_tStatus.MaxExp - m_tStatus.Exp;
		AddExp(Exp);
	}

	CActor::tick();
}

void CPlayer::render(HDC _dc)
{
	CActor::render(_dc);
	if (CDebug::GetInst()->IsDebugTextOn())
	{
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		RECT rt = { (LONG)(vPos.x - 200),
					(LONG)(vPos.y - 50),
					(LONG)(vPos.x + 200),
					(LONG)(vPos.y) };	// 문자가 써질 사각형

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"위치 : x : %d y : %d", (int)GetPos().x, (int)GetPos().y);

		SetBkMode(_dc, OPAQUE);				// 문자 배경 투명 설정
		DrawText(_dc, szBuff, -1, &rt, DT_CENTER);	// 문자 출력

		Ellipse(_dc, (int)(vPos.x - 2.f), (int)(vPos.y - 2.f), (int)(vPos.x + 2.f), (int)(vPos.y + 2.f));
	}
}

void CPlayer::BeginOverlap(CCollider* _pOther)
{
	CPlatform* pPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (pPlatform)
	{
		m_pPlatform = pPlatform;
		GetRigidbody()->SetVelocityLimit(300.f);
	}
}

void CPlayer::OnOverlap(CCollider* _pOther)
{
	CMob* pMob = dynamic_cast<CMob*>(_pOther->GetOwner());
	if (pMob)
		CBattleMgr::GetInst()->Battle(this, pMob);

	CFiledItem* pItem = dynamic_cast<CFiledItem*>(_pOther->GetOwner());
	if (pItem)
	{
		// 타겟아이템이 없을때
		if (m_pTargetItem == nullptr)
		{
			// 아이템이 습득 가능상태일때
			if (pItem->IsGetable())
				m_pTargetItem = pItem;
		}
	}
}

void CPlayer::EndOverlap(CCollider* _pOther)
{
	CPlatform* pPlatform = dynamic_cast<CPlatform*>(_pOther->GetOwner());
	if (pPlatform)
	{
		m_pPlatform = nullptr;
	}

	CFiledItem* pItem = dynamic_cast<CFiledItem*>(_pOther->GetOwner());
	if (pItem)
	{
		if (m_pTargetItem == pItem)
			m_pTargetItem = nullptr;
	}
}

void CPlayer::ChangeState(CPlayerState* _newState)
{
	if (m_pState != nullptr)
		m_pState->Exit(this);

	m_pState = _newState;
	m_pState->Enter(this);
}