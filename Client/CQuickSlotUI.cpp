#include "pch.h"
#include "CQuickSlotUI.h"

#include "CEngine.h"

#include "CPlayerMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

#include "CLayerUI.h"
#include "CBackGrndUI.h"
#include "KeySlot.h"

#include "CPlayer.h"
#include "CItem.h"

#include "CTexture.h"


CQuickSlotUI::CQuickSlotUI(CPlayer* _pPlayer)
	: m_pPlayer(_pPlayer)
	, m_eCurSlotType(KEYSLOT_TYPE::NONE)
	, m_eCurSkill(SKILL::END)
	, m_pCurItem(nullptr)
	, m_pCurSlot(nullptr)
	, m_pSelectedTex(nullptr)
	, m_pKeySlot{}
	, m_pPrvSkillSlot{}
{
	init();
}

CQuickSlotUI::~CQuickSlotUI()
{
}

void CQuickSlotUI::init()
{
	CBackGrndUI* StatusBackGrnd = new CBackGrndUI;
	CLayerUI* StatusLayer = new CLayerUI;

	StatusBackGrnd->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"QSlotBackGrnd", L"texture\\UI\\QuickSlot\\backgrnd.png"));
	StatusLayer->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"QSlotCover", L"texture\\UI\\QuickSlot\\cover.png"));

	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x = vPos.x - StatusLayer->GetIdleTex()->Width();
	vPos.y = vPos.y - (StatusLayer->GetIdleTex()->Height()) - 10;
	SetPos(vPos);
	SetScale(StatusLayer->GetScale());

	StatusBackGrnd->SetPos(Vec2(2, 3));

	AddChildUI(StatusBackGrnd);
	AddChildUI(StatusLayer);
	initKey();
}

void CQuickSlotUI::initKey()
{
	m_pKeySlot[0]	= new KeySlot(m_pPlayer, 0,(UINT)KEY::Q,CResMgr::GetInst()->LoadTexture(L"Qslotq",L"texture\\UI\\QuickSlot\\key\\q.png"));
	m_pKeySlot[1]	= new KeySlot(m_pPlayer, 1,(UINT)KEY::W,CResMgr::GetInst()->LoadTexture(L"Qslotw",L"texture\\UI\\QuickSlot\\key\\w.png"));
	m_pKeySlot[2]	= new KeySlot(m_pPlayer, 2,(UINT)KEY::E,CResMgr::GetInst()->LoadTexture(L"Qslote",L"texture\\UI\\QuickSlot\\key\\e.png"));
	m_pKeySlot[3]	= new KeySlot(m_pPlayer, 3,(UINT)KEY::R,CResMgr::GetInst()->LoadTexture(L"Qslotr",L"texture\\UI\\QuickSlot\\key\\r.png"));
	m_pKeySlot[4]	= new KeySlot(m_pPlayer, 4,(UINT)KEY::_1,CResMgr::GetInst()->LoadTexture(L"Qslot1",L"texture\\UI\\QuickSlot\\key\\1.png"));
	m_pKeySlot[5]	= new KeySlot(m_pPlayer, 5,(UINT)KEY::_2,CResMgr::GetInst()->LoadTexture(L"Qslot2",L"texture\\UI\\QuickSlot\\key\\2.png"));
	m_pKeySlot[6]	= new KeySlot(m_pPlayer, 6,(UINT)KEY::_3,CResMgr::GetInst()->LoadTexture(L"Qslot3",L"texture\\UI\\QuickSlot\\key\\3.png"));
	m_pKeySlot[7]	= new KeySlot(m_pPlayer, 7,(UINT)KEY::_4,CResMgr::GetInst()->LoadTexture(L"Qslot4",L"texture\\UI\\QuickSlot\\key\\4.png"));
	m_pKeySlot[8]	= new KeySlot(m_pPlayer, 8,(UINT)KEY::A,CResMgr::GetInst()->LoadTexture(L"Qslota",L"texture\\UI\\QuickSlot\\key\\a.png"));
	m_pKeySlot[9]	= new KeySlot(m_pPlayer, 9,(UINT)KEY::S,CResMgr::GetInst()->LoadTexture(L"Qslots",L"texture\\UI\\QuickSlot\\key\\s.png"));
	m_pKeySlot[10]	= new KeySlot(m_pPlayer, 10,(UINT)KEY::D,CResMgr::GetInst()->LoadTexture(L"Qslotd",L"texture\\UI\\QuickSlot\\key\\d.png"));
	m_pKeySlot[11]	= new KeySlot(m_pPlayer, 11,(UINT)KEY::F,CResMgr::GetInst()->LoadTexture(L"Qslotf",L"texture\\UI\\QuickSlot\\key\\f.png"));
	m_pKeySlot[12]	= new KeySlot(m_pPlayer, 12,(UINT)KEY::_5,CResMgr::GetInst()->LoadTexture(L"Qslot5",L"texture\\UI\\QuickSlot\\key\\5.png"));
	m_pKeySlot[13]	= new KeySlot(m_pPlayer, 13,(UINT)KEY::_6,CResMgr::GetInst()->LoadTexture(L"Qslot6",L"texture\\UI\\QuickSlot\\key\\6.png"));
	m_pKeySlot[14]	= new KeySlot(m_pPlayer, 14,(UINT)KEY::_7,CResMgr::GetInst()->LoadTexture(L"Qslot7",L"texture\\UI\\QuickSlot\\key\\7.png"));
	m_pKeySlot[15]	= new KeySlot(m_pPlayer, 15,(UINT)KEY::_8,CResMgr::GetInst()->LoadTexture(L"Qslot8",L"texture\\UI\\QuickSlot\\key\\8.png"));

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			m_pKeySlot[j + i * 8]->SetPos(Vec2(2 + 35 * j, 3 + 35 * i));
			m_pKeySlot[j + i * 8]->NumInit();
			AddChildUI(m_pKeySlot[j + i * 8]);
		}
	}
}

void CQuickSlotUI::ResetSlot()
{
	// 해당 슬롯의 타입을 확인
	
	// 스킬이면, 
	// 플레이어 객체에서 저장된 스킬의 사용 키 정보를 초기화한다.
	// 이전 저장된 슬롯의 동일한 스킬인 슬롯을 초기화한다.

	// 아이템이면,
	// 플레이어 객체에 저장된 아이템 사용 키 정보를 초기화한다.
	// 


}

void CQuickSlotUI::tick()
{
	CUI::tick();

	// 마우스 버튼이 때졌다.
	if (ISAWAY(KEY::LBTN))
	{
		// 마우스가 퀵슬롯 UI 위에 있다.
		if (IsMouseOn())
		{
			switch (m_eCurSlotType)
			{
			case KEYSLOT_TYPE::SKILL:
			{
				if (m_pCurSlot)
					m_pCurSlot->SetSlot(m_eCurSlotType, m_eCurSkill, m_pSelectedTex);
			}
				break;
			case KEYSLOT_TYPE::ITEM:
			{
				if (m_pCurSlot)
					m_pCurSlot->SetSlot(m_eCurSlotType, m_pCurItem);
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

		// 초기화
		m_eCurSkill = SKILL::END;
		m_eCurSlotType = KEYSLOT_TYPE::NONE;
		m_pCurItem = nullptr;
		m_pCurSlot = nullptr;
		m_pSelectedTex = nullptr;
	}
}

void CQuickSlotUI::render(HDC _dc)
{
	render_childUI(_dc);
}
