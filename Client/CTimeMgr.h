#pragma once

class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;

	UINT			m_iCallCount;
	float			m_fDT;
	float			m_fTime;

	wchar_t _szDebug[256];

public:
	void init();
	void tick();
	void render(HDC _dc);

public:
	inline float GetDT() { return m_fDT; }
};

