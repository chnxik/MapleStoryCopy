#pragma once
#include "CSkill.h"
class Skillbrick3 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillbrick3);

public:
    Skillbrick3(CPlayer* pPlayer);
    ~Skillbrick3();
};

