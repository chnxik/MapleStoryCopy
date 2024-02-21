#pragma once
#include "CMobState.h"
class CMobSpawn :
    public CMobState
{
private:
	float m_fAcc = 0;

public:
	virtual void Update(CMob* pMob);

public:
	virtual void Enter(CMob* pMob);
	virtual void Exit(CMob* pMob);
};

