#pragma once
#include "CUI.h"

class CPlayer;
class CBtnUI;
class CPNUI;

class CPlayerStatWin :
    public CUI
{
private:
    CPNUI* m_pPNUI;
    CPlayer* m_pPlayer;
    tStatus m_tPlayerStatus;
    CBtnUI* m_pbtnHP;
    CBtnUI* m_pbtnMP;
    CBtnUI* m_pbtnATK;
    CBtnUI* m_pbtnDEF;

    RECT m_rtStat[7];

public:
    void init();

    void SetBtnActive(bool _b);

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CPlayerStatWin(CPlayer* pPlayer);
    ~CPlayerStatWin();
};

