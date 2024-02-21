#include "pch.h"
#include "CExpGaugeUI.h"

#include "CTimeMgr.h"

#include "CTexture.h"
#include "CNum.h"

CExpGaugeUI::CExpGaugeUI()
	: m_fMaxValue(1)
	, m_fPrevValue(1)
	, m_fCurValue(1)
	, m_fUpdateValue(1)
	, m_fRatio(0.f)
	, m_arrVal{}
{
}

CExpGaugeUI::~CExpGaugeUI()
{
}

void CExpGaugeUI::Numinit()
{
	Vec2 vCenterPos = GetScale() / 2.f;
	Vec2 vPos = vCenterPos;
	vPos.y = vCenterPos.y - 4.5f;

	CNum* pPercent = new CNum;
	pPercent->SetScale(Vec2(9, 9));
	pPercent->SetStatTex();
	pPercent->SetPos(Vec2(vPos.x + 9.f, vPos.y));
	pPercent->SetPrint(true);
	pPercent->SetNum(11);
	AddChildUI(pPercent);

	for (int i = 0; i < 3; ++i)
	{
		m_arrVal[i] = new CNum;
		m_arrVal[i]->SetStatTex();
		m_arrVal[i]->SetScale(Vec2(7, 9));
		vPos.x = vCenterPos.x - (7 * i);
		m_arrVal[i]->SetPos(vPos);
		AddChildUI(m_arrVal[i]);
	}
}

void CExpGaugeUI::SetValueNum()
{
	int iVal = (UINT)(m_fRatio * 100.f);

	for (int i = 0; i < 3; ++i)
	{
		if (iVal == 0)
		{
			if (i == 0)
			{
				m_arrVal[i]->SetPrint(true);
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
}

void CExpGaugeUI::tick()
{
	// ���� ������ ������Ʈ ������ ũ��, 1�ʿ� ���ļ� �����.

	if (m_fCurValue != m_fUpdateValue)
	{
		float iVariation = m_fUpdateValue - m_fPrevValue;
		m_fCurValue += (iVariation * 3 * DT);

		if (m_fUpdateValue > m_fPrevValue) // ����
		{
			if (m_fCurValue >= m_fUpdateValue)
			{
				m_fCurValue = m_fUpdateValue;
				m_fPrevValue = m_fUpdateValue;
			}
		}
		else if (m_fUpdateValue < m_fPrevValue) // ����
		{
			if (m_fCurValue <= m_fUpdateValue)
			{
				m_fCurValue = m_fUpdateValue;
				m_fPrevValue = m_fUpdateValue;
			}
		}
	}


	m_fRatio = m_fCurValue / m_fMaxValue;
	
	SetValueNum();

	CUI::tick();
}

void CExpGaugeUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	CTexture* m_pTex = GetIdleTex();
	 
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = 255;

	float Gauge = m_pTex->Width() * m_fRatio;

	AlphaBlend(_dc							// ������ DC -> ���İ��� ����Ǿ�� �ϹǷ� ���� DC�� �����صд�.
		, (int)vPos.x, (int)vPos.y			// ������ â ������ ��� ������ġ X,Y
		, (int)Gauge						// ����� ���� ũ��
		, m_pTex->Height()					// ����� ���� ũ��
		, m_pTex->GetDC()					// ������ DC
		, 0, 0								// ������ ����� ������ġ x,y 
		, m_pTex->Width()					// ������ ���� ����
		, m_pTex->Height()					// ������ ���� ����
		, tBlend);

	CUI::render_childUI(_dc);
}

