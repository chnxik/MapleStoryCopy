#pragma once

class CCursor;

class CCsrMgr
{
	SINGLE(CCsrMgr);
private:
	CCursor*	m_pCursor;		// 커서 객체
	CSRSTATE	m_eCsrState;	// 커서 상태
	UINT		m_iCsrOnCnt;	// 마우스에 겹친 UI 수 

public:
	void AddCsrOnCnt() { ++m_iCsrOnCnt; }
	void SubCsrOnCnt() { if(0 != m_iCsrOnCnt) --m_iCsrOnCnt; }

	const UINT& GetCsrOnCnt() { return m_iCsrOnCnt; }
	
	void SetCsrState(CSRSTATE _CsrState) { m_eCsrState = _CsrState; }
	CSRSTATE GetCsrState() { return m_eCsrState; }

	CCursor* GetCsr() { return m_pCursor; }

	void SetItemCsr(CTexture* _pTex,Vec2 _Offset);

public:
	void init();
	void tick();
	void render(HDC _dc);
};