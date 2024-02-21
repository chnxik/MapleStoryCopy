#include "pch.h"
#include "CPlayerSkillWin.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CPlayerMgr.h"

#include "CPNUI.h"
#include "CLayerUI.h"
#include "CBtnUI.h"
#include "CSkillSLot.h"

#include "CTexture.h"

#include "CPlayer.h"
#include "CSound.h"

CPlayerSkillWin::CPlayerSkillWin(CPlayer* pPlayer)
	: m_pPlayer(pPlayer)
	, m_pPNUI(nullptr)
	, m_arrSkillSlot{nullptr}
	, m_rtSkillpt{}


{
	init();
}

CPlayerSkillWin::~CPlayerSkillWin()
{
	
}

void CPlayerSkillWin::init()
{
	SetClose();

	m_pPNUI = new CPNUI;
	CLayerUI* pLayerUI = new CLayerUI;

	m_pPNUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"SkillUIBackgrnd", L"texture\\UI\\WindowUI\\SKillWindow\\backgrnd.png"));
	pLayerUI->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"SkillUILayer", L"texture\\UI\\WindowUI\\SkillWindow\\layer.png"));


	// 포지션 셋팅
	Vec2 vPos = CEngine::GetInst()->GetResolution();
	vPos.x *= 3.f / 4.f;
	vPos.y *= 1.f / 8.f;

	m_pPNUI->SetPos(vPos);
	pLayerUI->SetPos(Vec2(5, 16));

	AddChildUI(m_pPNUI);
	m_pPNUI->AddChildUI(pLayerUI);
	
	SetSkillInfo();
	

	
}

void CPlayerSkillWin::SetBtnActive(bool _b)
{
	for (int i = 0; i < (UINT)SKILL::END; ++i)
	{
		if(CPlayerMgr::GetInst()->GetSkillLv((SKILL)i) < MAXSKILLLV)
			m_arrSkillSlot[i]->GetSkillPointBtn()->SetActive(_b);
		else
			m_arrSkillSlot[i]->GetSkillPointBtn()->SetActive(false);
	}
}

void CPlayerSkillWin::SetSkillInfo()
{
	m_arrSkillSlot[(UINT)SKILL::STROKE] = new CSkillSLot(L"체인아츠::스트로크", SKILL::STROKE);
	m_arrSkillSlot[(UINT)SKILL::CHASE] = new CSkillSLot(L"체인아츠::체이스", SKILL::CHASE);
	m_arrSkillSlot[(UINT)SKILL::SHOTGUN] = new CSkillSLot(L"슈팅 샷건", SKILL::SHOTGUN);
	m_arrSkillSlot[(UINT)SKILL::KNIFE] = new CSkillSLot(L"슬래싱 나이프", SKILL::KNIFE);
	m_arrSkillSlot[(UINT)SKILL::BAT] = new CSkillSLot(L"비팅 니들배트", SKILL::BAT);
	m_arrSkillSlot[(UINT)SKILL::BRICK] = new CSkillSLot(L"스트리이킹 브릭", SKILL::BRICK);

	m_arrSkillSlot[(UINT)SKILL::STROKE]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_stroke_a", L"texture\\UI\\SKill\\stroke.png"));
	m_arrSkillSlot[(UINT)SKILL::CHASE]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_scimitar_a", L"texture\\UI\\SKill\\scimitar_a.png"));
	m_arrSkillSlot[(UINT)SKILL::SHOTGUN]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_shotgun_a", L"texture\\UI\\SKill\\shotgun_a.png"));
	m_arrSkillSlot[(UINT)SKILL::KNIFE]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_knife_a", L"texture\\UI\\SKill\\knife_a.png"));
	m_arrSkillSlot[(UINT)SKILL::BAT]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_bat_a", L"texture\\UI\\SKill\\bat_a.png"));
	m_arrSkillSlot[(UINT)SKILL::BRICK]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_brick_a", L"texture\\UI\\SKill\\brick_a.png"));

	m_arrSkillSlot[(UINT)SKILL::STROKE]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_stroke_a", L"texture\\UI\\SKill\\stroke.png"));
	m_arrSkillSlot[(UINT)SKILL::CHASE]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_scimitar_d", L"texture\\UI\\SKill\\scimitar_d.png"));
	m_arrSkillSlot[(UINT)SKILL::SHOTGUN]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_shotgun_d", L"texture\\UI\\SKill\\shotgun_d.png"));
	m_arrSkillSlot[(UINT)SKILL::KNIFE]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_knife_d", L"texture\\UI\\SKill\\knife_d.png"));
	m_arrSkillSlot[(UINT)SKILL::BAT]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_bat_d", L"texture\\UI\\SKill\\bat_d.png"));
	m_arrSkillSlot[(UINT)SKILL::BRICK]->SetDisTex(CResMgr::GetInst()->LoadTexture(L"Skillicon_brick_d", L"texture\\UI\\SKill\\brick_d.png"));

	for (int i = 0; i < (UINT)SKILL::END; ++i)
	{
		m_arrSkillSlot[i]->SetPos(Vec2(15, 25 + i * 39));
		m_pPNUI->AddChildUI(m_arrSkillSlot[i]);
	}
}

void CPlayerSkillWin::tick()
{
	if (0 < m_pPlayer->GetStatus().SkillPoint)
		SetBtnActive(true);
	else
		SetBtnActive(false);



	Vec2 vPos = m_pPNUI->GetFinalPos();

	m_rtSkillpt = {
			(LONG)(vPos.x + 131),
			(LONG)(vPos.y + 266),
			(LONG)(vPos.x + 131 + 23),
			(LONG)(vPos.y + 266 + 12) };

	CUI::tick();
}

void CPlayerSkillWin::render(HDC _dc)
{
	HFONT hOldFont;
	hOldFont = (HFONT)SelectObject(_dc, CEngine::GetInst()->GetFONT(FONT_TYPE::UINUM));

	CUI::render_childUI(_dc);


	SetBkMode(_dc, TRANSPARENT);

	wchar_t szbuff[256] = {};

	swprintf_s(szbuff, L"%d", (int)m_pPlayer->GetStatus().SkillPoint); // 스킬포인트
	DrawText(_dc, szbuff, -1, &m_rtSkillpt, DT_RIGHT);	// 문자 출력

	SelectObject(_dc, hOldFont);
}

