#include "pch.h"
#include "CMobDamaged.h"

#include "CTimeMgr.h"
#include "CRigidbody.h"

#include "CMob.h"
#include "CSound.h"

void CMobDamaged::Update(CMob* pMob)
{
	m_fAcc += DT;

	if (m_fAcc > m_fDmgTime)
		pMob->randState();
}

void CMobDamaged::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	m_fDmgTime = pMob->Damaged();
	pMob->GetRigidbody()->SetFriction(50);
	pMob->GetRigidbody()->SetFrictionScale(0.1f);
	pMob->GetHitSound()->SetPosition(0);
	pMob->GetHitSound()->Play(false);
}

void CMobDamaged::Exit(CMob* pMob)
{
	pMob->GetRigidbody()->SetFriction(1000);
	pMob->GetRigidbody()->SetFrictionScale(1.f);
}
