#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CResMgr.h"
#include "CBattleMgr.h"

#include "CLevel.h"
#include "CPortal.h"
#include "CMap.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidbody.h"
#include "CSound.h"

#include "CPlayerState.h"
#include "CPlayerStandRight.h"

#include "CPlatform.h"
#include "CMob.h"
#include "CFiledItem.h"

#include "CInteraction.h"
#include "DoubleJump.h"
#include "LevelUP.h"
#include "Tomb.h"
#include "CPlayerDeadMessage.h"

void CPlayer::SetInterface()
{
	SetScale(Vec2(54, 75));
	SetDir(eDir::RIGHT);
	SetCmrAfctd(true);
	SetStatus();
	SetSkillInfo();
	CreateAnimator();
	CreateRigidbody();
	CreateCollider();
	CreateState();
	GetCollider()->SetScale(Vec2(54, 75));
	SoundInit();
}

void CPlayer::SetAnimation()
{
	GetAnimator()->CreateAnimation(L"stand_l");
	GetAnimator()->CreateAnimation(L"stand_r");
	GetAnimator()->CreateAnimation(L"walk_l");
	GetAnimator()->CreateAnimation(L"walk_r");
	GetAnimator()->CreateAnimation(L"alert_l");
	GetAnimator()->CreateAnimation(L"alert_r");
	GetAnimator()->CreateAnimation(L"jump_l");
	GetAnimator()->CreateAnimation(L"jump_r");
	GetAnimator()->CreateAnimation(L"prone_l");
	GetAnimator()->CreateAnimation(L"prone_r");
	GetAnimator()->CreateAnimation(L"rope");
	GetAnimator()->CreateAnimation(L"ladder");
	GetAnimator()->CreateAnimation(L"ropestop");
	GetAnimator()->CreateAnimation(L"ladderstop");
	GetAnimator()->CreateAnimation(L"ghost");
	GetAnimator()->CreateAnimation(L"mantis1_l");
	GetAnimator()->CreateAnimation(L"mantis1_r");
	GetAnimator()->CreateAnimation(L"mantis2_l");
	GetAnimator()->CreateAnimation(L"mantis2_r");
	GetAnimator()->CreateAnimation(L"NTshotgun_l");
	GetAnimator()->CreateAnimation(L"NTshotgun_r");
	GetAnimator()->CreateAnimation(L"NTbrick_l");
	GetAnimator()->CreateAnimation(L"NTbrick_r");
	GetAnimator()->CreateAnimation(L"NTbricklast_l");
	GetAnimator()->CreateAnimation(L"NTbricklast_r");

	GetAnimator()->Play(L"stand_r", true);
}

void CPlayer::SetSkillInfo()
{
	m_arrtSkill[(UINT)SKILL::STROKE]	= { 0.f,0.f,0,true,(UINT)KEY::END };
	m_arrtSkill[(UINT)SKILL::CHASE]		= { 5.f,0.f,30,true,(UINT)KEY::END };
	m_arrtSkill[(UINT)SKILL::SHOTGUN]	= { 3.f,0.f,5,true,(UINT)KEY::END };
	m_arrtSkill[(UINT)SKILL::KNIFE]		= { 5.f,0.f,30,true,(UINT)KEY::END };
	m_arrtSkill[(UINT)SKILL::BAT]		= { 5.f,0.f,30,true,(UINT)KEY::END };
	m_arrtSkill[(UINT)SKILL::BRICK]		= { 5.f,0.f,30,true,(UINT)KEY::END };

}

void CPlayer::SetStatus()
{
	m_tStatus.Lv = 1;
	m_tStatus.MaxExp = 20;
	m_tStatus.Exp = 0;
	m_tStatus.MaxHP = 50;
	m_tStatus.HP = 50;
	m_tStatus.MaxMP = 50;
	m_tStatus.MP = 50;
	m_tStatus.MAXATK = 10;
	m_tStatus.MINATK = 3;
	m_tStatus.DEF = 1;
	m_tStatus.StatPoint = 0;
	m_tStatus.SkillPoint = 0;
}


