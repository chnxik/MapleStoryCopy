#include "pch.h"
#include "CMobIdleRight.h"

#include "CTimeMgr.h"
#include "CMob.h"

void CMobIdleRight::Update(CMob* pMob)
{
	m_fAcc += DT;
	if (m_fAcc >= 5.f)
		pMob->randState();
}

void CMobIdleRight::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	pMob->SetDir(eDir::RIGHT);
	pMob->Idle();
}

void CMobIdleRight::Exit(CMob* pMob)
{
}
