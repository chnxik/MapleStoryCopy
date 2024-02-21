#pragma once
#include "CUI.h"

class CNum :
    public CUI
{
private:
    NUMB        m_eCurNum;
    bool        m_bPrint;
    CTexture*   m_pNumTex[12];

public:
    void SetNum(UINT _iNum) { m_eCurNum = (NUMB)_iNum; }

    void SetStatTex();
    void SetItemTex();

    inline void SetPrint(bool _b) { m_bPrint = _b; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CNum);

public:
    CNum();
    ~CNum();
};