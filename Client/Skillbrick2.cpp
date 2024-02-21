#include "pch.h"
#include "Skillbrick2.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CMob.h"


Skillbrick2::Skillbrick2(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"cadena_brick2_l");
	GetAnimator()->CreateAnimation(L"cadena_brick2_r");

	SetTime(0.77f);
	SetNextActTime(0.28f);

	CActor::SetCmrAfctd(true);
}

Skillbrick2::~Skillbrick2()
{
}

void Skillbrick2::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	CSkill::tick();
}

void Skillbrick2::Active()
{
	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetAnimator()->Play(L"cadena_brick2_l", false);
	}
	else
	{
		GetAnimator()->Play(L"cadena_brick2_r", false);
	}
}