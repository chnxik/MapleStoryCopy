#include "pch.h"
#include "CPlayerAlertRight.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerAlertRight::KeyInput(CPlayer* player)
{
	player->attack();
	player->Jump();

	if (ISHOLD(KEY::LEFT) && ISHOLD(KEY::RIGHT))
		return;

	if (ISHOLD(KEY::RIGHT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkright);
	}
	if (ISHOLD(KEY::LEFT))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::walkleft);
	}
	if (ISHOLD(KEY::DOWN))
	{
		player->ChangeState(CHANGESTATE(CPlayerState)::proneright);
	}
}

void CPlayerAlertRight::Update(CPlayer* player)
{
	if (!(player->IsAlert()))
		player->ChangeState(CHANGESTATE(CPlayerState)::standright);
}

void CPlayerAlertRight::Enter(CPlayer* player)
{
	player->SetDir(eDir::RIGHT);
	if (player->IsInvincible())
		player->GetAnimator()->Play(L"alert_r", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"alert_r", true);
}

void CPlayerAlertRight::Exit(CPlayer* player)
{
}
