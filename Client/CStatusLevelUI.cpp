#include "pch.h"
#include "CStatusLevelUI.h"

#include "CTexture.h"

#include "CLvNum.h"

CStatusLevelUI::CStatusLevelUI()
	: m_iLevel(1)
	, m_arrVal{}
{
}

CStatusLevelUI::~CStatusLevelUI()
{
}

void CStatusLevelUI::Numinit()
{
	Vec2 vPos = {15,0};

	for (int i = 2; i >= 0; --i)
	{
		m_arrVal[i] = new CLvNum;
		m_arrVal[i]->SetScale(Vec2(7, 10));
		vPos.x += 7;
		m_arrVal[i]->SetPos(vPos);
		AddChildUI(m_arrVal[i]);
	}
}

void CStatusLevelUI::SetVelueNum()
{
	int iLv = m_iLevel;

	for (int i = 0; i < 3; ++i)
	{
		if (iLv == 0)
		{
			m_arrVal[i]->SetPrint(false);
			continue;
		}
		m_arrVal[i]->SetPrint(true);
		m_arrVal[i]->SetNum(iLv % 10);
		iLv /= 10;
	}
}

void CStatusLevelUI::tick()
{
	SetVelueNum();
	CUI::tick();
}

void CStatusLevelUI::render(HDC _dc)
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