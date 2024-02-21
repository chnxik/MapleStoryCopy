#include "pch.h"
#include "CPlayerStatWin.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CResMgr.h"

#include "CPNUI.h"
#include "CLayerUI.h"
#include "CBtnUI.h"

#include "CTexture.h"

#include "CPlayer.h"
#include "CSound.h"

CPlayerStatWin::CPlayerStatWin(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, m_pPNUI(nullptr)
	, m_tPlayerStatus{}
	, m_pbtnHP(nullptr)
	, m_pbtnMP(nullptr)
	, m_pbtnATK(nullptr)
	, m_pbtnDEF(nullptr)
	, m_rtStat{}
{
	init();
}

CPlayerStatWin::~CPlayerStatWin()
{
}

void CPlayerStatWin::init()
{
	SetClose();

	m_pPNUI = new CPNUI;
	CLayerUI* pLayerUI = new CLayerUI;

	m_pbtnHP = new CBtnUI;
	m_pbtnMP = new CBtnUI;
	m_pbtnATK = new CBtnUI;
	m_pbtnDEF = new CBtnUI;


	m_pPNUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatUIBackgrnd",L"texture\\UI\\WindowUI\\StatWindow\\backgrnd.png"));
	pLayerUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"StatUILayer",L"texture\\UI\\WindowUI\\StatWindow\\layer.png"));
	
	m_pbtnHP->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_idle",L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_idle.png"));
	m_pbtnHP->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_over", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_over.png"));
	m_pbtnHP->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_pressed", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_pressed.png"));
	m_pbtnHP->SetDisAbleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_dis", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_dis.png"));
	
	m_pbtnMP->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_idle", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_idle.png"));
	m_pbtnMP->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_over", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_over.png"));
	m_pbtnMP->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_pressed", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_pressed.png"));
	m_pbtnMP->SetDisAbleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_dis", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_dis.png"));

	m_pbtnATK->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_idle", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_idle.png"));
	m_pbtnATK->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_over", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_over.png"));
	m_pbtnATK->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_pressed", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_pressed.png"));
	m_pbtnATK->SetDisAbleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_dis", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_dis.png"));

	m_pbtnDEF->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_idle", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_idle.png"));
	m_pbtnDEF->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_over", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_over.png"));
	m_pbtnDEF->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_pressed", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_pressed.png"));
	m_pbtnDEF->SetDisAbleTex(CResMgr::GetInst()->LoadTexture(L"statupbtn_dis", L"texture\\UI\\WindowUI\\StatWindow\\statupbtn_dis.png"));

	// 포지션 셋팅
	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x *= 3.f / 4.f;
	vPos.y *= 1.f / 8.f;

	m_pPNUI->SetPos(vPos);
	pLayerUI->SetPos(Vec2(6,20));
	m_pbtnHP->SetPos(Vec2(186,65));
	m_pbtnMP->SetPos(Vec2(186,83));
	m_pbtnATK->SetPos(Vec2(186,101));
	m_pbtnDEF->SetPos(Vec2(186,119));

	m_pbtnHP->SetDelegate(m_pPlayer, (DELEGATE)&CPlayer::HPUP);
	m_pbtnMP->SetDelegate(m_pPlayer, (DELEGATE)&CPlayer::MPUP);
	m_pbtnATK->SetDelegate(m_pPlayer, (DELEGATE)&CPlayer::ATKUP);
	m_pbtnDEF->SetDelegate(m_pPlayer, (DELEGATE)&CPlayer::DEFUP);

	AddChildUI(m_pPNUI);
	m_pPNUI->AddChildUI(pLayerUI);
	m_pPNUI->AddChildUI(m_pbtnHP);
	m_pPNUI->AddChildUI(m_pbtnMP);
	m_pPNUI->AddChildUI(m_pbtnATK);
	m_pPNUI->AddChildUI(m_pbtnDEF);
}

void CPlayerStatWin::SetBtnActive(bool _b)
{
	m_pbtnHP->SetActive(_b);
	m_pbtnMP->SetActive(_b);
	m_pbtnATK->SetActive(_b);
	m_pbtnDEF->SetActive(_b);
}

void CPlayerStatWin::tick()
{
	Vec2 vPos = m_pPNUI->GetFinalPos();

	m_tPlayerStatus = m_pPlayer->GetStatus();

	if (0 < m_tPlayerStatus.StatPoint)
		SetBtnActive(true);
	else
		SetBtnActive(false);


	// Text 출력 rt 갱신
	for (int i = 0; i < 2; ++i)
	{
		// 114, 14 크기
		m_rtStat[i] = {
			(LONG)(vPos.x + 73),
			(LONG)(vPos.y + 30 + (i * 18)),
			(LONG)(vPos.x + 73 + 109),
			(LONG)(vPos.y + 30 + (i * 18) + 14) };
	}

	for (int i = 2; i < 6; ++i)
	{
		// 114, 14 크기
		m_rtStat[i] = {
			(LONG)(vPos.x + 73),
			(LONG)(vPos.y + 30 + (i * 18)),
			(LONG)(vPos.x + 73 + 109),
			(LONG)(vPos.y + 30 + (i * 18) + 14) };
	}

	m_rtStat[6] = {
			(LONG)(vPos.x + 71),
			(LONG)(vPos.y + 162),
			(LONG)(vPos.x + 71 + 20),
			(LONG)(vPos.y + 162 + 14) };
	
	CUI::tick();
}

void CPlayerStatWin::render(HDC _dc)
{
	CUI::render_childUI(_dc);

	HFONT hOldFont;
	hOldFont = (HFONT)SelectObject(_dc, CEngine::GetInst()->GetFONT(FONT_TYPE::UINUM));

	// 문자 출력
	wchar_t szbuff[256] = {};

	SetBkMode(_dc, TRANSPARENT);				// 문자 배경 투명 설정

	swprintf_s(szbuff, L"%d", (int)m_tPlayerStatus.Lv); // 레벨
	DrawText(_dc, szbuff, -1, &m_rtStat[0], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d/%d [%.2f%%]", (int)m_tPlayerStatus.Exp, (int)m_tPlayerStatus.MaxExp, (float)m_tPlayerStatus.Exp / (float)m_tPlayerStatus.MaxExp); // 현재경험치
	DrawText(_dc, szbuff, -1, &m_rtStat[1], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d/%d", (int)m_tPlayerStatus.HP, (int)m_tPlayerStatus.MaxHP); // hp
	DrawText(_dc, szbuff, -1, &m_rtStat[2], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d/%d", (int)m_tPlayerStatus.MP, (int)m_tPlayerStatus.MaxMP); // mp
	DrawText(_dc, szbuff, -1, &m_rtStat[3], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d~%d", (int)m_tPlayerStatus.MINATK, (int)m_tPlayerStatus.MAXATK); // 공격력
	DrawText(_dc, szbuff, -1, &m_rtStat[4], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d", (int)m_tPlayerStatus.DEF); // 방어력
	DrawText(_dc, szbuff, -1, &m_rtStat[5], DT_LEFT);	// 문자 출력

	swprintf_s(szbuff, L"%d", (int)m_tPlayerStatus.StatPoint); // 스탯포인트
	DrawText(_dc, szbuff, -1, &m_rtStat[6], DT_RIGHT);	// 문자 출력
	
	SelectObject(_dc, hOldFont);
}

