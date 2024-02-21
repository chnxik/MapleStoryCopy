#include "pch.h"
#include "CLevelChange.h"

#include "CLevelMgr.h"
#include "CEventMgr.h"
#include "CCollisionMgr.h"
#include "CPortal.h"

void CLevelChange::tick()
{
	CCollisionMgr::GetInst()->CollisionClear(LAYER::PLAYER);
	CCollisionMgr::GetInst()->CollisionClear(LAYER::SKILL);
	CCollisionMgr::GetInst()->Clear();
	CPortal::SetZeroPortal();
	ChangeLevel();
	CLevelMgr::GetInst()->ChangeState(CHANGESTATE(CLevelState)::In);
}

void CLevelChange::Enter()
{
}

void CLevelChange::Exit()
{
	
	CLevelMgr::GetInst()->SetChangeInfo(LEVEL_TYPE::END, 0);
}

void CLevelChange::ChangeLevel()
{
	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::LEVEL_CHANGE;
	_evn.wParam = (DWORD_PTR)CLevelMgr::GetInst()->m_eNextLevel;
	_evn.lParam = (DWORD_PTR)CLevelMgr::GetInst()->m_iNextPortalNo;
	CEventMgr::GetInst()->AddEvent(_evn);
}
