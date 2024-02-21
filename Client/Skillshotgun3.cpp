#include "pch.h"
#include "Skillshotgun3.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CMob.h"


Skillshotgun3::Skillshotgun3(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"cadena_shotgun3_l");
	GetAnimator()->CreateAnimation(L"cadena_shotgun3_r");

	SetTime(0.35f);

	CActor::SetCmrAfctd(true);
}

Skillshotgun3::~Skillshotgun3()
{
}

void Skillshotgun3::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	CSkill::tick();
}

void Skillshotgun3::Active()
{
	Vec2 vScale = Vec2(140, 150);

	CCamera::GetInst()->Shake(0.5f);

	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetAnimator()->Play(L"cadena_shotgun3_l", false);
	}
	else
	{
		GetAnimator()->Play(L"cadena_shotgun3_r", false);
	}
}