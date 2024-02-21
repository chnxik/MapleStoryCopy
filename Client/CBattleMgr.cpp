#include "pch.h"
#include "CBattleMgr.h"

#include "CRigidbody.h"

#include "CMob.h"
#include "CPlayer.h"
#include "CSkill.h"

#include "CSound.h"

#include "CPlayerState.h"
#include "CMobState.h"
#include "CDamage.h"

CBattleMgr::CBattleMgr()
{
}

CBattleMgr::~CBattleMgr()
{
}


void CBattleMgr::DmgPrint(UINT _Dmg, CActor* pActor, DMG_TYPE _type, UINT _iHitCnt)
{
	int Dmg = _Dmg;
	int Temp = Dmg;
	int DmgLen = 0;

	while (Temp)
	{
		Temp /= 10;
		++DmgLen;
	}
	
	Vec2 vPos = pActor->GetPos();
	vPos.x -= pActor->GetScale().x / 2;
	vPos.y -= pActor->GetScale().y + 50 + (_iHitCnt * 30);
	
	vPos.x += ((DmgLen / 2) * 30 + (DmgLen % 2) * 15);

	for (int i = 0; i < DmgLen; ++i)
	{
		UINT num = Dmg % 10;
		Dmg /= 10;
		CDamage* pNum = new CDamage(num,_type);
		Instantiate(pNum, vPos, LAYER::DAMAGESKIN);
		vPos.x -= 30;
	}
}

void CBattleMgr::Battle(CPlayer* pPlayer, CMob* _pMob)
{
	if (pPlayer->IsInvincible() || _pMob->IsInvincible())
		return;

	tStatus MobStat = _pMob->GetStatus();
	tStatus PlayerStat = pPlayer->GetStatus();
	// Mob�� ������ ���� (���� ���ݷ� - �÷��̾� ����)
	// �ִ� ���ݷ°� �ְ� ���ݷ� ���̿��� �������� �ο�

	int MobAtk = (rand() % (MobStat.MAXATK - MobStat.MINATK)) + MobStat.MINATK;
	int iMobDmg = MobAtk - PlayerStat.DEF;

	if (iMobDmg <= 0)	// �������� 0 ������ ��� �ּҵ����� 1�� ����
		iMobDmg = 1;
	
	if (0 < pPlayer->HPtick(-iMobDmg))
		pPlayer->Damaged(_pMob->GetDir());

	DmgPrint(iMobDmg, pPlayer,DMG_TYPE::MOB,0);
}

void CBattleMgr::Battle(CSkill* pSkill, CMob* pMob, UINT _iTargetNum, UINT _iHitCnt)
{
	if (pMob->IsInvincible() || pMob->IsDead())
		return;

	tStatus MobStat = pMob->GetStatus();
	tStatus PlayerStat = pSkill->GetPlayer()->GetStatus();

	// Skill�� ������ ���� (�÷��̾� ���ݷ� * ��ų ������ ���)
	int iskillDmg = (int)(((rand() % (PlayerStat.MAXATK - PlayerStat.MINATK)) + PlayerStat.MINATK) * pSkill->GetSkillDmg());

	// ���� ó�� ( Skill ������ - Mob ���� )
	iskillDmg -= MobStat.DEF;

	if (iskillDmg <= 0)	// �������� 0 ������ ��� �ּҵ����� 1�� ����
		iskillDmg = 1;

	pMob->HPtick(-iskillDmg);

	DmgPrint(iskillDmg, pMob, DMG_TYPE::PLAYER, _iHitCnt);
	if (pSkill->GetHitSound() != nullptr)
	{
		pSkill->GetHitSound()->SetPosition(0);
		pSkill->GetHitSound()->Play(false);
	};

	if (MobStat.HP <= iskillDmg)
	{
		pSkill->GetTarget()[_iTargetNum] = nullptr;
		pMob->ChangeState(CHANGESTATE(CMobState)::dead);
		pSkill->GetPlayer()->AddExp(MobStat.Exp);
	}
	else
	{
		switch (pSkill->GetDir())
		{
		case eDir::LEFT:
			pMob->SetDir(eDir::RIGHT);
			break;
		case eDir::RIGHT:
			pMob->SetDir(eDir::LEFT);
			break;
		}
		pMob->ChangeState(CHANGESTATE(CMobState)::damaged);
	}
}