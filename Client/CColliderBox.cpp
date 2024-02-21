#include "pch.h"
#include "CColliderBox.h"

#include "CCollider.h"

CColliderBox::CColliderBox(CActor* _pAct)
	: m_pOwnerAct(_pAct)
	, m_bActivate(true)
{
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(m_pOwnerAct->GetScale());
}

CColliderBox::~CColliderBox()
{
}

void CColliderBox::tick()
{

	if (m_bActivate)
	{
		Vec2 vFinalPos = m_pOwnerAct->GetPos();
		vFinalPos.x += m_pOwnerAct->GetScale().x / 2.f;
		if(m_pOwnerAct->GetDir() == eDir::LEFT)
		{
			vFinalPos.x -= GetCollider()->GetScale().x;
		}

		SetPos(vFinalPos);
	}

	CActor::tick();
}

void CColliderBox::render(HDC _dc)
{
	CActor::render(_dc);
}

