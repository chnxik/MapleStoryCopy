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

	// tick ���� �ð�
	m_fDT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;
	
	if (0.01f < m_fDT)
		m_fDT = 0.01f;

	// ���� �ð�
	m_fTime += m_fDT;

	// �Լ� ȣ�� Ƚ��
	++m_iCallCount;

	// ���� ī��Ʈ ���� ���� ī��Ʈ�� ����
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::render(HDC _dc)
{
	if (CDebug::GetInst()->IsDebugOn())
	{
		RECT rt = { (LONG)(10),
					(LONG)(10),
					(LONG)(300),
					(LONG)(100) };	// ���ڰ� ���� �簢��

		// 1�ʿ� �ѹ�
		if (1.f <= m_fTime)
		{
			swprintf_s(_szDebug, L"FPS : %d\nDT : %f", m_iCallCount, m_fDT);

			m_fTime = 0.f;
			m_iCallCount = 0;
		}
		SetTextColor(_dc, RGB(0, 0, 0));

		SetBkMode(_dc, TRANSPARENT);				// ���� ��� ���� ����
		DrawText(_dc, _szDebug, -1, &rt, DT_LEFT);	// ���� ���
	}
}
