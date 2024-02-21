#include "pch.h"
#include "CItemSlot.h"

#include "CPlayerMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CItem.h"
#include "CPlayer.h"

#include "CPlayerInvenWin.h"
#include "CQuickSlotUI.h"
#include "CNum.h"

CItemSlot::CItemSlot(CPlayer* pPlayer, UINT _i)
	: m_iSlotNo(_i)
	, m_pPlayer(pPlayer)
	, m_pItem(nullptr)
	, m_pCNum{}
	, m_fAcc (0.f)
	, m_bDbClick(false)
{
}

CItemSlot::~CItemSlot()
{
	if (m_pItem)
		DEL(m_pItem);
}

void CItemSlot::tick()
{
	if (m_pItem != nullptr)
	{
		UINT ItemCnt = m_pItem->GetItemCnt();
	
		if (ItemCnt == 0)
		{
			delete m_pItem;
			m_pItem = nullptr;
			m_pCNum[0]->SetPrint(false);
			m_pCNum[1]->SetPrint(false);
		}
		else
		{
			
			if(ItemCnt / 10 == 0)
				m_pCNum[0]->SetPrint(false);
			else
				m_pCNum[0]->SetPrint(true);

			m_pCNum[1]->SetPrint(true);
			m_pCNum[0]->SetNum(ItemCnt /10);
			m_pCNum[1]->SetNum(ItemCnt %10);
		}
	}
	else if (m_pItem == nullptr)
	{
		m_pCNum[0]->SetPrint(false);
		m_pCNum[1]->SetPrint(false);
	}

	if (m_bDbClick)
	{
		m_fAcc += DT;
		if (0.5f < m_fAcc)
		{
			m_bDbClick = false;
			m_fAcc = 0.f;
		}
	}


	CUI::tick();
}

void CItemSlot::render(HDC _dc)
{
	linerender(_dc);

	if (m_pItem)
	{
		Vec2 vPos = GetFinalPos();
		OpRender(_dc, m_pItem->GetItemTex(), vPos, 100);

		if (IsLbtnDown())
			OpRender(_dc, m_pItem->GetItemTex(), CKeyMgr::GetInst()->GetMousePos() - GetScale() / 2.f, 70);
	}
	CUI::render_childUI(_dc);
}

void CItemSlot::NumInit()
{
	Vec2 vPos = { 15,21 };
	for (int i = 0; i < 2; ++i)
	{
		m_pCNum[i] = new CNum;
		m_pCNum[i]->SetItemTex();
		m_pCNum[i]->SetScale(Vec2(8, 11));
		m_pCNum[i]->SetPos(vPos);
		AddChildUI(m_pCNum[i]);
		vPos.x += 8;
	}
}

void CItemSlot::UseItem()
{
	if (m_pItem)
	{
		m_pItem->UseItem(m_pPlayer);
		m_pItem->SubItemCnt();
	}
}

void CItemSlot::MouseLbtnClicked()
{
	if (m_bDbClick)
	{
		if (m_pItem)
		{
			UseItem();
			m_bDbClick = false;
			m_fAcc = 0.f;
		}
	}

	m_bDbClick = true;
	m_fAcc = 0.f;
}

void CItemSlot::MouseLbtnDown()
{
	if (m_pItem)
	{
		CUI::MouseLbtnDown();
		CQuickSlotUI* QuickSlot = CPlayerMgr::GetInst()->GetQuickSlot();
		QuickSlot->SetSlotType(KEYSLOT_TYPE::ITEM);		// 슬롯타입 :: 아이템으로 등록
		QuickSlot->SetItemSlot(m_pItem);					// 아이템슬롯 등록
		QuickSlot->SelectTex(m_pItem->GetItemTex());	// 아이템 아이콘 텍스쳐 저장


		CPlayerMgr::GetInst()->GetInvenWin()->AddSourceSlot(this); // 인벤토리 이동
	}
}

void CItemSlot::MouseOn()
{
	CPlayerMgr::GetInst()->GetInvenWin()->AddDestSlot(this);
	if (ISAWAY(KEY::LBTN))
		CPlayerMgr::GetInst()->GetInvenWin()->SwapSlot();
}
