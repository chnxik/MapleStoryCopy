#include "pch.h"
#include "CMobIdleLeft.h"

#include "CTimeMgr.h"
#include "CMob.h"

void CMobIdleLeft::Update(CMob* pMob)
{
	m_fAcc += DT;
	if (m_fAcc >= 5.f)
		pMob->randState();
}

void CMobIdleLeft::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	pMob->SetDir(eDir::LEFT);
	pMob->Idle();
}

void CMobIdleLeft::Exit(CMob* pMob)
{
}
