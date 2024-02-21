#include "pch.h"
#include "SkillStroke.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CPlayer.h"
#include "CMob.h"


SkillStroke::SkillStroke(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();
	CreateCollider();

	GetAnimator()->CreateAnimation(L"cadena_stroke1_l");
	GetAnimator()->CreateAnimation(L"cadena_stroke1_r");
	
	SetSound(CResMgr::GetInst()->LoadSound(L"stroke1", L"sound\\skill\\stroke1.wav"));
	GetSound()->SetVolume(SKILLVOLUME);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"strokehit", L"sound\\skill\\strokehit.wav"));
	GetHitSound()->SetVolume(HITSOUND);

	SetSkillDmg(SKILL::STROKE, 1.2f, 0.1f);
	SetTime(0.3f);

	SetMaxTarget(4);
	SetMaxHitCnt(2);
	
	CActor::SetCmrAfctd(true);
}

SkillStroke::~SkillStroke()
{
}

void SkillStroke::tick()
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

void SkillStroke::Active()
{
	Vec2 vScale = Vec2(140, 150);
	GetCollider()->SetScale(vScale);

	eDir Dir = GetPlayer()->GetDir();

	if (Dir == eDir::LEFT)
	{
		GetPlayer()->GetAnimator()->Play(L"mantis1_l", false);
		GetAnimator()->Play(L"cadena_stroke1_l", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
	else if (Dir == eDir::RIGHT)
	{
		GetPlayer()->GetAnimator()->Play(L"mantis1_r", false);
		GetAnimator()->Play(L"cadena_stroke1_r", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
}