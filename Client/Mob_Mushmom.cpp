#include "pch.h"
#include "Mob_Mushmom.h"

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

Mob_Mushmom::Mob_Mushmom(CSpawner* _pSpawner)
	: CMob(_pSpawner)
	, m_fAcc(0.f)
	, m_iMoveDist(0)
{
	init();
	SetAnimator();
}

Mob_Mushmom::~Mob_Mushmom()
{
}

void Mob_Mushmom::init()
{
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	CreateState();

	SetCmrAfctd(true);
	SetDir(eDir::LEFT);

	SetScale(Vec2(119, 110));
	SetPos(GetSpawner()->GetPos());
	GetCollider()->SetScale(GetScale());

	GetRigidbody()->SetFriction(1000.f);
	GetRigidbody()->SetVelocityLimit(50.f);

	// ½ºÅÈ ¼³Á¤
	tStatus tStatus;
	tStatus.Lv = 10;
	tStatus.MaxExp = 0;
	tStatus.Exp = 50;
	tStatus.MaxHP = 50000;
	tStatus.HP = tStatus.MaxHP;
	tStatus.MaxMP = 0;
	tStatus.MP = tStatus.MaxMP;
	tStatus.MAXATK = 150;
	tStatus.MINATK = 100;
	tStatus.DEF = 50;

	SetStatus(tStatus);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"mushmom_hit", L"sound\\mob\\mushmom\\hit.wav"));
	GetHitSound()->SetVolume(MOBVOLUME);
	SetDeadSound(CResMgr::GetInst()->LoadSound(L"mushmom_die", L"sound\\mob\\mushmom\\die.wav"));
	GetDeadSound()->SetVolume(MOBVOLUME);
}

void Mob_Mushmom::SetAnimator()
{
	GetAnimator()->CreateAnimation(L"mushmom_stand_l");
	GetAnimator()->CreateAnimation(L"mushmom_stand_r");
	GetAnimator()->CreateAnimation(L"mushmom_walk_l");
	GetAnimator()->CreateAnimation(L"mushmom_walk_r");
	GetAnimator()->CreateAnimation(L"mushmom_hit_l");
	GetAnimator()->CreateAnimation(L"mushmom_hit_r");
	GetAnimator()->CreateAnimation(L"mushmom_die_l");
	GetAnimator()->CreateAnimation(L"mushmom_die_r");

}

void Mob_Mushmom::render(HDC _dc)
{
	CActor::render(_dc);
}

void Mob_Mushmom::Idle()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"mushmom_stand_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"mushmom_stand_r", true);
		break;
	}
}

void Mob_Mushmom::Walk()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"mushmom_walk_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"mushmom_walk_r", true);
		break;
	}
}

float Mob_Mushmom::Dead()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"mushmom_die_l", false);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"mushmom_die_r", false);
		break;
	}

	if (70 < rand() % 100)
		CItemMgr::GetInst()->CreateItem(ITEM_TYPE::REDPOTION, this);

	if (70 < rand() % 100)
		CItemMgr::GetInst()->CreateItem(ITEM_TYPE::BLUEPOTION, this);

	return 1.5f;
}

void Mob_Mushmom::Alert()
{
}

void Mob_Mushmom::Spawn(UINT _iOpacity)
{
	GetAnimator()->Play(L"mushmom_walk_l", true, _iOpacity);
}

float Mob_Mushmom::Damaged()
{
	switch (GetDir())
	{
	case eDir::LEFT:
	{
		GetRigidbody()->SetVelocity(Vec2(-2000.f, 0.f));
		GetAnimator()->Play(L"mushmom_hit_r", true);
	}
	break;
	case eDir::RIGHT:
	{
		GetRigidbody()->SetVelocity(Vec2(2000.f, 0.f));
		GetAnimator()->Play(L"mushmom_hit_l", true);
	}
	break;
	}

	return 0.8f;
}