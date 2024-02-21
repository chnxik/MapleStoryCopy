#include "pch.h"
#include "CMap.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CLevelMgr.h"

#include "CTexture.h"
#include "CCamera.h"
#include "CLevel.h"
#include "CToolLevel.h"

#include "CPlatform.h"
#include "Cwall.h"

#include "CDummy.h"

CMap::CMap()
	: m_pMapTex(nullptr)
	, m_pWall{nullptr,nullptr}
{
}

CMap::~CMap()
{
	if (m_pWall[0] != nullptr)
		m_pWall[0]->SetDead();

	if (m_pWall[1] != nullptr)
		m_pWall[1]->SetDead();
}

void CMap::tick()
{
	CActor::tick();
}

void CMap::render(HDC _dc)
{
	if (m_pMapTex)
	{
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;
		tBlend.BlendFlags = 0;
		tBlend.BlendOp = AC_SRC_OVER;
		tBlend.SourceConstantAlpha = 255;

		AlphaBlend(_dc
			, (int)vPos.x, (int)vPos.y
			, m_pMapTex->Width()
			, m_pMapTex->Height()
			, m_pMapTex->GetDC()
			, 0, 0
			, m_pMapTex->Width()
			, m_pMapTex->Height()
			, tBlend);
	}

	CActor::render(_dc);
}

void CMap::SetMap(wstring _strKey, wstring _strRelativePath)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	m_pMapTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);

	if (nullptr != m_pMapTex)
	{
		Vec2 vScale = Vec2((float)m_pMapTex->Width(), (float)m_pMapTex->Height());
		SetScale(vScale);
		SetPos(Vec2(0,0));

		ScreenWallInit();
	}
}

void CMap::ScreenWallInit()
{
	Vec2 vScale = GetScale();

	if (m_pWall[0] != nullptr)
		m_pWall[0]->SetDead();
	
	if (m_pWall[1] != nullptr)
		m_pWall[1]->SetDead();

	m_pWall[0] = new CWall;
	Instantiate(m_pWall[0], LAYER::MAP);

	m_pWall[1] = new CWall;
	Instantiate(m_pWall[1], LAYER::MAP);

	m_pWall[0]->SetWallDir(eDir::LEFT);
	m_pWall[1]->SetWallDir(eDir::RIGHT);
	m_pWall[0]->SetOnlyMob(false);
	m_pWall[1]->SetOnlyMob(false);
		
	m_pWall[0]->SetLine(Vec2(0, 0), Vec2(0.f, vScale.y));
	m_pWall[1]->SetLine(Vec2(vScale.x, 0.f), Vec2(vScale.x, vScale.y));
}
