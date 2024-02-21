#include "pch.h"
#include "CPlayerLadder.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CAnimation.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerLadder::KeyInput(CPlayer* player)
{
	if (ISTAP(KEY::UP) || ISTAP(KEY::DOWN))
		player->GetAnimator()->RePlay();
	
	if (ISAWAY(KEY::UP) || ISAWAY(KEY::DOWN))
		player->GetAnimator()->Stop();

	if (ISHOLD(KEY::LEFT) && ISTAP(KEY::SPACE))
	{
		player->LiftJump(Vec2(-300.f, -300.f));
		player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
	}

	if (ISHOLD(KEY::RIGHT) && ISTAP(KEY::SPACE))
	{
		player->LiftJump(Vec2(300.f, -300.f));
	}

	if (ISHOLD(KEY::UP))
	{
		Vec2 vPos = player->GetPos();
		vPos.y -= 200 * DT;
		player->SetPos(vPos);
	}

	if (ISHOLD(KEY::DOWN))
	{
		Vec2 vPos = player->GetPos();
		vPos.y += 200 * DT;
		player->SetPos(vPos);
	}
}

void CPlayerLadder::Update(CPlayer* player)
{
	if (player->GetLiftObj() == nullptr)
	{
		if (player->GetPlatform() == nullptr)
			switch (player->GetDir())
			{
			case eDir::LEFT:
				player->ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
				break;
			case eDir::RIGHT:
				player->ChangeState(CHANGESTATE(CPlayerState)::jumpright);
				break;
			}
		else
			player->Idle();
	}

	if (player->GetAnimator()->GetCurAnimation()->IsStop() && !(player->IsInvincible()))
		player->GetAnimator()->Play(L"ladder", true);

}

void CPlayerLadder::Enter(CPlayer* player)
{
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"ladder", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"ladder", true);

	player->ZeroJumpCnt();
	player->GetRigidbody()->SetGrnd(false);
	player->GetRigidbody()->SetGravityAccel(0);
	player->GetRigidbody()->SetVelocity(Vec2(0, 0));
}

void CPlayerLadder::Exit(CPlayer* player)
{
	player->GetRigidbody()->SetGravityAccel(2500);
}