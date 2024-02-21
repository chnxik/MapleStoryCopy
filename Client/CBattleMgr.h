#pragma once

class CPlayer;
class CMob;
class CSkill;
class CCollider;

class CBattleMgr
{
	SINGLE(CBattleMgr);

private:
	// BeginOverlap �� �Լ��� ȣ���ؼ� �� ��ü�� ����. (Player�� Mob)
	// �հ�ü���� �� ��ü���� ������ ����
	// �� ������ ���� �� �������� ������ Dead ó�� -> Player�� ����ġ ����, Mob�� SetDead�� �����ʷ� ����ó�� ����.
public:
	void DmgPrint(UINT _Dmg,CActor* pActor,DMG_TYPE _type, UINT _iHitCnt);

public:
	void Battle(CPlayer* pPlayer, CMob* _pMob);
	void Battle(CSkill* _pSkill, CMob*, UINT _TragetNum, UINT _iHitCnt);
};

