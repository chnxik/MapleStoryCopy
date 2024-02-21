#pragma once
#include "CInteraction.h"

class Tomb :
    public CInteraction
{
private:
    float m_fAcc;
    Vec2 m_TombPos;

public:
    virtual void tick();
    virtual void render(HDC _dc);

    CLONE_DEACTIVATE(Tomb);

    virtual void Active();

public:
    Tomb(CPlayer* pPlayer);
    ~Tomb();
};

