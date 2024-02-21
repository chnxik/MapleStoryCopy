#include "pch.h"
#include "CPlayerInvenWin.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"

#include "CPNUI.h"
#include "CLayerUI.h"
#include "CBtnUI.h"
#include "CItemSlot.h"
#include "CItem.h"

#include "CTexture.h"

#include "CPlayer.h"
#include "CSound.h"

CPlayerInvenWin::CPlayerInvenWin(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, m_pPNUI(nullptr)
	, m_iItemCnt(0)
	, m_pSourceSlot(nullptr)
	, m_pDestSlot(nullptr)
{
	init();
}

CPlayerInvenWin::~CPlayerInvenWin()
{
	vector<CItemSlot*>::iterator iter = m_arrItemSlot.begin();
	for (; iter != m_arrItemSlot.end();)
		iter = m_arrItemSlot.erase(iter);
}

void CPlayerInvenWin::SwapSlot()
{
	if (m_pSourceSlot && m_pDestSlot )
	{
		if (m_pSourceSlot != m_pDestSlot)
		{
			CItem* temp = m_pSourceSlot->GetItem();
			m_pSourceSlot->SetItem(m_pDestSlot->GetItem());
			m_pDestSlot->SetItem(temp);
		}
	}
	m_pSourceSlot = nullptr;
	m_pDestSlot = nullptr;
}

void CPlayerInvenWin::init()
{
	SetClose();

	m_pPNUI = new CPNUI;
	CLayerUI* pLayerUI = new CLayerUI;

	m_pPNUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"InvenUIBackgrnd", L"texture\\UI\\WindowUI\\InvenWindow\\backgrnd.png"));
	pLayerUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"InvenUILayer", L"texture\\UI\\WindowUI\\InvenWindow\\layer.png"));


	// 포지션 셋팅
	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x *= 3.f / 4.f;
	vPos.y *= 1.f / 8.f;

	m_pPNUI->SetPos(vPos);
	pLayerUI->SetPos(Vec2(6, 23));

	AddChildUI(m_pPNUI);
	m_pPNUI->AddChildUI(pLayerUI);

	SetItemSlot();
}

void CPlayerInvenWin::SetItemSlot()
{
		Vec2 vPos = { 20,39 };

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			CItemSlot* ItemSlot = new CItemSlot(m_pPlayer, j + i * 4);
			ItemSlot->SetPos(vPos);
			ItemSlot->SetScale(Vec2(32, 32));
			m_arrItemSlot.push_back(ItemSlot);
			m_pPNUI->AddChildUI(ItemSlot);
			ItemSlot->NumInit();

			vPos.x += 42;
		}
		vPos.x = 20;
		vPos.y += 42;
	}
}

bool CPlayerInvenWin::AddItem(CItem* pItem)
{
	int AddnewItem = -1;

	ITEM_TYPE item = pItem->GetItemType();

	for (int i = 0; i < 8; ++i)
	{
		if (m_arrItemSlot[i]->GetItem() == nullptr)
		{
			if (AddnewItem == -1)
				AddnewItem = i;
		}
		else
		{
			if (m_arrItemSlot[i]->GetItem()->GetItemType() == item)
			{
				m_arrItemSlot[i]->GetItem()->AddItemCnt();
				delete pItem;
				return false;
			}
		}
	}

	m_arrItemSlot[AddnewItem]->SetItem(pItem);
	return true;
}

void CPlayerInvenWin::tick()
{
	CUI::tick();
}

void CPlayerInvenWin::render(HDC _dc)
{
	CUI::render_childUI(_dc);
}