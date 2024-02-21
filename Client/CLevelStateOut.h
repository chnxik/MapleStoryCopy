#pragma once
#include "CLevelState.h"
class CLevelStateOut :
    public CLevelState
{
private:
    float _facc = 0.f;

public:
    virtual void tick();   // 해당 상태의 필요 업데이트

public:
    virtual void Enter();  // 상태로 처음 전환될 때
    virtual void Exit();   // 상태에서 나올 때
};

