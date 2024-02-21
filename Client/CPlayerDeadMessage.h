#pragma once
#include "CUI.h"

class CPlayer;

class CPlayerDeadMessage :
    public CUI
{
private:
    CPlayer* m_pPlayer;

public:
    void init();

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CPlayerDeadMessage(CPlayer* pPlayer);
    ~CPlayerDeadMessage();
};