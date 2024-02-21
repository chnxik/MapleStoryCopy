#include "pch.h"
#include "CAnimation.h"

#include "CActor.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CSound.h"

#include "CUI.h"

CAnimation::CAnimation(CAnimator* _pAnimator)
	: m_pAnimator(_pAnimator)
	, m_pAtlas(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
	, m_bFlashing(false)
	, m_pSound(nullptr)
	, m_fOpacity(1.f)
	, m_fScale(-1.5f)
	, m_iOpacityLimit(0.f)
	, m_bStop(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::init(const tAnimInfo* _tAnimInfo)
{
	SetName(_tAnimInfo->strAnimName);																		// �ִϸ��̼� �̸� ����
	m_pAtlas = CResMgr::GetInst()->LoadTexture(_tAnimInfo->strAtlasKey, _tAnimInfo->strAtlasPath);			// ��Ʋ�� �ε�

	if (_tAnimInfo->bUseSound)
		m_pSound = CResMgr::GetInst()->LoadSound(_tAnimInfo->strSoundKey, _tAnimInfo->strSoundPath);		// ���� �ε�

	for (UINT i = 0; i < _tAnimInfo->iFrmCnt; ++i)
	{
		m_vecFrm.push_back(_tAnimInfo->vecFrm[i]);
	}
}

void CAnimation::tick()
{
	if (m_bFinish)
		return;

	if (m_bFlashing)
	{
		m_fOpacity += m_fScale * DT;

		if (1.f <= m_fOpacity)
		{
			m_fScale *= -1.f;
			m_fOpacity -= m_fOpacity - 1.f;
		}
		else if (m_iOpacityLimit > m_fOpacity)
		{
			m_fScale *= -1.f;
			m_fOpacity += m_iOpacityLimit - m_fOpacity;
		}

	}

	
	if (!m_bStop)
	{
		m_fAccTime += DT;

		if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
		{
			++m_iCurFrm;
			m_fAccTime = 0.f;

			if (m_vecFrm.size() <= m_iCurFrm)
			{
				m_iCurFrm = (int)m_vecFrm.size() - 1;
				m_bFinish = true;
			}
		}
	}

	if (nullptr != m_pSound && 1 == m_iCurFrm)
	{
		m_pSound->Play(false);
	}
}

void CAnimation::render(HDC _dc)
{
	CActor* pOwnerAct = m_pAnimator->GetOwner();

	Vec2 vPos = pOwnerAct->GetPos();
	if (dynamic_cast<CUI*>(pOwnerAct))
		vPos = ((CUI*)pOwnerAct)->GetFinalPos();
	 
	
	if (pOwnerAct->IsCmrAfctd())
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	Vec2 vScale = pOwnerAct->GetScale();

	tAnimFrm frm = m_vecFrm[m_iCurFrm];

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;							// �Ϲ� ��Ʈ�� 0, 32��Ʈ ��Ʈ�� AC_SRC_ALPHA
	tBlend.BlendFlags = 0;										// ������ 0
	tBlend.BlendOp = AC_SRC_OVER;								// AC_SRC_OVER
	tBlend.SourceConstantAlpha = (int)(255.f * m_fOpacity);							// ��� ( ���� 0 - ������ 255)

	AlphaBlend(_dc												// ������ DC -> ���İ��� ����Ǿ�� �ϹǷ� ���� DC�� �����صд�.
		, int(vPos.x + frm.vOffset.x - (vScale.x / 2.f))		// ������ â ������ ��� ������ġ X
		, int(vPos.y + frm.vOffset.y - (vScale.y / 2.f))		// ������ â ������ ��� ������ġ Y
		, int(frm.vSize.x)										// ����� ���� ũ��
		, int(frm.vSize.y)										// ����� ���� ũ��
		, m_pAtlas->GetDC()										// ������ DC
		, int(frm.vLeftTop.x)									// ������ ����� ������ġ x
		, int(frm.vLeftTop.y)									// ������ ����� ������ġ y
		, int(frm.vSize.x)										// ������ ���� ����
		, int(frm.vSize.y)										// ������ ���� ����
		, tBlend);
}