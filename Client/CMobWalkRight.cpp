#include "pch.h"
#include "CMobWalkRight.h"

#include "CTimeMgr.h"
#include "CMob.h"

#include "CRigidbody.h"

void CMobWalkRight::Update(CMob* pMob)
{
	m_fAcc += DT;
	pMob->GetRigidbody()->AddForce(Vec2(1500.f, 0.f));
	if (m_fAcc >= 5.f)
		pMob->randState();
}

void CMobWalkRight::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	pMob->SetDir(eDir::RIGHT);
	pMob->Walk();
}

void CMobWalkRight::Exit(CMob* pMob)
{
}
