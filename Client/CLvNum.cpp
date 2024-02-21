#include "pch.h"
#include "CLvNum.h"

#include "CResMgr.h"

#include "CTexture.h"

CLvNum::CLvNum()
	: m_eCurNum(NUMB::_0)
	, m_bPrint(false)
	, m_pNumTex()
{
	for (int i = 0; i < 10; ++i)
	{
		wchar_t szTexName[256] = {};
		wchar_t szPathbuff[256] = {};
		swprintf_s(szTexName, L"LvNumb_%d", i);
		swprintf_s(szPathbuff, L"texture\\UI\\Mainbar\\Lvnum\\%d.png", i);
		m_pNumTex[i] = CResMgr::GetInst()->LoadTexture(szTexName, szPathbuff);
	}
}

CLvNum::~CLvNum()
{
}

void CLvNum::tick()
{
	CUI::tick();
}

void CLvNum::render(HDC _dc)
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