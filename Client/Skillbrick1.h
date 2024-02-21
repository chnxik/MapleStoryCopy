#pragma once
#include "CSkill.h"
class Skillbrick1 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillbrick1);

public:
    Skillbrick1(CPlayer* pPlayer);
    ~Skillbrick1();
};

