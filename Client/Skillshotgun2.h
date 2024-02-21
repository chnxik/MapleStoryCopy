#pragma once
#include "CSkill.h"
class Skillshotgun2 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(Skillshotgun2);

public:
    Skillshotgun2(CPlayer* pPlayer);
    ~Skillshotgun2();
};