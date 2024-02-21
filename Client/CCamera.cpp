#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"

#include "CTexture.h"

#include "CToolLevel.h"
#include "CMap.h"


CCamera::CCamera()
	: m_pBlindTex(nullptr)
	, m_fRatio(0.f)
	, m_vOffset{}
	, m_pTarget(nullptr)
	, m_vVelocity{}
	, m_fFriction(900.f)
	, m_fShakeRatio(0.f)
	, m_fVelocityLimit(500.f)
{
	// 페이드 효과를 위한 BlindTex 생성
	POINT ptResolution = CEngine::GetInst()->GetResolution();
	m_pBlindTex = CResMgr::GetInst()->CreateTexture(L"BlindTex", ptResolution.x, ptResolution.y);
}

CCamera::~CCamera()
{

}

void CCamera::tick()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	CMap* pCurMap = pCurLevel->GetCurMap();

	// 화면의 정중앙 지점
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	
	// 현재 레벨이 있는 상태다.
	if (pCurLevel)
	{
		CToolLevel* ToolLevelCheck = dynamic_cast<CToolLevel*>(pCurLevel);


		
		// 카메라 렌더링 효과
		CameraEffect();

		if (ToolLevelCheck && (nullptr == m_pTarget))
		{
			// 현재 Tool Level 이고 플레이어타겟이 없으면 wasd로 카메라 조작 가능
			if (ISHOLD(KEY::W))
				m_vLook.y -= 500.f * DT;
			if (ISHOLD(KEY::S))
				m_vLook.y += 500.f * DT;
			if (ISHOLD(KEY::A))
				m_vLook.x -= 500.f * DT;
			if (ISHOLD(KEY::D))
				m_vLook.x += 500.f * DT;
		}
		
		// 현재 레벨에 타겟이 있고 활성화 상태면 쫓아간다.
		else if (IsValid(m_pTarget))
		{
			Vec2 ForTargetDir = m_pTarget->GetPos() - m_vLook;
			float fdist = ForTargetDir.Length();
			ForTargetDir.Normalize();

			Vec2 vAccel = {};	// 카메라 가속도
			float fFrictionScale = 1/fdist; // 마찰계수

			// 일정 거리 이상일때 타겟 방향으로 카메라에 힘을 준다.
			if (fdist > 10.f)
				vAccel = ForTargetDir * 500.f;

			// 가속도를 이용해 속도를 증가시킴
			m_vVelocity = vAccel;


			Vec2 vFriction = -m_vVelocity; // 카메라 마찰 가속도
			
			if (!vFriction.IsZero()) // 마찰가속도가 0이 아닌경우 정규화시켜 방향값을 구한 다음 마찰계수를 곱해 이번프레임의 속도감소량을 계산한다.
			{
				vFriction.Normalize();
				vFriction *= m_fFriction * fFrictionScale * DT;
			}

			// 속도감소량이 기존 속도를 넘어설 경우 0으로 만들어 정지시킨다.
			if (m_vVelocity.Length() <= vFriction.Length())
			{
				m_vVelocity = Vec2(0.f, 0.f);
			}
			else
			{
				m_vVelocity += vFriction ; // 현재 속도 반대방향으로 마찰에 의한 속도감소.
			}

			// 카메라 속도 제한
			if (m_fVelocityLimit < m_vVelocity.Length())
			{
				m_vVelocity.Normalize();
				m_vVelocity *= m_fVelocityLimit;
			}

			m_vLook += m_vVelocity * DT; // 카메라 촬영 지점을 속도만큼 이동시킨다.
		}
	}

	SetSafyArea(pCurMap, vResolution);

	// render 좌표를 위한 차이값 계산
	m_vDiff = m_vLook + m_vOffset - vResolution;

}

void CCamera::render(HDC _dc)
{
	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = 0;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * m_fRatio);

	if (m_fRatio < 0.001f)
		return;

	AlphaBlend(_dc
		, 0, 0
		, m_pBlindTex->Width()
		, m_pBlindTex->Height()
		, m_pBlindTex->GetDC()
		, 0, 0
		, m_pBlindTex->Width()
		, m_pBlindTex->Height()
		, tBlend);
}

