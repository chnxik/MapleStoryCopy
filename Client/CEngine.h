#pragma once

class CTexture;

class CEngine
{
	SINGLE(CEngine);

private:
	HWND		m_hMainWnd;
	HDC			m_hDC;
	POINT		m_ptResolution;
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];
	HFONT		m_arrFont[(UINT)FONT_TYPE::END];

	CTexture*	m_pMemTex;

public:
	inline HWND GetMainWnd() { return m_hMainWnd; }
	inline HDC GetMainDC() { return m_hDC; }
	inline HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	inline HFONT GetFONT(FONT_TYPE _type) { return m_arrFont[(UINT)_type]; }
	inline POINT GetResolution() { return m_ptResolution; }

	void ChangeWindowSize(UINT _iWidth, UINT _iHeight);

public:
	void init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();
	void render();
	void CreatePenBrush();
	void CreateMyFont();
};

