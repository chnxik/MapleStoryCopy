#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_iCallCount(0)
	, m_fDT(0.f)
	, m_fTime(0.f)
	, _szDebug{}
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	// tick 간격 시간
	m_fDT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;
	
	if (0.01f < m_fDT)
		m_fDT = 0.01f;

	// 누적 시간
	m_fTime += m_fDT;

	// 함수 호출 횟수
	++m_iCallCount;

	// 이전 카운트 값을 현재 카운트로 갱신
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		RECT rt = { (LONG)(10),
					(LONG)(10),
					(LONG)(300),
					(LONG)(100) };	// 문자가 써질 사각형

		// 1초에 한번
		if (1.f <= m_fTime)
		{
			swprintf_s(_szDebug, L"FPS : %d\nDT : %f", m_iCallCount, m_fDT);

			m_fTime = 0.f;
			m_iCallCount = 0;
		}
		SetTextColor(_dc, RGB(0, 0, 0));

		SetBkMode(_dc, TRANSPARENT);				// 문자 배경 투명 설정
		DrawText(_dc, _szDebug, -1, &rt, DT_LEFT);	// 문자 출력
	}
}
