#include "pch.h"
#include "CLevelStateOut.h"

#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

void CLevelStateOut::tick()
{
	_facc += DT;

	if (0.5f <= _facc)
		CLevelMgr::GetInst()->ChangeState(CHANGESTATE(CLevelState)::Change);
}

void CLevelStateOut::Enter()
{
	_facc = 0.f;
	CLevelMgr::GetInst()->SetWaiting(true);
	CCamera::GetInst()->FadeOut(0.5f);
}

void CLevelStateOut::Exit()
{
}
