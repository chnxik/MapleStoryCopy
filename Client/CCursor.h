#pragma once
#include "CActor.h"

class CSound;

class CCursor :
    public CActor
{
private:
    CSound*     m_CsrSound[(UINT)CSRSTATE::END];
    CTexture*   m_ItemCsr;
    Vec2        m_vItemCsrOffset;
    CSRSTATE    m_eApplyCsrState;
    CSRSTATE    m_ePrevCsrState;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CCursor);

public:
    CCursor();
    ~CCursor();

    friend class CCsrMgr;
};

