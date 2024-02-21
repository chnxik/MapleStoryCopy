#include "pch.h"
#include "Skillbrick4.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CMob.h"


Skillbrick4::Skillbrick4(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();
	CreateCollider();

	GetAnimator()->CreateAnimation(L"cadena_brick4_l");
	GetAnimator()->CreateAnimation(L"cadena_brick4_r");

	SetSound(CResMgr::GetInst()->LoadSound(L"brick2", L"sound\\skill\\brick2.wav"));
	SetHitSound(CResMgr::GetInst()->LoadSound(L"brickhit", L"sound\\skill\\brickhit.wav"));
	GetSound()->SetVolume(SKILLVOLUME);
	GetHitSound()->SetVolume(HITSOUND);

	SetSkillDmg(SKILL::BRICK, 1.8f, 0.2f);
	SetTime(0.56f);
	SetNextActTime(0.56f);
	SetHitDelay(0.07f);

	SetMaxTarget(7);
	SetMaxHitCnt(7);

	CActor::SetCmrAfctd(true);
}

Skillbrick4::~Skillbrick4()
{
}

void Skillbrick4::tick()
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

void Skillbrick4::Active()
{
	Vec2 vScale = Vec2(300, 200);
	GetCollider()->SetScale(vScale);

	switch (GetPlayer()->GetDir())
	{
	case eDir::LEFT:
	{
		GetPlayer()->GetAnimator()->Play(L"NTbricklast_l", false);
		GetAnimator()->Play(L"cadena_brick4_l", false);
	}
		break;
	case eDir::RIGHT:
	{
		GetPlayer()->GetAnimator()->Play(L"NTbricklast_r", false);
		GetAnimator()->Play(L"cadena_brick4_r", false);
	}
		break;
	}
	
	GetSound()->SetPosition(0.f);
	GetSound()->Play(false);
}