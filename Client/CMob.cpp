#include "pch.h"
#include "CMob.h"

#include "CSpawner.h"
#include "CMobState.h"
#include "CMobSpawn.h"

#include "CAnimator.h"

CMob::CMob(CSpawner* _pSpawner)
	: m_pSpawner(_pSpawner)
	, m_tStatus{ 0 }
	, m_pState(nullptr)
	, m_pHitSound(nullptr)
	, m_pDeadSound(nullptr)
{
}

CMob::~CMob()
{
}

void CMob::tick()
{
	m_pState->Update(this);
}

void CMob::ChangeState(CMobState* _newState)
{
	if (m_pState != nullptr)
		m_pState->Exit(this);

	m_pState = _newState;
	m_pState->Enter(this);
}

void CMob::CreateState()
{
	m_pState = &CMobState::spawn;
}

void CMob::HPtick(int _amount)
{
	m_tStatus.HP += _amount;
	if (m_tStatus.HP <= 0)
		m_tStatus.HP = 0;

	if (m_tStatus.HP >= (int)m_tStatus.MaxHP)
		m_tStatus.HP = m_tStatus.MaxHP;
}

void CMob::MPtick(int _amount)
{
	m_tStatus.MP += _amount;
	if (m_tStatus.MP <= 0)
		m_tStatus.MP = 0;

	if (m_tStatus.MP >= (int)m_tStatus.MaxMP)
		m_tStatus.MP = m_tStatus.MaxMP;
}

void CMob::randState()
{
	UINT State = (rand() % 2);
	eDir dir = (eDir)(rand() % 2);
	switch (State)
	{
	case 0:
	{
		switch (dir)
		{
		case eDir::LEFT:
			ChangeState(CHANGESTATE(CMobState)::idleleft);
			break;
		case eDir::RIGHT:
			ChangeState(CHANGESTATE(CMobState)::idleright);
			break;
		}
		break;
	}
	case 1:
	{
		switch (dir)
		{
		case eDir::LEFT:
			ChangeState(CHANGESTATE(CMobState)::walkleft);
			break;
		case eDir::RIGHT:
			ChangeState(CHANGESTATE(CMobState)::walkright);
			break;
		}
		break;
	}
	}
}

float CMob::Dead()
{
	m_pSpawner->DeadMob();
	SetDead();

	return 0;
}