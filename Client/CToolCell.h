#pragma once
#include "CUI.h"

class CToolInven;
class CTexture;

class CToolCell :
    public CUI
{
private:
    CToolInven* m_pToolInven;
    const UINT m_CellNumb;
    CTexture*   m_pMobTex; // MOB TAB Texture;
    TOOL_TYPE   m_thisTool[(UINT)TOOL_TAP::END];
    wstring     m_strMobKey;
    bool        m_bSelected;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;

    void SetSelect(bool _b);
    void SetMobTex(CTexture* _pMobTex) { m_pMobTex = _pMobTex; }
    void SetCell(TOOL_TYPE _Tool, wstring _MobName) { m_thisTool[(UINT)TOOL_TAP::OBJ] = _Tool; m_strMobKey = _MobName; }
    void SetCellTool(TOOL_TYPE _Tool) { m_thisTool[(UINT)TOOL_TAP::OBJ] = _Tool; }
    UINT GetCellNumb() { return m_CellNumb; }

    TOOL_TYPE GetCellTool(TOOL_TAP _tapType) { return m_thisTool[(UINT)_tapType]; }

    void SetMobKey(wstring& _MobName) { m_strMobKey = _MobName; }
    wstring GetMobKey() { return m_strMobKey; }

public:
    CToolCell(CToolInven* pToolInven, int m_CellNumb);
    ~CToolCell();
};

