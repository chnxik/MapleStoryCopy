#pragma once
#include "CSkill.h"
class Skillshotgun3 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillshotgun3);

public:
    Skillshotgun3(CPlayer* pPlayer);
    ~Skillshotgun3();
};

