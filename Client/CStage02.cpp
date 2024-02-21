#include "pch.h"
#include "CStage02.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CPortal.h"


CStage02::CStage02()
{
}

CStage02::~CStage02()
{
}

void CStage02::init()
{
	if (IsInitComplet() == false)
	{
		MapFileLoad(L"stage02");
		PortalInit(PORTAL::PORTAL1, PORTAL::PORTAL1, LEVEL_TYPE::STAGE01);
		PortalInit(PORTAL::PORTAL2, PORTAL::PORTAL1, LEVEL_TYPE::STAGE03);
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
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLAYER, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::ITEM);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::PLATFORM, LAYER::MOB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::SKILL, LAYER::MOB);
	CCollisionMgr::GetInst()->LayerCheck(LAYER::MAP, LAYER::MOB);
}

void CStage02::Enter(UINT _iPortalNo)
{
	// ���� �������� ������ȯ Ʈ���Ÿ� �߻���Ų ��Ż�κ��� ������ ��Ż��ȣ�� �޾ƿ´�.
	init();
	CreatePlayer(_iPortalNo);
}

void CStage02::Exit()
{
	DeleteActor(LAYER::PLAYER);
	DeleteActor(LAYER::PLAYERUI);
}

void CStage02::CreateUI()
{
}

