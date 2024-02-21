#pragma once
#include "CUI.h"

class CLvNum;

class CStatusLevelUI :
    public CUI
{
private:
    UINT m_iLevel;
    CLvNum* m_arrVal[3];

public:
    void updateLevel(UINT _iLevel) { m_iLevel = _iLevel; }

public:
    void Numinit();
    void SetVelueNum();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CStatusLevelUI);

public:
    CStatusLevelUI();
    ~CStatusLevelUI();
};

