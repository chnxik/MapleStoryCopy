#include "pch.h"
#include "KeySlot.h"

#include "CResMgr.h"
#include "CPlayerMgr.h"
#include "CKeyMgr.h"

#include "CQuickSlotUI.h"

#include "CPlayer.h"
#include "CTexture.h"
#include "CItem.h"
#include "CNum.h"

KeySlot::KeySlot(CPlayer* _pPlayer, UINT _SlotNum, UINT _key, CTexture* _KeyTex)
	: m_pPlayer(_pPlayer)
	, m_iSlotNum(_SlotNum)
	, m_eSlotType(KEYSLOT_TYPE::NONE)
	, m_eKey(_key)
	, m_pCNum{}
	, m_eCurSkill(SKILL::END)
	, m_pCurItem(nullptr)
	, m_pSlotTex(nullptr)
	, m_pCoolTex(nullptr)
	, m_fCoolRatio(0.f)
{
	SetIdleTex(_KeyTex);
	m_pCoolTex = CResMgr::GetInst()->LoadTexture(L"CooldownEff", L"texture\\UI\\QuickSlot\\Cooldown.png");
	SetScale(Vec2(32, 32));
}

KeySlot::~KeySlot()
{
}

void KeySlot::NumInit()
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

void KeySlot::tick()
{
	if (m_eSlotType == KEYSLOT_TYPE::NONE)
		m_pSlotTex = nullptr;

	CUI::tick();

	
	CQuickSlotUI* QuickSlot = CPlayerMgr::GetInst()->GetQuickSlot();
	
	tSkillInfo tSkill = m_pPlayer->GetSkill(m_eCurSkill);

	if (!tSkill.bAble)
		m_fCoolRatio = 1.f - (tSkill.fAcc / tSkill.fCoolTime);
	
	if (m_pCurItem != nullptr)
	{
		UINT ItemCnt = m_pCurItem->GetItemCnt();

		if (ItemCnt / 10 == 0)
			m_pCNum[0]->SetPrint(false);
		else
			m_pCNum[0]->SetPrint(true);

		m_pCNum[1]->SetPrint(true);
		m_pCNum[0]->SetNum(ItemCnt / 10);
		m_pCNum[1]->SetNum(ItemCnt % 10);

	}
	else if (m_pCurItem == nullptr)
	{
		m_pCNum[0]->SetPrint(false);
		m_pCNum[1]->SetPrint(false);
	}

	if (ISTAP((KEY)m_eKey))
	{
		switch (m_eSlotType)
		{
		case KEYSLOT_TYPE::ITEM:
			if (m_pCurItem)
			{
				m_pCurItem->UseItem(m_pPlayer);
				if (0 == m_pCurItem->SubItemCnt())
				{
					ResetSlot();
					QuickSlot->SetPrevSlot(m_eCurSkill, nullptr);
				}
					
			}
			break;
		case KEYSLOT_TYPE::SYSTEM:
			break;
		}
	}


	if (ISHOLD(KEY::LBTN) && IsMouseOn())
	{
		CQuickSlotUI* pParentUI = dynamic_cast<CQuickSlotUI*>(GetParentUI());

		if (pParentUI)
		{
			pParentUI->SelectKeySlot(this);
		}
	}

	if (ISTAP(KEY::LBTN) && IsMouseOn())
	{
		CUI::MouseLbtnDown();
		switch (m_eSlotType)
		{
		case KEYSLOT_TYPE::SKILL:
		{
			QuickSlot->SelectSkill(m_eCurSkill);
			QuickSlot->SelectTex(m_pSlotTex);
			QuickSlot->SetSlotType(m_eSlotType);
		}
			break;
		case KEYSLOT_TYPE::ITEM:
		{
			QuickSlot->SetItemSlot(m_pCurItem);
			QuickSlot->SelectTex(m_pSlotTex);
			QuickSlot->SetSlotType(m_eSlotType);
		}
			break;
		case KEYSLOT_TYPE::SYSTEM:
			break;
		case KEYSLOT_TYPE::NONE:
			break;
		default:
			break;
		}
	}
}

