#pragma once

class CCursor;

class CCsrMgr
{
	SINGLE(CCsrMgr);
private:
	CCursor*	m_pCursor;		// Ŀ�� ��ü
	CSRSTATE	m_eCsrState;	// Ŀ�� ����
	UINT		m_iCsrOnCnt;	// ���콺�� ��ģ UI �� 

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