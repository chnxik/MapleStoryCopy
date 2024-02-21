#include "pch.h"
#include "CSkillSLot.h"

#include "CResMgr.h"

#include "CPlayerMgr.h"
#include "CKeyMgr.h"

#include "CQuickSlotUI.h"

#include "CEngine.h"
#include "CPlayerMgr.h"
#include "CBtnUI.h"


CSkillSLot::CSkillSLot(const wchar_t* _skillName, SKILL _skill)
	: m_strSkillName(_skillName)
	, m_pDisTex(nullptr)
	, m_eSkill(_skill)
	, m_iSkillLv(0)
	, m_rtSkillName{}
	, m_rtSkillLv{}
	, m_btnSkillPoint(nullptr)
	, m_bActive(false)
{
	init();
}

CSkillSLot::~CSkillSLot()
{
}

void CSkillSLot::init()
{
	m_btnSkillPoint = new CBtnUI;

	m_btnSkillPoint->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillbtn_idle", L"texture\\UI\\WindowUI\\SkillWindow\\skillupbtn_idle.png"));
	m_btnSkillPoint->SetMsOverTex(CResMgr::GetInst()->LoadTexture(L"Skillbtn_over", L"texture\\UI\\WindowUI\\SkillWindow\\skillupbtn_over.png"));
	m_btnSkillPoint->SetMsPressTex(CResMgr::GetInst()->LoadTexture(L"Skillbtn_pressed", L"texture\\UI\\WindowUI\\SkillWindow\\skillupbtn_pressed.png"));
	m_btnSkillPoint->SetDisAbleTex(CResMgr::GetInst()->LoadTexture(L"Skillbtn_dis", L"texture\\UI\\WindowUI\\SkillWindow\\skillupbtn_dis.png"));

	m_btnSkillPoint->SetPos(Vec2(123, 19));
	m_btnSkillPoint->SetDelegate(this, (DELEGATE)&CSkillSLot::SkillPointUp);

	AddChildUI(m_btnSkillPoint);
}

void CSkillSLot::SkillPointUp()
{
	CPlayerMgr::GetInst()->AddSkillLv(m_eSkill);
}

void CSkillSLot::MouseLbtnDown()
{
	if (m_bActive)
	{
		CUI::MouseLbtnDown();
		CQuickSlotUI* QuickSlot = CPlayerMgr::GetInst()->GetQuickSlot();
		QuickSlot->SetSlotType(KEYSLOT_TYPE::SKILL);	// 슬롯타입 :: 스킬로 등록
		QuickSlot->SelectSkill(m_eSkill);				// 스킬정보 저장
		QuickSlot->SelectTex(GetIdleTex());				// 스킬 아이콘 텍스쳐 저장
	}

}

void CSkillSLot::tick()
{
	Vec2 vPos = GetFinalPos();

	m_rtSkillName = {
		(LONG)(vPos.x + 39),
		(LONG)(vPos.y + 2),
		(LONG)(vPos.x + 39 + 98),
		(LONG)(vPos.y + 15) 
	};

	m_rtSkillLv = {
		(LONG)(vPos.x + 39),
		(LONG)(vPos.y + 19),
		(LONG)(vPos.x + 39 + 83),
		(LONG)(vPos.y + 32) 
	};


	m_iSkillLv = CPlayerMgr::GetInst()->GetSkillLv(m_eSkill);
	
	if (0 < m_iSkillLv)
		m_bActive = true;

	CUI::tick();
}

void CSkillSLot::render(HDC _dc)
{
	CTexture* pCurTex;

	if (m_bActive)
		pCurTex = GetIdleTex();
	else
		pCurTex = m_pDisTex;

	if (nullptr == pCurTex)	// Idle Texture를 얻어와서 nullptr일경우 return시킨다.
		return;

	OpRender(_dc, pCurTex, GetFinalPos(), 100);

	HFONT hOldFont;
	hOldFont = (HFONT)SelectObject(_dc, CEngine::GetInst()->GetFONT(FONT_TYPE::UINUM));

	DrawText(_dc, m_strSkillName, -1, &m_rtSkillName, DT_LEFT);	// 문자 출력

	wchar_t szbuff[3] = {};

	swprintf_s(szbuff, L"%d", m_iSkillLv); // 스킬포인트
	DrawText(_dc, szbuff, -1, &m_rtSkillLv , DT_LEFT);	// 문자 출력

	if (IsLbtnDown())
		OpRender(_dc, pCurTex, CKeyMgr::GetInst()->GetMousePos() - GetScale()/2.f, 70);

	CUI::render_childUI(_dc);

	SelectObject(_dc, hOldFont);
}