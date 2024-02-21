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
	// ���̵� ȿ���� ���� BlindTex ����
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

	// ȭ���� ���߾� ����
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	vResolution /= 2.f;
	
	// ���� ������ �ִ� ���´�.
	if (pCurLevel)
	{
		CToolLevel* ToolLevelCheck = dynamic_cast<CToolLevel*>(pCurLevel);


		
		// ī�޶� ������ ȿ��
		CameraEffect();

		if (ToolLevelCheck && (nullptr == m_pTarget))
		{
			// ���� Tool Level �̰� �÷��̾�Ÿ���� ������ wasd�� ī�޶� ���� ����
			if (ISHOLD(KEY::W))
				m_vLook.y -= 500.f * DT;
			if (ISHOLD(KEY::S))
				m_vLook.y += 500.f * DT;
			if (ISHOLD(KEY::A))
				m_vLook.x -= 500.f * DT;
			if (ISHOLD(KEY::D))
				m_vLook.x += 500.f * DT;
		}
		
		// ���� ������ Ÿ���� �ְ� Ȱ��ȭ ���¸� �Ѿư���.
		else if (IsValid(m_pTarget))
		{
			Vec2 ForTargetDir = m_pTarget->GetPos() - m_vLook;
			float fdist = ForTargetDir.Length();
			ForTargetDir.Normalize();

			Vec2 vAccel = {};	// ī�޶� ���ӵ�
			float fFrictionScale = 1/fdist; // �������

			// ���� �Ÿ� �̻��϶� Ÿ�� �������� ī�޶� ���� �ش�.
			if (fdist > 10.f)
				vAccel = ForTargetDir * 500.f;

			// ���ӵ��� �̿��� �ӵ��� ������Ŵ
			m_vVelocity = vAccel;


			Vec2 vFriction = -m_vVelocity; // ī�޶� ���� ���ӵ�
			
			if (!vFriction.IsZero()) // �������ӵ��� 0�� �ƴѰ�� ����ȭ���� ���Ⱚ�� ���� ���� ��������� ���� �̹��������� �ӵ����ҷ��� ����Ѵ�.
			{
				vFriction.Normalize();
				vFriction *= m_fFriction * fFrictionScale * DT;
			}

			// �ӵ����ҷ��� ���� �ӵ��� �Ѿ ��� 0���� ����� ������Ų��.
			if (m_vVelocity.Length() <= vFriction.Length())
			{
				m_vVelocity = Vec2(0.f, 0.f);
			}
			else
			{
				m_vVelocity += vFriction ; // ���� �ӵ� �ݴ�������� ������ ���� �ӵ�����.
			}

			// ī�޶� �ӵ� ����
			if (m_fVelocityLimit < m_vVelocity.Length())
			{
				m_vVelocity.Normalize();
				m_vVelocity *= m_fVelocityLimit;
			}

			m_vLook += m_vVelocity * DT; // ī�޶� �Կ� ������ �ӵ���ŭ �̵���Ų��.
		}
	}

	SetSafyArea(pCurMap, vResolution);

	// render ��ǥ�� ���� ���̰� ���
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
	// ī�޶� �������� Map ������ ���� ó��
	if (_pCurMap)
	{
		Vec2 vMapPos = _pCurMap->GetPos();
		Vec2 vMapScale = _pCurMap->GetScale();

		// ī�޶� �Կ����� ���� ����
		RECT RngOfMotionCmrRt = { (LONG)(vMapPos.x + vResolution.x) , (LONG)(vMapPos.y + vResolution.y), (LONG)(vMapPos.x + vMapScale.x - vResolution.x), (LONG)(vMapPos.y + vMapScale.y - vResolution.y) };

		// �� ����ũ�Ⱑ ȭ�麸�� ŭ
		if (vMapScale.x >= (vResolution.x * 2))
		{
			// ȭ���� ���� �� ��輱�� �������
			if (m_vLook.x < (float)RngOfMotionCmrRt.left)
				m_vLook.x = (float)RngOfMotionCmrRt.left;

			// ȭ���� ������ �� ��輱�� �������
			if (m_vLook.x > (float)RngOfMotionCmrRt.right)
				m_vLook.x = (float)RngOfMotionCmrRt.right;
		}
		else if (vMapScale.x < (vResolution.x * 2))
		{
			m_vLook.x = (vMapPos.x + vMapScale.x) / 2;
		}

		// �� ����ũ�Ⱑ ȭ�麸�� ŭ
		if (vMapScale.y >= (vResolution.y * 2))
		{
			// ȭ���� ���� �� ��輱�� ����� ��
			if (m_vLook.y < (float)RngOfMotionCmrRt.top)
				m_vLook.y = (float)RngOfMotionCmrRt.top;

			// ȭ���� �Ʒ��� ��輱�� ����� ��
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