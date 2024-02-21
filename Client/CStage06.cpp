#include "pch.h"
#include "CStage06.h"

#include "CCamera.h"
#include "CCollisionMgr.h"

#include "CPortal.h"


CStage06::CStage06()
{
}

CStage06::~CStage06()
{
}

void CStage06::init()
{
	if (IsInitComplet() == false)
	{
		MapFileLoad(L"stage06");
		PortalInit(PORTAL::PORTAL1, PORTAL::PORTAL2, LEVEL_TYPE::STAGE05);
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

void CStage06::Enter(UINT _iPortalNo)
{
	// ���� �������� ������ȯ Ʈ���Ÿ� �߻���Ų ��Ż�κ��� ������ ��Ż��ȣ�� �޾ƿ´�.
	init();
	CreatePlayer(_iPortalNo);
}

void CStage06::Exit()
{
	DeleteActor(LAYER::PLAYER);
	DeleteActor(LAYER::PLAYERUI);
}

void CStage06::CreateUI()
{
}