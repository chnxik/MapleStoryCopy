#include "pch.h"
#include "CMobSpawn.h"

#include "CTimeMgr.h"

#include "CMob.h"
#include "CSpawner.h"
#include "CAnimator.h"


void CMobSpawn::Update(CMob* pMob)
{
	m_fAcc += 40 * DT;

	pMob->Spawn((UINT)m_fAcc);
	if (m_fAcc >= 100)
		pMob->randState();
}

void CMobSpawn::Enter(CMob* pMob)
{
	pMob->SetInvincible(true);
	m_fAcc = 0.f;
}

void CMobSpawn::Exit(CMob* pMob)
{
	pMob->SetInvincible(false);
}
