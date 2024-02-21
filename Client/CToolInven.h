#pragma once
#include "CUI.h"

class CTab;
class CToolCell;
class CToolLevel;

class CToolInven :
    public CUI
{
private:
    CToolLevel* m_pToolLevel;
    CTab* m_pToolMod[(UINT)TOOL_TAP::END]; // 선택된 탭
    CToolCell* m_arrCell[20];
    TOOL_TAP m_eCurMode;                   // 현재 모드
    CToolCell* m_pCurCell;                // 선택된 셀

public:
    void CreateBtn();
    void CreateCell();
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void MouseLbtnDown() override;
    virtual void MouseLbtnClicked() override;
    virtual void MouseOn() override;
    
    void SetTool();

    void SetCurMode(TOOL_TAP _Mod);
    void SelectCell(CToolCell* _Cell);

    TOOL_TAP GetCurMode() { return m_eCurMode; }

public:
    CToolInven(CToolLevel* _pLevel);
    ~CToolInven();
};

