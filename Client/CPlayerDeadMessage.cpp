#include "pch.h"
#include "CPlayerDeadMessage.h"

#include "CEngine.h"
#include "CResMgr.h"

#include "CPlayer.h"

#include "CPNUI.h"
#include "CBtnUI.h"

CPlayerDeadMessage::CPlayerDeadMessage(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
{
}

CPlayerDeadMessage::~CPlayerDeadMessage()
{
}

void CPlayerDeadMessage::init()
{
	SetCmrAfctd(true);

	Vec2 vPos = CEngine::GetInst()->GetResolution();

	CPNUI* pPNUI = new CPNUI;
	pPNUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DeadNotice", L"texture\\UI\\die\\DeadNotice.png"));

	vPos /= 2.f;
	vPos -= pPNUI->GetScale() / 2.f;

	pPNUI->SetPos(vPos);

	CBtnUI* Resurrectionbtn = new CBtnUI;

	Resurrectionbtn->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"OKbtn_idle", L"texture\\UI\\die\\btOKIdle.png"));
	Resurrectionbtn->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"OKbtn_over", L"texture\\UI\\die\\btOKOver.png"));
	Resurrectionbtn->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"OKbtn_pressed", L"texture\\UI\\die\\btOKpressed.png"));

	Resurrectionbtn->SetPos(Vec2(130, 99));
	Resurrectionbtn->SetDelegate(m_pPlayer, (DELEGATE)&CPlayer::Resurrection);

	AddChildUI(pPNUI);
	pPNUI->AddChildUI(Resurrectionbtn);
}

void CPlayerDeadMessage::tick()
{
	CUI::tick();
}

void CPlayerDeadMessage::render(HDC _dc)
{
	CUI::render_childUI(_dc);
}
