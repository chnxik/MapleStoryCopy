#pragma once
#include "CInteraction.h"

class LevelUP :
    public CInteraction
{
public:
    virtual void tick();
    virtual void render(HDC _dc);

    CLONE_DEACTIVATE(LevelUP);

    virtual void Active();

public:
    LevelUP(CPlayer* pPlayer);
    ~LevelUP();
};

