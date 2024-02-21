#include "pch.h"
#include "CNum.h"

#include "CResMgr.h"

#include "CTexture.h"

CNum::CNum()
	: m_eCurNum(NUMB::_0)
	, m_bPrint(false)
	, m_pNumTex()
{
}

CNum::~CNum()
{
}

void CNum::SetStatTex()
{
	for (int i = 0; i < 10; ++i)
	{
		wchar_t szTexName[256] = {};
		wchar_t szPathbuff[256] = {};
		swprintf_s(szTexName, L"UINumb_%d", i);
		swprintf_s(szPathbuff, L"texture\\UI\\UINum\\%d.png", i);
		m_pNumTex[i] = CResMgr::GetInst()->LoadTexture(szTexName, szPathbuff);
	}
	m_pNumTex[10] = CResMgr::GetInst()->LoadTexture(L"UISlash", L"texture\\UI\\UINum\\slash.png");
	m_pNumTex[11] = CResMgr::GetInst()->LoadTexture(L"UIPercent", L"texture\\UI\\UINum\\percent.png");
}

void CNum::SetItemTex()
{
	for (int i = 0; i < 10; ++i)
	{
		wchar_t szTexName[256] = {};
		wchar_t szPathbuff[256] = {};
		swprintf_s(szTexName, L"ItemNumb_%d", i);
		swprintf_s(szPathbuff, L"texture\\UI\\itemNum\\%d.png", i);
		m_pNumTex[i] = CResMgr::GetInst()->LoadTexture(szTexName, szPathbuff);
	}
}

void CNum::tick()
{
	CUI::tick();
}

void CNum::render(HDC _dc)
{
	if (m_bPrint)
	{
		Vec2 vPos = GetFinalPos();
		CTexture* m_pTex = m_pNumTex[(UINT)m_eCurNum];

		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = 255;

		AlphaBlend(_dc
			, (int)vPos.x, (int)vPos.y
			, m_pTex->Width()
			, m_pTex->Height()
			, m_pTex->GetDC()
			, 0, 0
			, m_pTex->Width()
			, m_pTex->Height()
			, tBlend);
	}
	CUI::render_childUI(_dc);
}
