#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel.h"

#include "CLogoLevel.h"
#include "CLoginLevel.h"

#include "CToolLevel.h"
#include "CStage01.h"
#include "CStage02.h"
#include "CStage03.h"
#include "CStage04.h"
#include "CStage05.h"
#include "CStage06.h"

#include "CLevelState.h"
#include "CLevelStateIdle.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurLevel(nullptr)
	, m_pState(nullptr)
	, m_eNextLevel(LEVEL_TYPE::END)
	, m_iNextPortalNo(0)
	, m_bWaiting(false)
{

}

CLevelMgr::~CLevelMgr()
{
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		DEL(m_arrLevel[i]);
	}
}

void CLevelMgr::init()
{
	m_pState = &CLevelState::Idle;
//	m_arrLevel[(UINT)LEVEL_TYPE::TOOL] = new CToolLevel;

	// Level 생성
	m_arrLevel[(UINT)LEVEL_TYPE::LOGO] = new CLogoLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::LOGIN] = new CLoginLevel;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE01] = new CStage01;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE02] = new CStage02;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE03] = new CStage03;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE04] = new CStage04;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE05] = new CStage05;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE06] = new CStage06;

	ChangeLevel(LEVEL_TYPE::LOGO, 0);

//	ChangeLevel(LEVEL_TYPE::TOOL, 0);
}

void CLevelMgr::tick()
{
	m_pState->tick();
	m_pCurLevel->tick();
	m_pCurLevel->final_tick();
}

void CLevelMgr::render(HDC _dc)
{
	m_pCurLevel->render(_dc);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _eNext, UINT _iPortalNo)
{
	// 현재 레벨과 변경하려는 레벨이 동일 한 경우
	assert(m_pCurLevel != m_arrLevel[(UINT)_eNext]);

	// 현재 레벨을 벗어남
	if (nullptr != m_pCurLevel)
		m_pCurLevel->Exit();

	m_pCurLevel = m_arrLevel[(UINT)_eNext];
	m_pCurLevel->Enter(_iPortalNo);
}

void CLevelMgr::ChangeState(CLevelState* _newState)
{
	if (m_pState != nullptr)
		m_pState->Exit();

	m_pState = _newState;
	m_pState->Enter();
}
