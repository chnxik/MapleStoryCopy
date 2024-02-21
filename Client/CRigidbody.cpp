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
	Vec2 vAccel = m_vForce / m_fMass;		// ������ ���� ���Է� ���ӵ��� ���Ѵ�.
	m_vVelocity += vAccel * DT;				// ���ӵ��� �̿��ؼ� �ӵ��� ������Ŵ


	// ���� ���� ��
	if (m_bGround)
	{
		m_fFrictionScale = 1.f;
		
		Vec2 vSlope = m_vGrndDir;


		if (m_vVelocity.x < 0)
			vSlope *= -1.f;

		m_vVelocity = vSlope * (m_vVelocity.Length());

		// ���� ���ӵ�
		Vec2 vFriction = -m_vVelocity;

		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= m_fFriction * m_fFrictionScale * m_fMass * DT;
		}

		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			m_vVelocity += vFriction;
		}
	}

	// ���� ����
	if (!m_bGround)
	{
		// ���⸶����
		m_fFrictionScale = 0.1f;
		Vec2 vFriction = -m_vVelocity;

		if (!vFriction.IsZero())
		{
			vFriction.Normalize();
			vFriction *= (m_fFriction * m_fFrictionScale * m_fMass * DT);
		}

		// �ӵ� ���ҷ�(�����¿� ����) �� ���� �ӵ��� �Ѿ� �� ���, ���� ���η� �����.
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			m_vVelocity += vFriction;
		}

		// �߷°��ӵ�
		Vec2 vGravityAccel = Vec2(0.f, m_fGravityAccel);
		m_vVelocity += vGravityAccel * DT;
	}


	// �ӵ� ���� ����(��, ��)
	if (m_fVelocityLimit < fabsf(m_vVelocity.x))
	{
  		m_vVelocity.x = (m_vVelocity.x / fabsf(m_vVelocity.x)) * m_fVelocityLimit;
	}

	if (m_fGravityVLimit < fabsf(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / fabsf(m_vVelocity.y)) * m_fGravityVLimit;
	}

	// Actor�� ��ġ
	Vec2 vPos = GetOwner()->GetPos();

	// �ӵ�(�ӷ� + ����) �� �°� ��ü�� �̵���Ű��
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