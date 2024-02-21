#pragma once
#include "CSkill.h"
class DoubleJump :
    public CSkill
{
public:
    virtual void tick();
    virtual void render(HDC _dc);

    CLONE_DEACTIVATE(DoubleJump);

    virtual void Active();

public:
    DoubleJump(CPlayer* pPlayer);
    ~DoubleJump();
};

