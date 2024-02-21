#include "pch.h"
#include "Mob_Priestmem.h"

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

Mob_Priestmem::Mob_Priestmem(CSpawner* _pSpawner)
	: CMob(_pSpawner)
	, m_fAcc(0.f)
	, m_iMoveDist(0)
{
	init();
	SetAnimator();
}

Mob_Priestmem::~Mob_Priestmem()
{
}

void Mob_Priestmem::init()
{
	CreateAnimator();
	CreateCollider();
	CreateRigidbody();
	CreateState();

	SetCmrAfctd(true);
	SetDir(eDir::LEFT);

	SetScale(Vec2(67, 186));
	SetPos(GetSpawner()->GetPos());
	GetCollider()->SetScale(GetScale());

	GetRigidbody()->SetFriction(1000.f);
	GetRigidbody()->SetVelocityLimit(50.f);

	// ½ºÅÈ ¼³Á¤
	tStatus tStatus;
	tStatus.Lv = 30;
	tStatus.MaxExp = 0;
	tStatus.Exp = 300;
	tStatus.MaxHP = 200000;
	tStatus.HP = tStatus.MaxHP;
	tStatus.MaxMP = 0;
	tStatus.MP = tStatus.MaxMP;
	tStatus.MAXATK = 500;
	tStatus.MINATK = 450;
	tStatus.DEF = 300;

	SetStatus(tStatus);

	SetHitSound(CResMgr::GetInst()->LoadSound(L"priest_hit", L"sound\\mob\\priest\\hit.wav"));
	GetHitSound()->SetVolume(MOBVOLUME);
	SetDeadSound(CResMgr::GetInst()->LoadSound(L"priest_die", L"sound\\mob\\priest\\die.wav"));
	GetDeadSound()->SetVolume(MOBVOLUME);
}

void Mob_Priestmem::SetAnimator()
{
	GetAnimator()->CreateAnimation(L"priestmem_stand_l");
	GetAnimator()->CreateAnimation(L"priestmem_stand_r");
	GetAnimator()->CreateAnimation(L"priestmem_walk_l");
	GetAnimator()->CreateAnimation(L"priestmem_walk_r");
	GetAnimator()->CreateAnimation(L"priestmem_hit_l");
	GetAnimator()->CreateAnimation(L"priestmem_hit_r");
	GetAnimator()->CreateAnimation(L"priestmem_die_l");
	GetAnimator()->CreateAnimation(L"priestmem_die_r");

}

void Mob_Priestmem::render(HDC _dc)
{
	CActor::render(_dc);
}

void Mob_Priestmem::Idle()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"priestmem_stand_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"priestmem_stand_r", true);
		break;
	}
}

void Mob_Priestmem::Walk()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"priestmem_walk_l", true);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"priestmem_walk_r", true);
		break;
	}
}

float Mob_Priestmem::Dead()
{
	switch (GetDir())
	{
	case eDir::LEFT:
		GetAnimator()->Play(L"priestmem_die_l", false);
		break;
	case eDir::RIGHT:
		GetAnimator()->Play(L"priestmem_die_r", false);
		break;
	}

	if (50 < rand() % 100)
		CItemMgr::GetInst()->CreateItem(ITEM_TYPE::ELIXIR, this);

	return 1.2f;
}

void Mob_Priestmem::Alert()
{
}

void Mob_Priestmem::Spawn(UINT _iOpacity)
{
	GetAnimator()->Play(L"priestmem_walk_l", true, _iOpacity);
}

float Mob_Priestmem::Damaged()
{
	switch (GetDir())
	{
	case eDir::LEFT:
	{
		GetRigidbody()->SetVelocity(Vec2(-2000.f, 0.f));
		GetAnimator()->Play(L"priestmem_hit_r", true);
	}
	break;
	case eDir::RIGHT:
	{
		GetRigidbody()->SetVelocity(Vec2(2000.f, 0.f));
		GetAnimator()->Play(L"priestmem_hit_l", true);
	}
	break;
	}

	return 0.8f;
}