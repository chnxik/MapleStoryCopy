#include "pch.h"
#include "CActor.h"

#include "CEventMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidbody.h"

CActor::CActor()
	: m_vPos{}
	, m_vScale{}
	, m_bDead(false)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_bCmrAfctd(false)
	, m_eDir(eDir::NONE)
{
}

CActor::CActor(const CActor& _other)
	: CEntity(_other)
	, m_vPos(_other.m_vPos)
	, m_vScale(_other.m_vScale)
	, m_bDead(false)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_bCmrAfctd(_other.m_bCmrAfctd)
	, m_eDir(_other.m_eDir)
{
	if (nullptr != _other.m_pCollider)
	{
		m_pCollider = _other.m_pCollider->Clone();
		m_pCollider->SetOwner(this);
	}

	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = _other.m_pAnimator->Clone();
		m_pAnimator->SetOwner(this);
	}

	if (nullptr != _other.m_pRigidbody)
	{
		m_pRigidbody = _other.m_pRigidbody->Clone();
		m_pRigidbody->SetOwner(this);
	}
}

CActor::~CActor()
{
	DEL(m_pCollider);
	DEL(m_pAnimator);
	DEL(m_pRigidbody);
}

void CActor::CreateCollider()
{
	m_pCollider = new CCollider(this);
}

void CActor::CreateAnimator()
{
	m_pAnimator = new CAnimator(this);
}

void CActor::CreateRigidbody()
{
	m_pRigidbody = new CRigidbody(this);
}

void CActor::tick()
{
	if (nullptr != m_pCollider)
		m_pCollider->tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->tick();

	if (nullptr != m_pRigidbody)
		m_pRigidbody->tick();
}

void CActor::final_tick()
{
	if (nullptr != m_pRigidbody)
		m_pRigidbody->final_tick();

	if (nullptr != m_pAnimator)
		m_pAnimator->final_tick();

	if (nullptr != m_pCollider)
		m_pCollider->final_tick();
}

void CActor::render(HDC _dc)
{
	if (nullptr != m_pAnimator)
		m_pAnimator->render(_dc);

	if (nullptr != m_pCollider)
		m_pCollider->render(_dc);
}

void CActor::SetDead()
{
	tEvent evn = {};
	evn.eType = EVENT_TYPE::DELETE_ACTOR;
	evn.wParam = (DWORD_PTR)this;
	CEventMgr::GetInst()->AddEvent(evn);
}