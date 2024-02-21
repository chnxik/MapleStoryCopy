#include "pch.h"
#include "CPlayerAlertLeft.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CPlayerState.h"
#include "CPlayer.h"

void CPlayerAlertLeft::KeyInput(CPlayer* player)
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
		player->ChangeState(CHANGESTATE(CPlayerState)::proneleft);
	}
}

void CPlayerAlertLeft::Update(CPlayer* player)
{
	if (!(player->IsAlert()))
		player->ChangeState(CHANGESTATE(CPlayerState)::standleft);
}

void CPlayerAlertLeft::Enter(CPlayer* player)
{
	player->SetDir(eDir::LEFT);
	if(player->IsInvincible())
		player->GetAnimator()->Play(L"alert_l", true, FLASHGVALUE, true);
	else
		player->GetAnimator()->Play(L"alert_l", true);
}

void CPlayerAlertLeft::Exit(CPlayer* player)
{
}
