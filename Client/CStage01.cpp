#include "pch.h"
#include "CStage01.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CPortal.h"
#include "CPlayer.h"


CStage01::CStage01()
{
}

CStage01::~CStage01()
{
}

void CStage01::init()
{
	if (IsInitComplet() == false)
	{
		MapFileLoad(L"stage01");
		PortalInit(PORTAL::PORTAL1, PORTAL::PORTAL1, LEVEL_TYPE::STAGE02);
		CreateUI();
		SetInitComplet();
	}
	else
	{
		ChangeBgm();
	}

	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::PLATFORM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MAP);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MAPOBJ);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::MOB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::SKILL, LAYER::MOB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MAP, LAYER::MOB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::MOB);

}

void CStage01::Enter(UINT _iPortalNo)
{
	// ���� �������� ������ȯ Ʈ���Ÿ� �߻���Ų ��Ż�κ��� ������ ��Ż��ȣ�� �޾ƿ´�.
	init();
	if (_iPortalNo == 0)
	{
		Vec2 vPos(497,745);
		CreatePlayer(vPos);
	}
	else
	{
		CreatePlayer(_iPortalNo);
	}
}

void CStage01::Exit()
{
	DeleteActor(LAYER::PLAYER);
	DeleteActor(LAYER::PLAYERUI);
}

void CStage01::CreateUI()
{
}
