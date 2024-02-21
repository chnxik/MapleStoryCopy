#pragma once
#include "CSkill.h"
class Skillbrick2 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillbrick2);

public:
    Skillbrick2(CPlayer* pPlayer);
    ~Skillbrick2();
};

