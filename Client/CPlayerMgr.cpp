#include "pch.h"
#include "CPlayerMgr.h"

#include "CLevelMgr.h"
#include "CKeyMgr.h"

#include "CPlayer.h"
#include "CStatusBarUI.h"
#include "CExpBarUI.h"
#include "CQuickSlotUI.h"
#include "CPlayerStatWin.h"
#include "CPlayerSkillWin.h"
#include "CPlayerInvenWin.h"
#include "CLevel.h"

#include "CAnimation.h"

CPlayerMgr::CPlayerMgr()
	: m_pPlayer(nullptr)
	, m_pStatusBar(nullptr)
	, m_pExpBar(nullptr)
	, m_pQuickSlot(nullptr)
	, m_pPlayerStatWin(nullptr)
	, m_pPlayerSkillWin(nullptr)
	, m_pPlayerInvenWin(nullptr)
	, m_iSkillLv{}
{
}

CPlayerMgr::~CPlayerMgr()
{
	DEL(m_pPlayer);
	DEL(m_pStatusBar);
	DEL(m_pExpBar);
	DEL(m_pQuickSlot);
	DEL(m_pPlayerStatWin);
	DEL(m_pPlayerSkillWin);
	DEL(m_pPlayerInvenWin);
}

void CPlayerMgr::tick()
{
	if (ISTAP(KEY::P))
		ToggleStatWin();

	if (ISTAP(KEY::K))
		ToggleSkillWin();

	if (ISTAP(KEY::I))
		ToggleInvenWin();

	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (ISTAP(KEY::ESC))
	{
		if (m_pPlayerStatWin->IsUIOpen())
		{
			m_pPlayerStatWin->UIClose();
			CurLevel->CloseUI(m_pPlayerStatWin);
		}
		if (m_pPlayerSkillWin->IsUIOpen())
		{
			m_pPlayerSkillWin->UIClose();
			CurLevel->CloseUI(m_pPlayerSkillWin);
		}
		if (m_pPlayerInvenWin->IsUIOpen())
		{
			m_pPlayerInvenWin->UIClose();
			CurLevel->CloseUI(m_pPlayerInvenWin);
		}
	}
}

void CPlayerMgr::init()
{
	m_pPlayer = new CPlayer;
	m_pPlayer->SetCmrAfctd(true);
	
	m_pStatusBar = new CStatusBarUI(m_pPlayer);
	m_pExpBar = new CExpBarUI(m_pPlayer);
	m_pQuickSlot = new CQuickSlotUI(m_pPlayer);
	m_pPlayerStatWin = new CPlayerStatWin(m_pPlayer);
	m_pPlayerSkillWin = new CPlayerSkillWin(m_pPlayer);
	m_pPlayerInvenWin = new CPlayerInvenWin(m_pPlayer);

	m_iSkillLv[(UINT)SKILL::STROKE] = 1;
}

void CPlayerMgr::ToggleStatWin()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (m_pPlayerStatWin->IsUIOpen())
	{
		m_pPlayerStatWin->UIClose();
		CurLevel->CloseUI(m_pPlayerStatWin);
	}
	else
	{
		CurLevel->OpenUI(m_pPlayerStatWin);
		m_pPlayerStatWin->UIOpen();
	}
}

void CPlayerMgr::ToggleSkillWin()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (m_pPlayerSkillWin->IsUIOpen())
	{
		m_pPlayerSkillWin->UIClose();
		CurLevel->CloseUI(m_pPlayerSkillWin);
	}
	else
	{
		CurLevel->OpenUI(m_pPlayerSkillWin);
		m_pPlayerSkillWin->UIOpen();
	}
}

void CPlayerMgr::ToggleInvenWin()
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (m_pPlayerInvenWin->IsUIOpen())
	{
		m_pPlayerInvenWin->UIClose();
		CurLevel->CloseUI(m_pPlayerInvenWin);
	}
	else
	{
		CurLevel->OpenUI(m_pPlayerInvenWin);
		m_pPlayerInvenWin->UIOpen();
	}
}

void CPlayerMgr::AddSkillLv(SKILL _skill)
{

	if (m_iSkillLv[(UINT)_skill] < 20)
	{
		++m_iSkillLv[(UINT)_skill];
		m_pPlayer->SkillUP();
	}
}
