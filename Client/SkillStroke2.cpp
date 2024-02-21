#include "pch.h"
#include "SkillStroke2.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CMob.h"

SkillStroke2::SkillStroke2(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();
	CreateCollider();

	GetAnimator()->CreateAnimation(L"cadena_stroke2_l");
	GetAnimator()->CreateAnimation(L"cadena_stroke2_r");

	SetSound(CResMgr::GetInst()->LoadSound(L"stroke2", L"sound\\skill\\stroke2.wav"));
	GetSound()->SetVolume(SKILLVOLUME);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"strokehit", L"sound\\skill\\strokehit.wav"));
	GetHitSound()->SetVolume(HITSOUND);

	SetSkillDmg(SKILL::STROKE, 1.7f, 0.1f);
	SetTime(0.4f);

	SetMaxTarget(6);
	SetMaxHitCnt(2);

	CActor::SetCmrAfctd(true);
}

SkillStroke2::~SkillStroke2()
{
}

void SkillStroke2::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	Vec2 vSkillScale = GetCollider()->GetScale();
	Vec2 voffsetPos = Vec2(vSkillScale.x / 2, (GetScale().y / 2.f) - (vSkillScale.y / 2.f));

	if (GetPlayer()->GetDir() == eDir::LEFT)
		voffsetPos.x -= vSkillScale.x;

	GetCollider()->SetOffsetPos(voffsetPos);

	CSkill::tick();
}

void SkillStroke2::Active()
{
	Vec2 vScale = Vec2(400, 250);
	GetCollider()->SetScale(vScale);

	Vec2 voffsetPos = Vec2(vScale.x / 2, GetScale().y - vScale.y);
	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetPlayer()->GetAnimator()->Play(L"mantis2_l", false);
		GetAnimator()->Play(L"cadena_stroke2_l", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
	else
	{
		GetPlayer()->GetAnimator()->Play(L"mantis2_r", false);
		GetAnimator()->Play(L"cadena_stroke2_r", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
}