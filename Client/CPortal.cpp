#include "pch.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CLevelMgr.h"

#include "CPortal.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"

#include "CLevel.h"

#include "CPlayer.h"
#include "CSound.h"

UINT CPortal::g_iPortalNo = 1;

CPortal::CPortal()
	: m_iPortalNo(g_iPortalNo++)
	, m_pConnectLevel(LEVEL_TYPE::END)
	, m_iConnectPortalNo(0)
{
	SetCmrAfctd(true);
	SetScale(Vec2(89, 30));
	
	CreateAnimator();
	CreateCollider();
	GetCollider()->SetScale(Vec2(20, 60));
	
	GetAnimator()->CreateAnimation(L"portal");
	GetAnimator()->Play(L"portal",true);

	m_pPortalSound = CResMgr::GetInst()->LoadSound(L"Portal", L"sound\\etc\\Portal.wav");
}

CPortal::~CPortal()
{
}

void CPortal::tick()
{
	CActor::tick();
	CActor::final_tick();
}

void CPortal::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	CActor::render(_dc);
	if (CDebug::GetInst()->IsDebugTextOn())
	{
		RECT rt = { (LONG)(vPos.x - 200),
					(LONG)(vPos.y - 100),
					(LONG)(vPos.x + 200),
					(LONG)(vPos.y) };	// 문자가 써질 사각형

		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"PortalNo.%d\nx : %d\ny : %d", m_iPortalNo,(int)GetPos().x,(int)GetPos().y);

		SetBkMode(_dc, OPAQUE);				// 문자 배경 투명 설정
		DrawText(_dc, szBuff, -1, &rt, DT_CENTER);	// 문자 출력

		Ellipse(_dc, (int)(vPos.x - 2.f), (int)(vPos.y - 2.f), (int)(vPos.x + 2.f), (int)(vPos.y + 2.f));
	}
}

void CPortal::BeginOverlap(CCollider* _pOther)
{
}

void CPortal::OnOverlap(CCollider* _pOther)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOther->GetOwner());
	if (pPlayer)
	{
		if (CLevelMgr::GetInst()->IsWaiting() == false)
		{
			if (ISHOLD(KEY::UP))
			{
				if (m_pConnectLevel != LEVEL_TYPE::END)
				{
					m_pPortalSound->Play(false);
					ChangeLevel(m_pConnectLevel, m_iConnectPortalNo);
				}
			}
		}
	}
}

void CPortal::EndOverlap(CCollider* _pOther)
{
}

void CPortal::SetDead()
{
	if (1 < g_iPortalNo)
		--g_iPortalNo;

	CActor::SetDead();
}

CPortal* CPortal::CreatePortal()
{
	if ((UINT)PORTAL::END <= g_iPortalNo)	// 포탈의 최대 갯수보다 크거나 같다면
	{
		wchar_t szbuff[256] = {};
		swprintf_s(szbuff, L"해당 맵 최대 포탈 갯수 초과.\n현재 맵 포탈 수 : %d", g_iPortalNo - 1);
		ShowCursor(true);
		MessageBox(nullptr, szbuff, L"맵 이동 포탈 생성 실패", MB_OK);
		ShowCursor(false);
		return nullptr;
	}
	
	return new CPortal;
}
