#pragma once
#include "CUI.h"


class CLvNum :
    public CUI
{
private:
    NUMB        m_eCurNum;
    bool        m_bPrint;
    CTexture* m_pNumTex[10];

public:
    void SetNum(UINT _iNum) { m_eCurNum = (NUMB)_iNum; }
    inline void SetPrint(bool _b) { m_bPrint = _b; }

public:
    virtual void tick();
    virtual void render(HDC _dc);

public:
    CLONE_DEACTIVATE(CLvNum);

public:
    CLvNum();
    ~CLvNum();
};