void CCamera::FadeOut(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_OUT;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}

void CCamera::FadeIn(float _fTerm)
{
	tCamEffect effect = {};
	effect.m_eCurEffect = CAMERA_EFFECT::FADE_IN;
	effect.m_fAccTime = 0.f;
	effect.m_fMaxTime = _fTerm;

	m_CamEffectList.push_back(effect);
}

void CCamera::Shake(float _fTerm)
{
	if (m_CamEffectList.empty())
	{
		tCamEffect effect = {};
			effect.m_eCurEffect = CAMERA_EFFECT::SHAKE;
			effect.m_fAccTime = 0.f;
			effect.m_fMaxTime = _fTerm;

			m_CamEffectList.push_back(effect);
	}
}

void CCamera::SetSafyArea(CMap* _pCurMap, Vec2 vResolution)
{
	// 카메라 가동범위 Map 범위로 제한 처리
	if (_pCurMap)
	{
		Vec2 vMapPos = _pCurMap->GetPos();
		Vec2 vMapScale = _pCurMap->GetScale();

		// 카메라 촬영가능 가동 범위
		RECT RngOfMotionCmrRt = { (LONG)(vMapPos.x + vResolution.x) , (LONG)(vMapPos.y + vResolution.y), (LONG)(vMapPos.x + vMapScale.x - vResolution.x), (LONG)(vMapPos.y + vMapScale.y - vResolution.y) };

		// 맵 가로크기가 화면보다 큼
		if (vMapScale.x >= (vResolution.x * 2))
		{
			// 화면이 왼쪽 맵 경계선을 벗어났을때
			if (m_vLook.x < (float)RngOfMotionCmrRt.left)
				m_vLook.x = (float)RngOfMotionCmrRt.left;

			// 화면이 오른쪽 맵 경계선을 벗어났을때
			if (m_vLook.x > (float)RngOfMotionCmrRt.right)
				m_vLook.x = (float)RngOfMotionCmrRt.right;
		}
		else if (vMapScale.x < (vResolution.x * 2))
		{
			m_vLook.x = (vMapPos.x + vMapScale.x) / 2;
		}

		// 맵 세로크기가 화면보다 큼
		if (vMapScale.y >= (vResolution.y * 2))
		{
			// 화면이 위쪽 맵 경계선을 벗어났을 때
			if (m_vLook.y < (float)RngOfMotionCmrRt.top)
				m_vLook.y = (float)RngOfMotionCmrRt.top;

			// 화면이 아랫쪽 경계선을 벗어났을 때
			if (m_vLook.y > (float)RngOfMotionCmrRt.bottom)
				m_vLook.y = (float)RngOfMotionCmrRt.bottom;
		}
		else if (vMapScale.y < (vResolution.y * 2))
		{
			m_vLook.y = (vMapPos.y + vMapScale.y) / 2;
		}
	}
}

void CCamera::CameraEffect()
{
	if (m_CamEffectList.empty())
		return;

	tCamEffect& effect = m_CamEffectList.front();

	effect.m_fAccTime += DT;

	if (effect.m_fMaxTime <= effect.m_fAccTime)
	{
		m_CamEffectList.pop_front();
		m_fShakeRatio = 0.f;
		return;
	}

	if (CAMERA_EFFECT::SHAKE == effect.m_eCurEffect)
	{
		int x = (rand() % 10 * 2) - 10;
		int y = (rand() % 10 * 2) - 10;
		x = x == 0 ? 1 : x;
		y = y == 0 ? 1 : y;

		m_fShakeRatio = 1.f - effect.m_fAccTime / effect.m_fMaxTime;

		m_vOffset.x = (float)x * m_fShakeRatio;
		m_vOffset.y = (float)y * m_fShakeRatio;
		
		return;
	}

	m_fRatio = effect.m_fAccTime / effect.m_fMaxTime;
	if (CAMERA_EFFECT::FADE_IN == effect.m_eCurEffect)
		m_fRatio = 1.f - m_fRatio;
}