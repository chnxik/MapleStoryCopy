#pragma once
#include "CPlayerState.h"
class CPlayerSkillBrick1 :
    public CPlayerState
{
private:
    float _facc = 0.f;
    float _fDelay = 0.f;

public:
    virtual void KeyInput(CPlayer* player); // 키입력
    virtual void Update(CPlayer* player);   // 해당 상태의 필요 업데이트

public:
    virtual void Enter(CPlayer* player);  // 상태로 처음 전환될 때
    virtual void Exit(CPlayer* player);   // 상태에서 나올 때
};