void CPlayer::CreateState()
{
	m_pState = &CPlayerState::standright;
}

void CPlayer::SoundInit()
{
	m_pSound[(UINT)SOUND_ETC::JUMP] = CResMgr::GetInst()->LoadSound(L"Jump", L"sound\\etc\\Jump.wav");
	m_pSound[(UINT)SOUND_ETC::GETITEM] = CResMgr::GetInst()->LoadSound(L"GetItem", L"sound\\etc\\GetItem.wav");
}


void CPlayer::CoolTime()
{
	for (int i = 0; i < (UINT)SKILL::END; ++i)
	{
		if (m_arrtSkill[i].bAble == false)
		{
			m_arrtSkill[i].fAcc += DT;
			if (m_arrtSkill[i].fAcc >= m_arrtSkill[i].fCoolTime)
			{
				m_arrtSkill[i].fAcc = 0.f;
				m_arrtSkill[i].bAble = true;
			}
		}
	}

}

void CPlayer::attack()
{
	// 퀵슬롯에서 단축키별 호출 스킬을 변경할 수 있도록
	if (m_arrtSkill[(UINT)SKILL::STROKE].Key != (UINT)KEY::END && ISHOLD((KEY)m_arrtSkill[(UINT)SKILL::STROKE].Key))
	{
		if ((0 > (m_tStatus.MP - m_arrtSkill[(UINT)SKILL::STROKE].iMP)) || !(m_arrtSkill[(UINT)SKILL::STROKE].bAble))
			return;

		m_tStatus.MP -= m_arrtSkill[(UINT)SKILL::STROKE].iMP;
		m_arrtSkill[(UINT)SKILL::STROKE].bAble = false;
		m_arrtSkill[(UINT)SKILL::STROKE].fAcc = 0.f;
		ChangeState(CHANGESTATE(CPlayerState)::Storke);
		return;
	}

	if (m_arrtSkill[(UINT)SKILL::SHOTGUN].Key != (UINT)KEY::END && ISHOLD((KEY)m_arrtSkill[(UINT)SKILL::SHOTGUN].Key))
	{
		int a = m_tStatus.MP - m_arrtSkill[(UINT)SKILL::SHOTGUN].iMP;
		if ((0 > (m_tStatus.MP - m_arrtSkill[(UINT)SKILL::SHOTGUN].iMP)) || !(m_arrtSkill[(UINT)SKILL::SHOTGUN].bAble))
			return;
		
		m_tStatus.MP -= m_arrtSkill[(UINT)SKILL::SHOTGUN].iMP;
		m_arrtSkill[(UINT)SKILL::SHOTGUN].bAble = false;
		m_arrtSkill[(UINT)SKILL::SHOTGUN].fAcc = 0.f;
		ChangeState(CHANGESTATE(CPlayerState)::shotgun1);
		return;
	}

	if (m_arrtSkill[(UINT)SKILL::BRICK].Key != (UINT)KEY::END && ISHOLD((KEY)m_arrtSkill[(UINT)SKILL::BRICK].Key))
	{
		int a = m_tStatus.MP - m_arrtSkill[(UINT)SKILL::BRICK].iMP;
		if ((0 > (m_tStatus.MP - m_arrtSkill[(UINT)SKILL::BRICK].iMP)) || !(m_arrtSkill[(UINT)SKILL::BRICK].bAble))
			return;

		m_tStatus.MP -= m_arrtSkill[(UINT)SKILL::BRICK].iMP;
		m_arrtSkill[(UINT)SKILL::BRICK].bAble = false;
		m_arrtSkill[(UINT)SKILL::BRICK].fAcc = 0.f;
		ChangeState(CHANGESTATE(CPlayerState)::brick1);
		return;
	}
}

