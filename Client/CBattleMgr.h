#pragma once

class CPlayer;
class CMob;
class CSkill;
class CCollider;

class CBattleMgr
{
	SINGLE(CBattleMgr);

private:
	// BeginOverlap 때 함수를 호출해서 두 객체를 받음. (Player와 Mob)
	// 앞객체에서 뒤 객체에게 데미지 연산
	// 몹 데미지 연산 후 데미지가 낮으면 Dead 처리 -> Player로 경험치 전달, Mob은 SetDead후 스포너로 데드처리 전달.
public:
	void DmgPrint(UINT _Dmg,CActor* pActor,DMG_TYPE _type, UINT _iHitCnt);

public:
	void Battle(CPlayer* pPlayer, CMob* _pMob);
	void Battle(CSkill* _pSkill, CMob*, UINT _TragetNum, UINT _iHitCnt);
};

