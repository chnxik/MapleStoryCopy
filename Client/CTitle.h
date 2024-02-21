#pragma once
#include "CActor.h"

class CSound;

class CTitle :
    public CActor
{
private:
    float m_fAcc;
    bool m_bPlay;
    CSound* m_pSound;

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CTitle);

public:
    CTitle();
    ~CTitle();
};