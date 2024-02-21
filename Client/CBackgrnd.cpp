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
	Vec2 vlook = CCamera::GetInst()->GetLook();						 // ȭ�� �� �߾���ǥ ( ������ ��, ��� �ػ� �ݸ�ŭ �÷�����)
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	CMap* pCurMap = CLevelMgr::GetInst()->GetCurLevel()->GetCurMap();

	if (pCurMap)
	{
		// ���� ���� ������ ���� ���ۼ�Ʈ ��������.
		// texoffset = �ؽ��� ũ�� * Look ���� �ۼ�Ʈ

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
	// ���⼭ Map�� �ؽ��� ũ��
	// offsetPos = ī�޶� look

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	if (m_pBgTex)
	{
		BLENDFUNCTION tBlend = {};

		tBlend.AlphaFormat = AC_SRC_ALPHA;					// �Ϲ� ��Ʈ�� 0, 32��Ʈ ��Ʈ�� AC_SRC_ALPHA
		tBlend.BlendFlags = 0;								// ������ 0
		tBlend.BlendOp = AC_SRC_OVER;						// AC_SRC_OVER
		tBlend.SourceConstantAlpha = m_iOpacity;					// ���� ( ���� 0 - ������ 255)
															
		AlphaBlend(_dc                                      // ������ DC -> ���İ��� ����Ǿ�� �ϹǷ� ���� DC�� �����صд�.
			, (int)vPos.x	, (int)vPos.y					// ������ â ������ ��� ������ġ X , Y
			, (int)vScale.x	, (int)vScale.y					// ����� ����, ���� ũ��
			, m_pBgTex->GetDC()								// ������ DC
			, (int)m_vTexOffset.x, (int)m_vTexOffset.y		// ������ ����� ������ġ x , y
			, (int)vScale.x, (int)vScale.y					// ������ ����, ���� ����
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
		// ī�޶��� �»�� ��ġ�� ��� �������� �����.

		Vec2 vTextureScale = { m_pBgTex->Width(),m_pBgTex->Height() };
		m_vTexOffset = (vTextureScale) / 2 - (vResolution / 2);
	}
}
