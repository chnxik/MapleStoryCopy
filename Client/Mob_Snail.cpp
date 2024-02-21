#include "pch.h"
#include "Mob_Snail.h"

#include "CTimeMgr.h"
#include "CBattleMgr.h"
#include "CResMgr.h"
#include "CItemMgr.h"

#include "CAnimator.h"
#include "CRigidbody.h"
#include "CCollider.h"
#include "CSound.h"

#include "CSkill.h"
#include "CPlayer.h"

#include "CSpawner.h"

Mob_Snail::Mob_Snail(CSpawner* _pSpawner)
	: CMob(_pSpawner)
	, m_fAcc(0.f)
	, m_iMoveDist(0)
{
	init();
	SetAnimator();
}

Mob_Snail::~Mob_Snail()
{
}

void Mob_Snail::init()
{
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	CreateState();
	
	SetCmrAfctd(true);
	SetDir(eDir::LEFT);

	SetScale(Vec2(37, 26));
	SetPos(GetSpawner()->GetPos());
	GetCollider()->SetScale(GetScale());

	GetRigidbody()->SetFriction(1000.f);
	GetRigidbody()->SetVelocityLimit(50.f);

	// ½ºÅÈ ¼³Á¤
	tStatus tStatus;
	tStatus.Lv = 1;
	tStatus.MaxExp = 0;
	tStatus.Exp = 3;
	tStatus.MaxHP = 150;
	tStatus.HP = tStatus.MaxHP;
	tStatus.MaxMP = 0;
	tStatus.MP = tStatus.MaxMP;
	tStatus.MAXATK = 10;
	tStatus.MINATK = 1;
	tStatus.DEF = 1;

	SetStatus(tStatus);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"snail_hit", L"sound\\mob\\snail\\hit.wav"));
	SetDeadSound(CResMgr::GetInst()->LoadSound(L"snail_die", L"sound\\mob\\snail\\die.wav"));
	GetHitSound()->SetVolume(MOBVOLUME);
	GetDeadSound()->SetVolume(MOBVOLUME);
}

void Mob_Snail::SetAnimator()
{
	GetAnimator()->CreateAnimation(L"snail_idle_l");
	GetAnimator()->CreateAnimation(L"snail_idle_r");
	GetAnimator()->CreateAnimation(L"snail_walk_l");
	GetAnimator()->CreateAnimation(L"snail_walk_r");
	GetAnimator()->CreateAnimation(L"snail_hit_l");
	GetAnimator()->CreateAnimation(L"snail_hit_r");
	GetAnimator()->CreateAnimation(L"snail_die_l");
	GetAnimator()->CreateAnimation(L"snail_die_r");

}

void Mob_Snail::render(HDC _dc)
{
	CActor::render(_dc);
}

void Mob_Snail::Idle()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"snail_idle_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"snail_idle_r", true);
		break;
	}
}

void Mob_Snail::Walk()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"snail_walk_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"snail_walk_r", true);
		break;
	}
}

float Mob_Snail::Dead()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"snail_die_l", false);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"snail_die_r", false);
		break;
	}

	if (70 < rand() % 100)
		CItemMgr::GetInst()->CreateItem(ITEM_TYPE::REDPOTION, this);

	return 1.5f;
}

void Mob_Snail::Alert()
{
}

void Mob_Snail::Spawn(UINT _iOpacity)
{
	GetAnimator()->Play(L"snail_walk_l", true, _iOpacity);
}

float Mob_Snail::Damaged()
{
	switch (GetDir())
	{
	case eDir::LEFT:
	{
		GetRigidbody()->SetVelocity(Vec2(-2000.f, 0.f));
		GetAnimator()->Play(L"snail_hit_r", true);
	}
		break;
	case eDir::RIGHT:
	{
		GetRigidbody()->SetVelocity(Vec2(2000.f, 0.f));
		GetAnimator()->Play(L"snail_hit_l", true);
	}
		break;
	}

	return 0.8f;
}