#pragma once
#include "CSkill.h"
class Skillshotgun1 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillshotgun1);

public:
    Skillshotgun1(CPlayer* pPlayer);
    ~Skillshotgun1();
};

