#include "pch.h"
#include "CCollider.h"

#include "CTimeMgr.h"

#include "CEngine.h"
#include "CActor.h"
#include "CPlatform.h"
#include "CRigidbody.h"


CCollider::CCollider(CActor* _pOwner)
	: CComponent(_pOwner)
	, m_iOverlapCount(0)
	, m_iPlatformCnt(0)
	, m_vGrndPos{}
{
}

CCollider::CCollider(const CCollider& _other)
	: CComponent(nullptr)
	, m_vOffsetPos(_other.m_vOffsetPos)
	, m_vScale(_other.m_vScale)
	, m_iOverlapCount(0)
	, m_iPlatformCnt(0)
	, m_vGrndPos{}
{
}

CCollider::~CCollider()
{
}

void CCollider::tick()
{
	// 중첩수가 음수인 경우
	assert(!(m_iOverlapCount < 0));
	assert(!(m_iPlatformCnt < 0));
}

void CCollider::final_tick()
{
	// 충돌체의 최종 위치값을 결정한다.
	m_vFinalPos = GetOwner()->GetPos() + m_vOffsetPos;
	m_vGrndPos = { m_vFinalPos.x,m_vFinalPos.y + (m_vScale.y / 2.f) };
}

void CCollider::render(HDC _dc)
{
	// 충돌체를 그린다.
	// 필요한 펜과 브러시를 만든다(또는 가져온다)	
	
	if (CDebug::GetInst()->IsDebugOn())
	{
		HPEN hPen = nullptr;

		if (0 < m_iOverlapCount)
		{
			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::RED);
		}
		else
		{
			hPen = CEngine::GetInst()->GetPen(PEN_TYPE::GREEN);
		}

		HBRUSH hNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

		// DC 의 기존 펜과 브러시를 새로 가져온 것들로 대체한다
		HPEN hOriginPen = (HPEN)SelectObject(_dc, hPen);
		HBRUSH hOriginBrush = (HBRUSH)SelectObject(_dc, hNullBrush);

		Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vFinalPos);

		// 콜라이더 범위 사각형 그리기
		Rectangle(_dc, (int)(vPos.x - m_vScale.x / 2.f)
			, (int)(vPos.y - m_vScale.y / 2.f)
			, (int)(vPos.x + m_vScale.x / 2.f)
			, (int)(vPos.y + m_vScale.y / 2.f));

		Vec2 vGrndPos = CCamera::GetInst()->GetRenderPos(m_vGrndPos);

		Ellipse(_dc, (int)(vGrndPos.x - 2.f)
			, (int)(vGrndPos.y - 2.f)
			, (int)(vGrndPos.x + 2.f)
			, (int)(vGrndPos.y + 2.f));

		// DC 의 GDI 오브젝트들을 기존의 펜과 브러시로 되돌린다.
		SelectObject(_dc, hOriginPen);
		SelectObject(_dc, hOriginBrush);
	}
}

void CCollider::BeginOverlap(CCollider* _pOther)
{
	++m_iOverlapCount;

	GetOwner()->BeginOverlap(_pOther);
}

void CCollider::OnOverlap(CCollider* _pOther)
{

	GetOwner()->OnOverlap(_pOther);
}

void CCollider::EndOverlap(CCollider* _pOther)
{
	--m_iOverlapCount;
	
	GetOwner()->EndOverlap(_pOther);
}