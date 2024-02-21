#include "pch.h"
#include "CExpBarUI.h"

#include "CEngine.h"

#include "CBackGrndUI.h"
#include "CLayerUI.h"
#include "CExpGaugeUI.h"
#include "CResMgr.h"

#include "CPlayer.h"
#include "CTexture.h"

CExpBarUI::CExpBarUI(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, m_pExpGauge(nullptr)
{
	
	init();
}

CExpBarUI::~CExpBarUI()
{
}

void CExpBarUI::init()
{
	CBackGrndUI* ExpBackGrnd = new CBackGrndUI;
	CLayerUI* ExpCover = new CLayerUI;
	m_pExpGauge = new CExpGaugeUI;

	ExpBackGrnd->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"ExpBackgrnd", L"texture\\UI\\Mainbar\\Exp\\backgrnd.png"));
	ExpCover->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"ExpCover", L"texture\\UI\\Mainbar\\Exp\\cover.png"));
	m_pExpGauge->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"ExpGauge", L"texture\\UI\\Mainbar\\Exp\\exp.png"));

	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x = 0;
	vPos.y = vPos.y - ExpBackGrnd->GetIdleTex()->Height();
	SetPos(vPos);

	m_pExpGauge->SetPos(Vec2(15,2));
	ExpCover->SetPos(Vec2(150,2));

	m_pExpGauge->Numinit();

	AddChildUI(ExpBackGrnd);
	AddChildUI(m_pExpGauge);
	AddChildUI(ExpCover);

	tStatus PlayerStatus = m_pPlayer->GetStatus();
	m_pExpGauge->SetMaxValue(PlayerStatus.MaxExp);
	m_pExpGauge->SetValue(PlayerStatus.Exp);

}

void CExpBarUI::tick()
{
	tStatus PlayerStatus = m_pPlayer->GetStatus();
	m_pExpGauge->SetMaxValue(PlayerStatus.MaxExp);
	m_pExpGauge->UpdateValue(PlayerStatus.Exp);

	CUI::tick();
}

void CExpBarUI::render(HDC _dc)
{
	render_childUI(_dc);
}