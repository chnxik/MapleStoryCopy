#include "pch.h"
#include "CGaugeUI.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CNum.h"

CGaugeUI::CGaugeUI()
	: m_fMaxValue(1)
	, m_fPrevValue(1)
	, m_fCurValue(1)
	, m_fUpdateValue(1)
	, m_fRatio(0.f)
	, m_arrVal{}
	, m_arrMaxVal{}
{
}

CGaugeUI::~CGaugeUI()
{
}

void CGaugeUI::Numinit()
{
	Vec2 vCenterPos = GetScale() / 2;
	Vec2 vPos = vCenterPos;
	vPos.y = vCenterPos.y - 4.5f;

	CNum* pSlash = new CNum;
	pSlash->SetStatTex();
	pSlash->SetScale(Vec2(6, 10));
	pSlash->SetPos(Vec2(vPos.x - 3.f, vPos.y - 0.5f));
	pSlash->SetPrint(true);
	pSlash->SetNum(10);
	AddChildUI(pSlash);

	for (int i = 0; i < 5; ++i)
	{
		m_arrVal[i] = new CNum;
		m_arrVal[i]->SetStatTex();
		m_arrVal[i]->SetScale(Vec2(7, 9));
		vPos.x = vCenterPos.x - (7 * i) - 12;
		m_arrVal[i]->SetPos(vPos);
		
		AddChildUI(m_arrVal[i]);

		m_arrMaxVal[i] = new CNum;
		m_arrMaxVal[i]->SetStatTex();
		m_arrMaxVal[i]->SetScale(Vec2(7, 9));
		vPos.x = vCenterPos.x + (7 * i) + 6;
		m_arrMaxVal[i]->SetPos(vPos);
		AddChildUI(m_arrMaxVal[i]);
	}
}

void CGaugeUI::SetValueNum()
{
	int iMaxVal = (UINT)m_fMaxValue;
	int iVal = (UINT)m_fUpdateValue;
	int iMaxValLen = iMaxVal;
	int iMaxValCnt = 0;

	while (iMaxValLen)
	{
		iMaxValLen /= 10;
		++iMaxValCnt;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (iVal == 0)
		{
			if (i == 0)
			{
				m_arrVal[i]->SetNum(0);
				continue;
			}
			m_arrVal[i]->SetPrint(false);
		}
		else
		{
			m_arrVal[i]->SetPrint(true);
			m_arrVal[i]->SetNum(iVal % 10);
			iVal /= 10;
		}
	}

	for (int i = 4; i >= 0; --i)
	{
		if (iMaxValCnt - 1 < i)
			m_arrMaxVal[i]->SetPrint(false);
		else
		{
			m_arrMaxVal[i]->SetPrint(true);
			m_arrMaxVal[i]->SetNum(iMaxVal % 10);
			iMaxVal /= 10;
		}
	}
}

void CGaugeUI::tick()
{
	// 현재 값보다 업데이트 벨류가 크면, 1초에 걸쳐서 맞춘다.

	if (m_fCurValue != m_fUpdateValue)
	{
		float iVariation = m_fUpdateValue - m_fPrevValue;
		m_fCurValue += (iVariation * 3 * DT);

		if (m_fUpdateValue > m_fPrevValue) // 증가
		{
			if (m_fCurValue >= m_fUpdateValue)
			{
				m_fCurValue = m_fUpdateValue;
				m_fPrevValue = m_fUpdateValue;
			}
		}
		else if (m_fUpdateValue < m_fPrevValue) // 감소
		{
			if (m_fCurValue <= m_fUpdateValue)
			{
				m_fCurValue = m_fUpdateValue;
				m_fPrevValue = m_fUpdateValue;
			}
		}
	} 

	SetValueNum();

	m_fRatio = m_fCurValue / m_fMaxValue;
	
	CUI::tick();
}

void CGaugeUI::render(HDC _dc) 
{
	Vec2 vPos = GetFinalPos();
	CTexture* m_pTex = GetIdleTex();

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = 255;

	float Gauge = m_pTex->Width() * m_fRatio;

	AlphaBlend(_dc							// 복사할 DC -> 알파값이 적용되어야 하므로 알파 DC에 복사해둔다.
		, (int)vPos.x, (int)vPos.y			// 윈도우 창 내에서 출력 시작위치 X,Y
		, (int)Gauge						// 출력할 가로 크기
		, m_pTex->Height()					// 출력할 세로 크기
		, m_pTex->GetDC()					// 복사할 DC
		, 0, 0								// 복사할 대상의 시작위치 x,y 
		, m_pTex->Width()					// 복사할 가로 범위
		, m_pTex->Height()					// 복사할 세로 범위
		, tBlend);	

	CUI::render_childUI(_dc);
}											

