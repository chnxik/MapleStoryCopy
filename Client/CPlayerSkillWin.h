#pragma once
#include "CUI.h"

class CPlayer;
class CPNUI;
class CSkillSLot;


class CPlayerSkillWin :
    public CUI
{
private:
    CPNUI*      m_pPNUI;
    CPlayer*    m_pPlayer;

    CSkillSLot* m_arrSkillSlot[(UINT)SKILL::END];
    RECT m_rtSkillpt;

public:
    void init();

    void SetBtnActive(bool _b);
    void SetSkillInfo();

    CLONE_DEACTIVATE(CPlayerSkillWin);

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CPlayerSkillWin(CPlayer* pPlayer);
    ~CPlayerSkillWin();
};

