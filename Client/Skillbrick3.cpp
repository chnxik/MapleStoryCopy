#include "pch.h"
#include "Skillbrick3.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CMob.h"


Skillbrick3::Skillbrick3(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"cadena_brick3_l");
	GetAnimator()->CreateAnimation(L"cadena_brick3_r");

	SetTime(0.63f);
	SetNextActTime(0.35f);

	CActor::SetCmrAfctd(true);
}

Skillbrick3::~Skillbrick3()
{
}

void Skillbrick3::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	CSkill::tick();
}

void Skillbrick3::Active()
{
	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetAnimator()->Play(L"cadena_brick3_l", false);
	}
	else
	{
		GetAnimator()->Play(L"cadena_brick3_r", false);
	}
}