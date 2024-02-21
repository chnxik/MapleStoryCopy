#include "pch.h"
#include "CPlayerSkillStroke.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidbody.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayer.h"
#include "SkillStroke.h"

void CPlayerSkillStroke::KeyInput(CPlayer* player)
{
}

void CPlayerSkillStroke::Update(CPlayer* player)
{
	_facc += DT;
	
	if (_facc >= _fDelay)
		player->ChangeState(CHANGESTATE(CPlayerState)::Stroke2);
}

void CPlayerSkillStroke::Enter(CPlayer* player)
{
	_facc = 0;
	CSkill* stroke = new SkillStroke(player);	// 스킬생성
	_fDelay = stroke->GetNextActTime();
	stroke->Active();
	Instantiate(stroke, LAYER::SKILL);
	player->SetAlert();
}

void CPlayerSkillStroke::Exit(CPlayer* player)
{
}