#include "pch.h"
#include "CStatusBarUI.h"

#include "CEngine.h"

#include "CLayerUI.h"
#include "CBackGrndUI.h"
#include "CGaugeUI.h"
#include "CStatusLevelUI.h"
#include "CResMgr.h"

#include "CPlayer.h"
#include "CTexture.h"

CStatusBarUI::CStatusBarUI(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, m_pHPGauge(nullptr)
	, m_pMPGauge(nullptr)
	, m_pLv(nullptr)
{
	init();
}

CStatusBarUI::~CStatusBarUI()
{
}

void CStatusBarUI::init()
{
	CBackGrndUI* StatusBackGrnd = new CBackGrndUI;
	CLayerUI* StatusLayer = new CLayerUI;
	m_pHPGauge = new CGaugeUI;
	m_pMPGauge = new CGaugeUI;
	m_pLv = new CStatusLevelUI;
	
	StatusBackGrnd->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatusBackgrnd",L"texture\\UI\\Mainbar\\Status\\backgrnd.png"));
	StatusLayer->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatusLayer",L"texture\\UI\\Mainbar\\Status\\layer.png"));
	m_pHPGauge->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatusHPGauge",L"texture\\UI\\Mainbar\\Status\\hp.png"));
	m_pMPGauge->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatusMPGauge",L"texture\\UI\\Mainbar\\Status\\mp.png"));
	m_pLv->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatusLvChar",L"texture\\UI\\Mainbar\\Status\\Lv.png"));

	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x = (vPos.x / 2.f) - (StatusLayer->GetIdleTex()->Width() / 2);
	vPos.y = vPos.y - (StatusLayer->GetIdleTex()->Height()) - 10;
	SetPos(vPos);
	
	StatusBackGrnd->SetPos(Vec2(3,24));
	m_pHPGauge->SetPos(Vec2(25,28));
	m_pMPGauge->SetPos(Vec2(25,44));
	m_pLv->SetPos(Vec2(25,8));

	m_pHPGauge->Numinit();
	m_pMPGauge->Numinit();
	m_pLv->Numinit();

	AddChildUI(StatusBackGrnd);
	AddChildUI(m_pHPGauge);
	AddChildUI(m_pMPGauge);

	AddChildUI(StatusLayer);
	AddChildUI(m_pLv);
	
	tStatus PlayerStatus = m_pPlayer->GetStatus();

	m_pHPGauge->SetMaxValue(PlayerStatus.MaxHP);
	m_pHPGauge->SetValue(PlayerStatus.HP);
	m_pMPGauge->SetMaxValue(PlayerStatus.MaxMP);
	m_pMPGauge->SetValue(PlayerStatus.MP);

}

void CStatusBarUI::tick()
{
	tStatus PlayerStatus = m_pPlayer->GetStatus();

	m_pHPGauge->SetMaxValue(PlayerStatus.MaxHP);
	m_pMPGauge->SetMaxValue(PlayerStatus.MaxMP);
	m_pHPGauge->UpdateValue(PlayerStatus.HP);
	m_pMPGauge->UpdateValue(PlayerStatus.MP);
	m_pLv->updateLevel(PlayerStatus.Lv);

	CUI::tick();
}

void CStatusBarUI::render(HDC _dc)
{
	render_childUI(_dc);
}