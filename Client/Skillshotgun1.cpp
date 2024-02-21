#include "pch.h"
#include "Skillshotgun1.h"

#include "CBattleMgr.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayer.h"
#include "CMob.h"


Skillshotgun1::Skillshotgun1(CPlayer* pPlayer)
	: CSkill(pPlayer)
{
	SetScale(pPlayer->GetScale());

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"cadena_shotgun1_l");
	GetAnimator()->CreateAnimation(L"cadena_shotgun1_r");

	SetSound(CResMgr::GetInst()->LoadSound(L"shotgun", L"sound\\skill\\shotgun.wav"));
	GetSound()->SetVolume(SKILLVOLUME);

	SetTime(0.2f);

	CActor::SetCmrAfctd(true);
}

Skillshotgun1::~Skillshotgun1()
{
}

void Skillshotgun1::tick()
{
	Vec2 vPos = GetPlayer()->GetPos();
	SetPos(vPos);

	CSkill::tick();
}

void Skillshotgun1::Active()
{
	if (GetPlayer()->GetDir() == eDir::LEFT)
	{
		GetPlayer()->GetAnimator()->Play(L"NTshotgun_l", false);
		GetAnimator()->Play(L"cadena_shotgun1_l", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
	else
	{
		GetPlayer()->GetAnimator()->Play(L"NTshotgun_r", false);
		GetAnimator()->Play(L"cadena_shotgun1_r", false);
		GetSound()->SetPosition(0.f);
		GetSound()->Play(false);
	}
}