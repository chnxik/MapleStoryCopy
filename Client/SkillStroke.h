#pragma once
#include "CSkill.h"
class SkillStroke :
    public CSkill
{
public:
    virtual void tick();
    virtual void Active();

public:
    CLONE_DEACTIVATE(SkillStroke);

public:
    SkillStroke(CPlayer* pPlayer);
    ~SkillStroke();
};

