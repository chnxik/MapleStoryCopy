#include "pch.h"
#include "CStage04.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CPortal.h"


CStage04::CStage04()
{
}

CStage04::~CStage04()
{
}

void CStage04::init()
{
	if (IsInitComplet() == false)
	{
		MapFileLoad(L"stage04");
		PortalInit(PORTAL::PORTAL1, PORTAL::PORTAL2, LEVEL_TYPE::STAGE03);
		PortalInit(PORTAL::PORTAL2, PORTAL::PORTAL1, LEVEL_TYPE::STAGE05);
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

void CStage04::Enter(UINT _iPortalNo)
{
	// ���� �������� ������ȯ Ʈ���Ÿ� �߻���Ų ��Ż�κ��� ������ ��Ż��ȣ�� �޾ƿ´�.
	init();
	CreatePlayer(_iPortalNo);
}

void CStage04::Exit()
{
	DeleteActor(LAYER::PLAYER);
	DeleteActor(LAYER::PLAYERUI);
}

void CStage04::CreateUI()
{
}