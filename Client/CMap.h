#pragma once
#include "CActor.h"

class CTexture;
class CPlatform;
class CWall;

class CMap :
    public CActor
{
private:
    CTexture* m_pMapTex;
    CWall* m_pWall[2];

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    void SetMap(wstring _strKey, wstring _strRelativePath);
    void ScreenWallInit();

public:
    CLONE(CMap);

public:
    CMap();
    ~CMap();
};

