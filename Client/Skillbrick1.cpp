#include "pch.h"
#include "Skillbrick1.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CMob.h"


Skillbrick1::Skillbrick1(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"cadena_brick1_l");
	GetAnimator()->CreateAnimation(L"cadena_brick1_r");

	SetSound(CResMgr::GetInst()->LoadSound(L"brick1", L"sound\\skill\\brick1.wav"));
	GetSound()->SetVolume(SKILLVOLUME);

	SetTime(0.77f);
	SetNextActTime(0.0f);

	CActor::SetCmrAfctd(true);
}

Skillbrick1::~Skillbrick1()
{
}

void Skillbrick1::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	CSkill::tick();
}

void Skillbrick1::Active()
{
	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetPlayer()->GetAnimator()->Play(L"NTbrick_l", false);
		GetAnimator()->Play(L"cadena_brick1_l", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
	else
	{
		GetPlayer()->GetAnimator()->Play(L"NTbrick_r", false);
		GetAnimator()->Play(L"cadena_brick1_r", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
}