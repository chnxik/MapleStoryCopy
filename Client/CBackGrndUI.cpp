#include "pch.h"
#include "CBackGrndUI.h"

#include "CTexture.h"

CBackGrndUI::CBackGrndUI()
{
}

CBackGrndUI::~CBackGrndUI()
{
}

void CBackGrndUI::tick()
{
	CUI::tick();
}

void CBackGrndUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	CTexture* m_pTex = GetIdleTex();

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
	CUI::render_childUI(_dc);
}

