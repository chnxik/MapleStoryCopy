#pragma once
#include "CSkill.h"

class SkillStroke2 :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(SkillStroke2);

public:
    SkillStroke2(CPlayer* pPlayer);
    ~SkillStroke2();
};

