#pragma once
#include "CActor.h"

class CTexture;

class CDamage :
    public CActor
{
private:
    CTexture* m_pTex;
    float m_fRatio;
    int m_iNumb;

    virtual void tick();
    virtual void render(HDC _dc);

    CLONE_DEACTIVATE(CDamage);
public:
    CDamage(int _num,DMG_TYPE _type);
    ~CDamage();
};

