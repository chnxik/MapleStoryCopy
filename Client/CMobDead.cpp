#include "pch.h"
#include "CMobDead.h"

#include "CTimeMgr.h"

#include "CSound.h"
#include "CMob.h"

void CMobDead::Update(CMob* pMob)
{
	m_fAcc += DT;
	if(m_fAcc >= m_fDeadTime)
		pMob->CMob::Dead();
}

void CMobDead::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	pMob->SetInvincible(true);
	m_fDeadTime = pMob->Dead();
	pMob->GetHitSound()->SetPosition(0);
	pMob->GetHitSound()->Play(false);
	pMob->GetDeadSound()->SetPosition(0);
	pMob->GetDeadSound()->Play(false);
}

void CMobDead::Exit(CMob* pMob)
{
}