void CPlayer::Idle()
{
	GetRigidbody()->SetGravityAccel(2500.f);

	switch (GetDir())
	{
	case eDir::LEFT:
	{
		if (IsAlert())
			ChangeState(CHANGESTATE(CPlayerState)::alertleft);
		else
			ChangeState(CHANGESTATE(CPlayerState)::standleft);
	}
	break;
	case eDir::RIGHT:
	{
		if (IsAlert())
			ChangeState(CHANGESTATE(CPlayerState)::alertright);
		else
			ChangeState(CHANGESTATE(CPlayerState)::standright);
	}
	break;
	}
}

void CPlayer::Jump()
{
	if (GetRigidbody()->IsGrnd())
	{
		if (ISTAP(KEY::SPACE))
		{
			GetRigidbody()->SetGravityAccel(2500.f);
			m_iJumpCnt = 0;
			Vec2 vCurVel = GetRigidbody()->GetVelocity();
			GetRigidbody()->SetVelocity(Vec2(vCurVel.x, -700.f));
			GetRigidbody()->SetGrnd(false);
			GetSound(SOUND_ETC::JUMP)->SetPosition(0);
			GetSound(SOUND_ETC::JUMP)->Play(false);

			switch (GetDir())
			{
			case eDir::LEFT:
				ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
				break;
			case eDir::RIGHT:
				ChangeState(CHANGESTATE(CPlayerState)::jumpright);
				break;
			}
		}
	}
	else if (m_iJumpCnt < 2)

	{
		if (ISTAP(KEY::SPACE))
		{
			GetRigidbody()->SetGravityAccel(2500.f);
			CSkill* dbjump = new DoubleJump(this);
			dbjump->Active();
			Instantiate(dbjump, LAYER::SKILL);
			++m_iJumpCnt;
			switch (GetDir())
			{
			case eDir::LEFT:
				ChangeState(CHANGESTATE(CPlayerState)::jumpleft);
				break;
			case eDir::RIGHT:
				ChangeState(CHANGESTATE(CPlayerState)::jumpright);
				break;
			}
		}
	}
}

void CPlayer::DownJump()
{
	GetRigidbody()->SetVelocity(Vec2(0, 0));
	SetPos(Vec2(GetPos().x, GetPos().y + 15));
	GetRigidbody()->SetGrnd(false);
	GetSound(SOUND_ETC::JUMP)->SetPosition(0);
	GetSound(SOUND_ETC::JUMP)->Play(false);
}

void CPlayer::Damaged(eDir MobDir)
{
	SetAlert();
	SetInvincible();
	GetRigidbody()->SetFriction(2000.f);
	GetRigidbody()->SetGravityAccel(2500.f);
	GetRigidbody()->SetGrnd(false);

	switch (MobDir)
	{
	case eDir::LEFT:
	{
		GetRigidbody()->SetVelocity(Vec2(-300.f, -300.f));
		ChangeState(CHANGESTATE(CPlayerState)::alertright);
	}
	break;
	case eDir::RIGHT:
	{
		GetRigidbody()->SetVelocity(Vec2(300.f, -300.f));
		GetRigidbody()->SetGrnd(false);
		ChangeState(CHANGESTATE(CPlayerState)::alertleft);
	}
	break;
	}
}

void CPlayer::LiftJump(Vec2 _vVelocity)
{
	GetRigidbody()->SetVelocity(_vVelocity);
	GetSound(SOUND_ETC::JUMP)->SetPosition(0);
	GetSound(SOUND_ETC::JUMP)->Play(false);
}

void CPlayer::PlayerDead()
{
	m_pTomb = new Tomb(this);
	m_pTomb->Active();
	Instantiate(m_pTomb, LAYER::MAPOBJ);

	m_pDeadMessage = new CPlayerDeadMessage(this);
	m_pDeadMessage->init();
	Instantiate(m_pDeadMessage, LAYER::PLAYERUI);
	
	m_bInvincible = true;
	m_bPlayerDead = true;

	GetAnimator()->Play(L"ghost", false);
}

