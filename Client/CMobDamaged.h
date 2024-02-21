#pragma once
#include "CMobState.h"
class CMobDamaged :
    public CMobState
{
private:
	float m_fAcc = 0.f;
	float m_fDmgTime = 0.f;

public:
	virtual void Update(CMob* _pMob);

public:
	virtual void Enter(CMob* _pMob);
	virtual void Exit(CMob* _pMob);
};

