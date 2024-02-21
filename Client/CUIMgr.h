#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)
private:
	CUI* m_pFocusedUI;
	CUI* m_pPriorityUI;


public:
	void tick();

private:
	// 최상위 부모UI 포함, 자식 UI 까지 포함해서 가장 우선순위가 높은 UI 를 찾아낸다.
	CUI* GetPriorityUI(CUI* _pParentUI);

public:
	void CloseUI(CUI* _pParentUI);
	void OpenUI(CUI* _pParentUI);
};