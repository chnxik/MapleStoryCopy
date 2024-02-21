#pragma once
#include "CSkill.h"
class Skillbrick4 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillbrick4);

public:
    Skillbrick4(CPlayer* pPlayer);
    ~Skillbrick4();
};

