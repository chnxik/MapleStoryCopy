#include "pch.h"
#include "CPlayerJumpRight.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

#include "DoubleJump.h"

void CPlayerJumpRight::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISHOLD(KEY::LEFT) && ISHOLD(KEY::RIGHT))
		return;

	if (ISHOLD(KEY::RIGHT))
	{
		player->GetRigidbody()->AddForce(Vec2(800.f, 0.f));
	}
	if (ISHOLD(KEY::LEFT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
	}
}

void CPlayerJumpRight::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == true)
		player->Idle();
}

void CPlayerJumpRight::Enter(CPlayer* player)
{
	player->SetDir(eDir::RIGHT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"jump_r", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"jump_r", true);
}

void CPlayerJumpRight::Exit(CPlayer* player)
{
}