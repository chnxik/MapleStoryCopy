#pragma once
#include "CActor.h"

class CSound;

class CUI :
    public CActor
{
private:
    CUI*            m_pParentUI;
    vector<CUI*>    m_vecChildUI;
    Vec2            m_vFinalPos;

    CTexture*       m_pIdleTex;

    bool            m_bLbtnDown;
    bool            m_bMouseOn;

    bool            m_bOpen;

    CSound*         m_pOCSound;

public:
    virtual void tick();
    virtual void render(HDC _dc);
    void linerender(HDC _dc);

    void render_childUI(HDC _dc);

public:
    void SetIdleTex(CTexture* _pTex);

    Vec2 GetFinalPos() { return m_vFinalPos; }

    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }

    CUI* GetParentUI() { return m_pParentUI; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

    CTexture* GetIdleTex() { return m_pIdleTex; }

    void AddChildUI(CUI* _pChildUI)
    {
        _pChildUI->m_pParentUI = this;
        m_vecChildUI.push_back(_pChildUI);
    }

public:
    bool IsUIOpen() { return m_bOpen; }
    void UIOpen(); 
    void UIClose();
    void SetClose() { m_bOpen = false; }

public:
    virtual void MouseLbtnDown() { m_bLbtnDown = true; }

    virtual void MouseLbtnClicked() {};

    virtual void MouseOn() {};

    virtual void SetCsrState(CSRSTATE _csrstate);

private:
    void MouseOnCheck();

public:
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _other);
    ~CUI();

    friend class CUIMgr;
};