void KeySlot::render(HDC _dc)
{
	linerender(_dc);

	if (m_pSlotTex)
	{
		Vec2 vPos = GetFinalPos();
		vPos.x += (32.f - m_pSlotTex->Width()) / 2.f;
		vPos.y += (32.f - m_pSlotTex->Height()) / 2.f;

		OpRender(_dc, m_pSlotTex, vPos, 100);
	
		if (IsLbtnDown())
			OpRender(_dc, m_pSlotTex, CKeyMgr::GetInst()->GetMousePos() - GetScale() / 2.f, 70);

		tSkillInfo tSkill = m_pPlayer->GetSkill(m_eCurSkill);
		
		if (!tSkill.bAble)
		{
			BLENDFUNCTION tBlend = {};

			tBlend.AlphaFormat = AC_SRC_ALPHA;
			tBlend.BlendFlags = 0;
			tBlend.BlendOp = AC_SRC_OVER;
			tBlend.SourceConstantAlpha = 255;

			float Gauge = m_pCoolTex->Height() * m_fCoolRatio;
			float yPos = m_pCoolTex->Height() * (1.f - m_fCoolRatio);

			AlphaBlend(_dc								// 복사할 DC -> 알파값이 적용되어야 하므로 알파 DC에 복사해둔다.
				, (int)vPos.x, (int)vPos.y + (int)yPos // 윈도우 창 내에서 출력 시작위치 X,Y
				, m_pCoolTex->Width()					// 출력할 가로 크기
				, (int)Gauge							// 출력할 세로 크기
				, m_pCoolTex->GetDC()					// 복사할 DC
				, 0, 0									// 복사할 대상의 시작위치 x,y 
				, m_pCoolTex->Width()					// 복사할 가로 범위
				, m_pCoolTex->Height()					// 복사할 세로 범위
				, tBlend);

			CUI::render_childUI(_dc);
		}
	}

	OpRender(_dc, GetIdleTex(), GetFinalPos() + 2, 100);

	CUI::render_childUI(_dc);
}

void KeySlot::SetSlot(KEYSLOT_TYPE _NewSlotType, SKILL _newSkill, CTexture* _pTex)
{
	CQuickSlotUI* QuickSlot = CPlayerMgr::GetInst()->GetQuickSlot();
	
	KeySlot* PrevSlot = QuickSlot->GetPrevSlot(_newSkill);
	if (PrevSlot)
	{
		PrevSlot->ResetSlot();
		QuickSlot->SetPrevSlot(_newSkill,nullptr);
	}

	switch (m_eSlotType)
	{
	case KEYSLOT_TYPE::SKILL:
	{
		// 기존에 등록되있던 스킬키를 해제
		m_pPlayer->DeleteSkillKey(m_eCurSkill);
		PrevSlot = QuickSlot->GetPrevSlot(m_eCurSkill);
		QuickSlot->SetPrevSlot(m_eCurSkill, nullptr);
	}
		break;
	case KEYSLOT_TYPE::ITEM:
	{
		QuickSlot->SetPrevSlot(m_pCurItem->GetItemType(), nullptr);
		m_pCurItem = nullptr;
	}
		break;
	case KEYSLOT_TYPE::SYSTEM:
		break;
	case KEYSLOT_TYPE::NONE:
		break;
	}

	m_pPlayer->SetKey(_newSkill, m_eKey);
	m_eCurSkill = _newSkill;
	m_eSlotType = _NewSlotType;
	m_pSlotTex = _pTex;
	QuickSlot->SetPrevSlot(_newSkill,this);
}

void KeySlot::SetSlot(KEYSLOT_TYPE _NewSlotType, CItem* _newItem)
{
	CQuickSlotUI* QuickSlot = CPlayerMgr::GetInst()->GetQuickSlot();

	KeySlot* PrevSlot = QuickSlot->GetPrevSlot(_newItem->GetItemType());
	if (PrevSlot)
	{
		PrevSlot->ResetSlot();
		QuickSlot->SetPrevSlot(_newItem->GetItemType(), nullptr);
	}

	switch (m_eSlotType)
	{
	case KEYSLOT_TYPE::SKILL:
	{
		// 기존에 등록되있던 스킬키를 해제
		m_pPlayer->DeleteSkillKey(m_eCurSkill);
		PrevSlot = QuickSlot->GetPrevSlot(m_eCurSkill);
		QuickSlot->SetPrevSlot(m_eCurSkill, nullptr);
		m_eCurSkill = SKILL::END;
	}
	break;
	case KEYSLOT_TYPE::ITEM:
	{
		QuickSlot->SetPrevSlot(m_pCurItem->GetItemType(), nullptr);
	}
		break;
	case KEYSLOT_TYPE::SYSTEM:
		break;
	case KEYSLOT_TYPE::NONE:
		break;
	}
	
	m_pCurItem = _newItem;
	m_eSlotType = _NewSlotType;
	m_pSlotTex = m_pCurItem->GetItemTex();
	PrevSlot = this;
	QuickSlot->SetPrevSlot(m_pCurItem->GetItemType(), this);
}

void KeySlot::ResetSlot()
{
	m_eSlotType = KEYSLOT_TYPE::NONE;
	m_eCurSkill = SKILL::END;
	m_pCurItem = nullptr;
	m_pSlotTex = nullptr;
}
