#include "pch.h"
#include "Skillshotgun2.h"

#include "CBattleMgr.h"
#include "CCamera.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CMob.h"


Skillshotgun2::Skillshotgun2(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();
	CreateCollider();

	GetAnimator()->CreateAnimation(L"cadena_shotgun2_l");
	GetAnimator()->CreateAnimation(L"cadena_shotgun2_r");

	SetHitSound(CResMgr::GetInst()->LoadSound(L"shotgunhit", L"sound\\skill\\shotgunhit.wav"));
	GetHitSound()->SetVolume(HITSOUND);

	SetSkillDmg(SKILL::SHOTGUN, 1.2f, 0.1f);
	SetTime(1.f);
	SetNextActTime(0.2f);

	SetMaxTarget(6);
	SetMaxHitCnt(7);

	CActor::SetCmrAfctd(true);
}

Skillshotgun2::~Skillshotgun2()
{
}

void Skillshotgun2::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	Vec2 vSkillScale = GetCollider()->GetScale();
	Vec2 voffsetPos = Vec2(vSkillScale.x / 2, 0.f);

	if (GetPlayer()->GetDir() == eDir::LEFT)
		voffsetPos.x -= vSkillScale.x;

	GetCollider()->SetOffsetPos(voffsetPos);

	CSkill::tick();
}

void Skillshotgun2::Active()
{
	Vec2 vScale = Vec2(400, 350);
	GetCollider()->SetScale(vScale);

	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetAnimator()->Play(L"cadena_shotgun2_l", false);
	}
	else
	{
		GetAnimator()->Play(L"cadena_shotgun2_r", false);
	}
}