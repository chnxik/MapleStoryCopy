#include "pch.h"
#include "CBackgrnd.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"

#include "CLevel.h"
#include "CMap.h"

#include "CTexture.h"

CBackgrnd::CBackgrnd()
	: m_pBgTex(nullptr)
	, m_vTexOffset{}
	, m_iOpacity(210)
{
}

CBackgrnd::~CBackgrnd()
{
}

void CBackgrnd::tick()
{
	Vec2 vlook = CCamera::GetInst()->GetLook();						 // 화명 정 중앙좌표 ( 렌더는 좌, 우로 해상도 반만큼 올려야함)
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CMap* pCurMap = CLevelMgr::GetInst()->GetCurLevel()->GetCurMap();

	if (pCurMap)
	{
		// 현재 보는 지점이 맵의 몇퍼센트 지점인지.
		// texoffset = 텍스쳐 크기 * Look 지점 퍼센트

		Vec2 vMapScale = pCurMap->GetScale();
		m_vTexOffset = (vlook - (vResolution/2.f)) / (vMapScale - (vResolution));
		m_vTexOffset *= Vec2(m_pBgTex->Width() - vResolution.x, m_pBgTex->Height() - vResolution.y);
	}
	else
	{
		m_vTexOffset = { 0, 0 };
	}


	CActor::tick();
}

void CBackgrnd::render(HDC _dc)
{
	// 여기서 Map은 텍스쳐 크기
	// offsetPos = 카메라 look

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (m_pBgTex)
	{
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;					// 일반 비트맵 0, 32비트 비트맵 AC_SRC_ALPHA
		tBlend.BlendFlags = 0;								// 무조건 0
		tBlend.BlendOp = AC_SRC_OVER;						// AC_SRC_OVER
		tBlend.SourceConstantAlpha = m_iOpacity;					// 투명도 ( 투명 0 - 불투명 255)
															
		AlphaBlend(_dc                                      // 복사할 DC -> 알파값이 적용되어야 하므로 알파 DC에 복사해둔다.
			, (int)vPos.x	, (int)vPos.y					// 윈도우 창 내에서 출력 시작위치 X , Y
			, (int)vScale.x	, (int)vScale.y					// 출력할 가로, 세로 크기
			, m_pBgTex->GetDC()								// 복사할 DC
			, (int)m_vTexOffset.x, (int)m_vTexOffset.y		// 복사할 대상의 시작위치 x , y
			, (int)vScale.x, (int)vScale.y					// 복사할 가로, 세로 범위
			, tBlend);										
	}														

	CActor::render(_dc);
}

void CBackgrnd::SetBackGrnd(wstring _strKey, wstring _strRelativePath)
{
	Vec2 vLookPos = CCamera::GetInst()->GetLook();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	m_pBgTex = CResMgr::GetInst()->LoadTexture(_strKey, _strRelativePath);

	if (nullptr != m_pBgTex)
	{
		Vec2 vScale = vResolution;
		SetScale(vScale);
		// 카메라의 좌상단 위치에 배경 포지션을 맞춘다.

		Vec2 vTextureScale = { m_pBgTex->Width(),m_pBgTex->Height() };
		m_vTexOffset = (vTextureScale) / 2 - (vResolution / 2);
	}
}
