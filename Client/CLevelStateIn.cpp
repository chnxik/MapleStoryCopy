#include "pch.h"
#include "CLevelStateIn.h"

#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

void CLevelStateIn::tick()
{
	_facc += DT;

	if (0.5f <= _facc)
		CLevelMgr::GetInst()->ChangeState(CHANGESTATE(CLevelState)::Idle);
}

void CLevelStateIn::Enter()
{
	_facc = 0.f;
	CCamera::GetInst()->FadeIn(0.5f);
}

void CLevelStateIn::Exit()
{
	CLevelMgr::GetInst()->SetWaiting(false);
}
