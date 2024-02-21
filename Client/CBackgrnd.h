#pragma once
#include "CActor.h"

class CTexture;

class CBackgrnd :
    public CActor
{
private:
    CTexture* m_pBgTex;
    Vec2      m_vTexOffset;
    UINT      m_iOpacity;
    
    
public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void SetBackGrnd(wstring _strKey, wstring _strRelativePath);
    void SetFullOpacity() { m_iOpacity = 255; }

public:
    CLONE(CBackgrnd);

public:
    CBackgrnd();
    ~CBackgrnd();
};

