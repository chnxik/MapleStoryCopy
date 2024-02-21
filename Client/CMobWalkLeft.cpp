#include "pch.h"
#include "CMobWalkLeft.h"

#include "CTimeMgr.h"
#include "CMob.h"

#include "CRigidbody.h"

void CMobWalkLeft::Update(CMob* pMob)
{
	m_fAcc += DT;
	pMob->GetRigidbody()->AddForce(Vec2(-1500.f, 0.f));
	if (m_fAcc >= 5.f)
		pMob->randState();
}

void CMobWalkLeft::Enter(CMob* pMob)
{
	m_fAcc = 0.f;
	pMob->SetDir(eDir::LEFT);
	pMob->Walk();
}

void CMobWalkLeft::Exit(CMob* pMob)
{
}
