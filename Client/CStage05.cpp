#include "pch.h"
#include "CStage05.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CPortal.h"


CStage05::CStage05()
{
}

CStage05::~CStage05()
{
}

void CStage05::init()
{
	if (IsInitComplet() == false)
	{
		MapFileLoad(L"stage05");
		PortalInit(PORTAL::PORTAL1, PORTAL::PORTAL2, LEVEL_TYPE::STAGE04);
		PortalInit(PORTAL::PORTAL2, PORTAL::PORTAL1, LEVEL_TYPE::STAGE06);
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

void CStage05::Enter(UINT _iPortalNo)
{
	// 이전 레벨에서 레벨전환 트리거를 발생시킨 포탈로부터 스폰될 포탈번호를 받아온다.
	init();
	CreatePlayer(_iPortalNo);
}

void CStage05::Exit()
{
	DeleteActor(LAYER::PLAYER);
	DeleteActor(LAYER::PLAYERUI);
}

void CStage05::CreateUI()
{
}