void CPlayer::Resurrection()
{
	m_pTomb->SetDead();
	m_pDeadMessage->SetDead();
	m_bInvincible = false;
	m_bPlayerDead = false;
	m_tStatus.HP = 50;
	m_tStatus.MP = 50;
	SetPos(CLevelMgr::GetInst()->GetCurLevel()->GetPortal(PORTAL::PORTAL1)->GetSpawnPos());
	Idle();
}

UINT CPlayer::HPtick(int _amount)
{
	m_tStatus.HP += _amount;
	if (m_tStatus.HP <= 0)
	{
		m_tStatus.HP = 0;
		PlayerDead();
	}

	if (m_tStatus.HP >= (int)m_tStatus.MaxHP)
		m_tStatus.HP = (int)m_tStatus.MaxHP;

	return m_tStatus.HP;
}

UINT CPlayer::MPtick(int _amount)
{
	m_tStatus.MP += _amount;
	if (m_tStatus.MP <= 0)
		m_tStatus.MP = 0;

	if (m_tStatus.MP >= (int)m_tStatus.MaxMP)
		m_tStatus.MP = (int)m_tStatus.MaxMP;

	return m_tStatus.MP;
}

void CPlayer::AddExp(int _Exp)
{
	m_tStatus.Exp += _Exp;

	if (m_tStatus.MaxExp <= m_tStatus.Exp)
	{
		int MaxExp = m_tStatus.MaxExp;
		int Exp = m_tStatus.Exp;
		Exp -= MaxExp;
		PlayerLvUP();// 레벨업 처리, 스탯상승 경험치 초기화.
		m_tStatus.Exp += Exp; // 잔여 경험치 더하기
	}
}

void CPlayer::HPUP()
{
	m_tStatus.MaxHP += 50;
	--m_tStatus.StatPoint;
}

void CPlayer::MPUP()
{
	m_tStatus.MaxMP += 50;
	--m_tStatus.StatPoint;
}

void CPlayer::ATKUP()
{
	m_tStatus.MAXATK += 50;
	m_tStatus.MINATK = (UINT)((float)m_tStatus.MAXATK * 0.9f);
	--m_tStatus.StatPoint;
}

void CPlayer::DEFUP()
{
	m_tStatus.DEF += 1;
	--m_tStatus.StatPoint;
}

void CPlayer::DeleteSkillKey(SKILL _skill)
{
	m_arrtSkill[(UINT)_skill].Key = (UINT)KEY::END;
}

void CPlayer::Keyinit()
{
	for (int i = 0; i < (UINT)SKILL::END; ++i)
		m_arrtSkill[(UINT)i].Key = (UINT)KEY::END;
}

void CPlayer::PlayerLvUP()
{
	m_tStatus.Lv += 1;
	m_tStatus.MaxExp = (UINT)((float)m_tStatus.MaxExp * 1.5f);
	m_tStatus.Exp = 0;
	m_tStatus.MaxHP += 10;
	m_tStatus.HP = m_tStatus.MaxHP;
	m_tStatus.MaxMP += 10;
	m_tStatus.MP = m_tStatus.MaxMP;
	m_tStatus.MAXATK += (UINT)((float)m_tStatus.MAXATK * 0.2f);
	m_tStatus.MINATK = (UINT)((float)m_tStatus.MAXATK * 0.9f);
	m_tStatus.DEF += (UINT)((float)m_tStatus.DEF * 0.2f);;
	m_tStatus.StatPoint += 5;
	m_tStatus.SkillPoint += 3;

	CInteraction* pLevelUP = new LevelUP(this);
	pLevelUP->Active();
	Instantiate(pLevelUP, LAYER::SKILL); 
}
