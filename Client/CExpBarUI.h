#pragma once
#include "CUI.h"

    class CPlayer;
    class CExpGaugeUI;

class CExpBarUI :
    public CUI
{
    CPlayer* m_pPlayer;
    CExpGaugeUI* m_pExpGauge;

public:
    void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
    void init();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CExpBarUI(CPlayer* pPlayer);
    ~CExpBarUI();
};

