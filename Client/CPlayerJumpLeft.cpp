#include "pch.h"
#include "CPlayerJumpLeft.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

#include "DoubleJump.h"

void CPlayerJumpLeft::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISHOLD(KEY::LEFT) && ISHOLD(KEY::RIGHT))
		return;

	if (ISHOLD(KEY::RIGHT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
	}
	if (ISHOLD(KEY::LEFT))
	{
		player->GetRigidbody()->AddForce(Vec2(-800.f, 0.f));
	}
}

void CPlayerJumpLeft::Update(CPlayer* player)
{
	if (player->GetRigidbody()->IsGrnd() == true)
		player->Idle();
}

void CPlayerJumpLeft::Enter(CPlayer* player)
{
	player->SetDir(eDir::LEFT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"jump_l", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"jump_l", true);
}

void CPlayerJumpLeft::Exit(CPlayer* player)
{
}