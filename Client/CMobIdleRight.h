#pragma once
#include "CMobState.h"
class CMobIdleRight :
    public CMobState
{
private:
	float m_fAcc;

public:
	virtual void Update(CMob* pMob);

public:
	virtual void Enter(CMob* pMob);
	virtual void Exit(CMob* pMob);
};

