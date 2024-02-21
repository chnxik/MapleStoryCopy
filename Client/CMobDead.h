#pragma once
#include "CMobState.h"
class CMobDead :
    public CMobState
{
private:
	float m_fAcc;
	float m_fDeadTime = 0;

public:
	virtual void Update(CMob* pMob);

public:
	virtual void Enter(CMob* pMob);
	virtual void Exit(CMob* pMob);
};

