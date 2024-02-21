#pragma once
#include "CMobState.h"
class CMobIdleLeft :
    public CMobState
{
private:
	float m_fAcc;

public:
	virtual void Update(CMob* _pMob);

public:
	virtual void Enter(CMob* _pMob);
	virtual void Exit(CMob* _pMob);
};

