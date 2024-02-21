#pragma once
#include "CUI.h"

class CPlayer;
class CGaugeUI;
class CStatusLevelUI;

class CStatusBarUI :
    public CUI
{
    CPlayer* m_pPlayer;

    CGaugeUI* m_pHPGauge;
    CGaugeUI* m_pMPGauge;

    CStatusLevelUI* m_pLv;

public:
    void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
    void init();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CStatusBarUI(CPlayer* pPlayer);
    ~CStatusBarUI();
};