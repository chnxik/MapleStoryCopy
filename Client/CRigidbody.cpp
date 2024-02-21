#include "pch.h"
#include "CRigidbody.h"

#include "CEngine.h"

#include "CCamera.h"

#include "CTimeMgr.h"
#include "CActor.h"


CRigidbody::CRigidbody(CActor* _pOwner)
	: CComponent(_pOwner)
	, m_fMass(1.f)
	, m_fFriction(2000.f)
	, m_fFrictionScale(1.f)
	, m_fVelocityLimit(300.f)
	, m_fGravityVLimit(800.f)
	, m_fGravityAccel(2500.f)
	, m_bGround(false)
	, m_vGrndDir{1,0}
{
}

CRigidbody::CRigidbody(const CRigidbody& _other)
	: CComponent(_other)
	, m_vForce(_other.m_vForce)
	, m_vVelocity(_other.m_vVelocity)
	, m_fMass(_other.m_fMass)
	, m_fFriction(_other.m_fFriction)
	, m_fFrictionScale(_other.m_fFrictionScale)
	, m_fVelocityLimit(_other.m_fVelocityLimit)
	, m_fGravityVLimit(_other.m_fGravityVLimit)
	, m_fGravityAccel(_other.m_fGravityAccel)
	, m_bGround(false)
	, m_vGrndDir{ 1,0 }
{
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::tick()
{

}

void CRigidbody::final_tick()
{
	// F = M x A
	Vec2 vAccel = m_vForce / m_fMass;		// 더해진 힘과 무게로 가속도를 구한다.
	m_vVelocity += vAccel * DT;				// 가속도를 이용해서 속도를 증가시킴


	// 땅에 있을 때
	if (m_bGround)
	{
		m_fFrictionScale = 1.f;
		
		Vec2 vSlope = m_vGrndDir;


		if (m_vVelocity.x < 0)
			vSlope *= -1.f;

		m_vVelocity = vSlope * (m_vVelocity.Length());

		// 마찰 가속도
		Vec2 vFriction = -m_vVelocity;

		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= m_fFriction * m_fFrictionScale * m_fMass * DT;
		}

		// 속도 감소량(마찰력에 의한) 이 기존 속도를 넘어 설 경우, 완전 제로로 만든다.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 현재 속도 반대방향으로 마찰의 의한 속도 감소
			m_vVelocity += vFriction;
		}
	}

	// 공중 상태
	if (!m_bGround)
	{
		// 공기마찰력
		m_fFrictionScale = 0.1f;
		Vec2 vFriction = -m_vVelocity;

		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		// 속도 감소량(마찰력에 의한) 이 기존 속도를 넘어 설 경우, 완전 제로로 만든다.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 현재 속도 반대방향으로 마찰의 의한 속도 감소
			m_vVelocity += vFriction;
		}

		// 중력가속도
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT;
	}


	// 속도 제한 설정(좌, 우)
	if (m_fVelocityLimit < fabsf(m_vVelocity.x))
	{
  		m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
	}

	if (m_fGravityVLimit < fabsf(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
	}

	// Actor의 위치
	Vec2 vPos = GetOwner()->GetPos();

	// 속도(속력 + 방향) 에 맞게 물체를 이동시키며
	vPos.x += m_vVelocity.x * DT;
	vPos.y += m_vVelocity.y * DT;

	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}

void CRigidbody::render(HDC _dc)
{
}

void CRigidbody::SetGrnd(bool _bGround)
{
	m_bGround = _bGround;
	
	if (m_bGround)
	{
		m_vVelocity.y = 0.f;
	}
}