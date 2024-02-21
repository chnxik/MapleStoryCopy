#include "pch.h"
#include "Mob_BlueSnail.h"

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

Mob_BlueSnail::Mob_BlueSnail(CSpawner* _pSpawner)
	: CMob(_pSpawner)
	, m_fAcc(0.f)
	, m_iMoveDist(0)
{
	init();
	SetAnimator();
}

Mob_BlueSnail::~Mob_BlueSnail()
{
}

void Mob_BlueSnail::init()
{
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	CreateState();

	SetCmrAfctd(true);
	SetDir(eDir::LEFT);

	SetScale(Vec2(35, 34));
	SetPos(GetSpawner()->GetPos());
	GetCollider()->SetScale(GetScale());

	GetRigidbody()->SetFriction(1000.f);
	GetRigidbody()->SetVelocityLimit(50.f);

	// ½ºÅÈ ¼³Á¤
	tStatus tStatus;
	tStatus.Lv = 2;
	tStatus.MaxExp = 0;
	tStatus.Exp = 5;
	tStatus.MaxHP = 200;
	tStatus.HP = tStatus.MaxHP;
	tStatus.MaxMP = 0;
	tStatus.MP = tStatus.MaxMP;
	tStatus.MAXATK = 20;
	tStatus.MINATK = 15;
	tStatus.DEF = 3;

	SetStatus(tStatus);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"snail_hit", L"sound\\mob\\snail\\hit.wav"));
	SetDeadSound(CResMgr::GetInst()->LoadSound(L"snail_die", L"sound\\mob\\snail\\die.wav"));
	GetHitSound()->SetVolume(MOBVOLUME);
	GetDeadSound()->SetVolume(MOBVOLUME);
}

void Mob_BlueSnail::SetAnimator()
{
	GetAnimator()->CreateAnimation(L"bluesnail_idle_l");
	GetAnimator()->CreateAnimation(L"bluesnail_idle_r");
	GetAnimator()->CreateAnimation(L"bluesnail_walk_l");
	GetAnimator()->CreateAnimation(L"bluesnail_walk_r");
	GetAnimator()->CreateAnimation(L"bluesnail_hit_l");
	GetAnimator()->CreateAnimation(L"bluesnail_hit_r");
	GetAnimator()->CreateAnimation(L"bluesnail_die_l");
	GetAnimator()->CreateAnimation(L"bluesnail_die_r");

}

void Mob_BlueSnail::render(HDC _dc)
{
	CActor::render(_dc);
}

void Mob_BlueSnail::Idle()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"bluesnail_idle_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"bluesnail_idle_r", true);
		break;
	}
}

void Mob_BlueSnail::Walk()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"bluesnail_walk_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"bluesnail_walk_r", true);
		break;
	}
}

float Mob_BlueSnail::Dead()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"bluesnail_die_l", false);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"bluesnail_die_r", false);
		break;
	}

	if (70 < rand() % 100)
		CItemMgr::GetInst()->CreateItem(ITEM_TYPE::BLUEPOTION, this);

	return 1.2f;
}

void Mob_BlueSnail::Alert()
{
}

void Mob_BlueSnail::Spawn(UINT _iOpacity)
{
	GetAnimator()->Play(L"bluesnail_walk_l", true, _iOpacity);
}

float Mob_BlueSnail::Damaged()
{
	switch (GetDir())
	{
	case eDir::LEFT:
	{
		GetRigidbody()->SetVelocity(Vec2(-2000.f, 0.f));
		GetAnimator()->Play(L"bluesnail_hit_r", true);
	}
	break;
	case eDir::RIGHT:
	{
		GetRigidbody()->SetVelocity(Vec2(2000.f, 0.f));
		GetAnimator()->Play(L"bluesnail_hit_l", true);
	}
	break;
	}

	return 0.8f;
}