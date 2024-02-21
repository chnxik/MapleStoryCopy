#include "pch.h"
#include "CLoginLevel.h"

#include "CEngine.h"
#include "CLevelMgr.h"
#include "CResMgr.h"

#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CBackgrnd.h"
#include "CBtnUI.h"

#include "CSound.h"
#include "CTexture.h"

CLoginLevel::CLoginLevel()
	: m_pSound(nullptr)
	, m_pLoginBtn(nullptr)
{
}

CLoginLevel::~CLoginLevel()
{
}

void CLoginLevel::GameStart()
{
	CSound* pSound = CResMgr::GetInst()->LoadSound(L"Login", L"sound\\etc\\GameIn.wav");
	pSound->Play(false);
	ChangeLevel(LEVEL_TYPE::STAGE01, 0);
}

void CLoginLevel::init()
{
	CBackgrnd* BackGrnd = new CBackgrnd;
	BackGrnd->SetBackGrnd(L"LoginTitle", L"texture\\map\\backgrnd\\login.png");
	BackGrnd->SetPos(0);
	BackGrnd->SetFullOpacity();
	Instantiate(BackGrnd, LAYER::BACKGROUND);

	m_pSound = CResMgr::GetInst()->LoadSound(L"TitleBgm", L"sound\\title\\Title.wav");
	m_pSound->PlayToBGM(true);

	CreateUI();
}

void CLoginLevel::Enter(UINT _iPortalNo)
{
	init();
}

void CLoginLevel::Exit()
{
	DEL(m_pLoginBtn);
	DeleteAllActor();
}

void CLoginLevel::CreateUI()
{
	m_pLoginBtn = new CBtnUI;
	Vec2 vPos = CEngine::GetInst()->GetResolution();

	m_pLoginBtn->SetCmrAfctd(false);

	m_pLoginBtn->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"titlebtnidle",L"texture\\UI\\title\\TitleBtIdle.png"));
	m_pLoginBtn->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"titlebtnover",L"texture\\UI\\title\\TitleBtOver.png"));
	m_pLoginBtn->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"titlebtnpressed",L"texture\\UI\\title\\TitleBtpressed.png"));

	vPos /= 2.f;
	vPos.x -= m_pLoginBtn->GetIdleTex()->Width() / 2.f;
	m_pLoginBtn->SetPos(vPos);

	m_pLoginBtn->SetDelegate(this, (DELEGATE)&CLoginLevel::GameStart);

	Instantiate(m_pLoginBtn, LAYER::PLAYERUI);
}