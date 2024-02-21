#pragma once
#include "CUI.h"

class CTexture;
class CSound;

class CTab :
    public CUI
{
private:
    TOOL_TAP    m_eThisType;
    CTexture*   m_pSelectedTex;
    CSound*     m_pTabSound;

public:
    virtual void render(HDC _dc) override;

public:
    void SetSelectedTex(CTexture* _pTex) { m_pSelectedTex = _pTex; }
    void SetMod(TOOL_TAP _Mod) { m_eThisType = _Mod; }

private:
    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;

public:
    CLONE(CTab);

public:
    CTab();
    ~CTab();
};

