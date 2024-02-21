#include "pch.h"
#include "CToolInven.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCsrMgr.h"

#include "CToolLevel.h"

#include "CTexture.h"

#include "CToolCell.h"
#include "CBtnUI.h"
#include "CTab.h"

#define INVENCELLSIZE 30			// 셀 한칸의 크기
#define CELLINTERVAL 12				// 셀 간격

CToolInven::CToolInven(CToolLevel* _pLevel)
	: m_pToolLevel(_pLevel)
	, m_eCurMode(TOOL_TAP::OBJ)
	, m_pToolMod{}
	, m_arrCell{0}
	, m_pCurCell(nullptr)
{
}

CToolInven::~CToolInven()
{
}

void CToolInven::tick()
{
	CUI::tick();
}

void CToolInven::render(HDC _dc)
{
	linerender(_dc);

	CTexture* pIdleTex = GetIdleTex();

	if (nullptr == pIdleTex)	// Idle Texture를 얻어와서 nullptr일경우 return시킨다.
		return;

	OpRender(_dc, pIdleTex, GetFinalPos(), 100);

	render_childUI(_dc);
}

void CToolInven::MouseLbtnDown()
{
	CUI::MouseLbtnDown();
}

void CToolInven::MouseLbtnClicked()
{
}

void CToolInven::MouseOn()
{
	SetCsrState(CSRSTATE::IDLE);
}

void CToolInven::SetTool()
{
	m_pToolLevel->UpdateCurTool(m_pCurCell->GetCellTool(m_eCurMode),m_pCurCell);
}

void CToolInven::SetCurMode(TOOL_TAP _Mod)
{
	if (m_pCurCell != nullptr)
	{
		m_pCurCell->SetSelect(false);
		m_pCurCell = nullptr;
		CCsrMgr::GetInst()->SetItemCsr(nullptr,Vec2(0,0));

		m_pToolLevel->UpdateCurTool(TOOL_TYPE::NONE,nullptr);
	}

	m_eCurMode = _Mod;
}

void CToolInven::SelectCell(CToolCell* _Cell)
{
	// 셀 선택 상태 변경
	if (m_pCurCell != nullptr)
		m_pCurCell->SetSelect(false);

	m_pCurCell = _Cell;
	_Cell->SetSelect(true);

	// 선택된 셀로 정보 업데이트
	m_pToolLevel->UpdateCurTool(m_pCurCell->GetCellTool(m_eCurMode), m_pCurCell);
}

void CToolInven::CreateCell()
{
	Vec2 UIPos(14, 38);

	for (int iRow = 0; iRow < 5; ++iRow)
	{
		for (UINT iCol = 0; iCol < 4; ++iCol)
		{
			m_arrCell[iCol + iRow * 4] = new CToolCell(this, iCol + iRow * 4);
			m_arrCell[iCol + iRow * 4]->SetPos(UIPos);
			AddChildUI(m_arrCell[iCol + iRow * 4]);

			UIPos.x += INVENCELLSIZE + CELLINTERVAL;				// 셀크기 + 셀간격 만큼 다음 생성좌표 이동
		}
		UIPos.x = 14;												// x좌표 초기화
		UIPos.y += INVENCELLSIZE + CELLINTERVAL;
	}

	// 셀 정보 입력
	m_arrCell[0]->SetCell(TOOL_TYPE::DRAWPLATFORM,L"m_snail");
	m_arrCell[1]->SetCell(TOOL_TYPE::DRAWEARTH,L"m_bluesnail");
	m_arrCell[2]->SetCell(TOOL_TYPE::DRAWWALL_LEFT,L"m_mushmom");
	m_arrCell[3]->SetCell(TOOL_TYPE::DRAWWALL_RIGHT,L"m_priestmem");
	m_arrCell[4]->SetCellTool(TOOL_TYPE::DRAWMOBWALL_LEFT);
	m_arrCell[5]->SetCellTool(TOOL_TYPE::DRAWMOBWALL_RIGHT);
	m_arrCell[6]->SetCellTool(TOOL_TYPE::DRAWROPE);
	m_arrCell[7]->SetCellTool(TOOL_TYPE::DRAWLADDER);
	m_arrCell[8]->SetCellTool(TOOL_TYPE::CREATEPORTAL);
	
	m_arrCell[0]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawPlatform", L"texture\\tool\\cell\\DrawPlatform.png"));
	m_arrCell[1]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawEarth",L"texture\\tool\\cell\\DrawEarth.png"));
	m_arrCell[2]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawWallLeft",L"texture\\tool\\cell\\DrawWallLeft.png"));
	m_arrCell[3]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawWallRight",L"texture\\tool\\cell\\DrawWallRight.png"));
	m_arrCell[4]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawMobWallLeft",L"texture\\tool\\cell\\DrawMobWallLeft.png"));
	m_arrCell[5]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawMobWallRight",L"texture\\tool\\cell\\DrawMobWallRight.png"));
	m_arrCell[6]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawRope",L"texture\\tool\\cell\\DrawRope.png"));
	m_arrCell[7]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"DrawLadder",L"texture\\tool\\cell\\DrawLadder.png"));
	m_arrCell[8]->SetIdleTex(CResMgr::GetInst()->LoadTexture(L"CreatePortal",L"texture\\tool\\cell\\CreatePortal.png"));
	
	m_arrCell[0]->SetMobTex(CResMgr::GetInst()->LoadTexture(L"snail", L"texture\\tool\\cell\\snail.png"));
	m_arrCell[1]->SetMobTex(CResMgr::GetInst()->LoadTexture(L"bluesnail", L"texture\\tool\\cell\\bluesnail.png"));
	m_arrCell[2]->SetMobTex(CResMgr::GetInst()->LoadTexture(L"mushmom", L"texture\\tool\\cell\\mushmom.png"));
	m_arrCell[3]->SetMobTex(CResMgr::GetInst()->LoadTexture(L"priestmem", L"texture\\tool\\cell\\priestmem.png"));
}

void CToolInven::CreateBtn()
{
	SetIdleTex(CResMgr::GetInst()->LoadTexture(L"ToolInvenPN", L"texture\\tool\\ToolInvenpn2.png")); // InvenPn Texture

	// Save 버튼
	CTexture* SaveBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"toolSaveBtnIdle", L"texture\\tool\\savebtnidle.png");
	CTexture* SaveBtnOverTex = CResMgr::GetInst()->LoadTexture(L"toolSaveBtnOver",L"texture\\tool\\savebtnover.png");
	CTexture* SaveBtnPressTex = CResMgr::GetInst()->LoadTexture(L"toolSaveBtnPress",L"texture\\tool\\savebtnpress.png");

	// Load 버튼
	CTexture* LoadBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"toolLoadBtnIdleTex",L"texture\\tool\\loadbtnidle.png");
	CTexture* LoadBtnOverTex = CResMgr::GetInst()->LoadTexture(L"toolLoadBtnOverTex",L"texture\\tool\\loadbtnover.png");
	CTexture* LoadBtnPressTex = CResMgr::GetInst()->LoadTexture(L"toolLoadBtnPressTex",L"texture\\tool\\loadbtnpress.png");
	
	// 배경 이미지 버튼
	CTexture* BackGrndCreateBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"BackGrndCreateBtnIdleTex",L"texture\\tool\\bgbtnidle.png");
	CTexture* BackGrndCreateBtnOverTex = CResMgr::GetInst()->LoadTexture(L"BackGrndCreateBtnOverTex",L"texture\\tool\\bgbtnover.png");
	CTexture* BackGrndCreateBtnPressTex = CResMgr::GetInst()->LoadTexture(L"BackGrndCreatenBtnPressTex", L"texture\\tool\\bgbtnpress.png");

	// Map이미지 버튼
	CTexture* MapCreateBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"MapCreateBtnIdleTex",L"texture\\tool\\mapbtnidle.png");
	CTexture* MapCreateBtnOverTex = CResMgr::GetInst()->LoadTexture(L"MapCreateBtnOverTex",L"texture\\tool\\mapbtnover.png");
	CTexture* MapCreateBtnPressTex = CResMgr::GetInst()->LoadTexture(L"MapCreateBtnPressTex",L"texture\\tool\\mapbtnpress.png");
	

	// 배경음악 버튼
	CTexture* BGMCreateBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"BGMCreateBtnIdleTex", L"texture\\tool\\noteidle.png");
	CTexture* BGMCreateBtnOverTex = CResMgr::GetInst()->LoadTexture(L"BGMCreateBtnOverTex", L"texture\\tool\\noteover.png");
	CTexture* BGMCreateBtnPressTex = CResMgr::GetInst()->LoadTexture(L"BGMCreatenBtnPressTex", L"texture\\tool\\notepress.png");

	// OBJ 탭 버튼
	CTexture* ObjTabselectedTex = CResMgr::GetInst()->LoadTexture(L"ObjTabselectedTex", L"texture\\tool\\tabobj.png");
	CTexture* ObjTabdeselectedTex = CResMgr::GetInst()->LoadTexture(L"ObjTabdeselectedTex", L"texture\\tool\\tabobj_d.png");

	// MOB 탭 버튼
	CTexture* MobTabselectedTex = CResMgr::GetInst()->LoadTexture(L"MobTabselectedTex", L"texture\\tool\\tabmob.png");
	CTexture* MobTabdeselectedTex = CResMgr::GetInst()->LoadTexture(L"MobTabdeselectedTex", L"texture\\tool\\tabmob_d.png");


	
	// 버튼 생성
	CBtnUI* BtnUI = new CBtnUI;

	// 맵 세이브 버튼
	BtnUI->SetName(L"mpSaveBtn");
	BtnUI->SetIdleTex(SaveBtnIdleTex);
	BtnUI->SetMsOverTex(SaveBtnOverTex);
	BtnUI->SetMsPressTex(SaveBtnPressTex);
	BtnUI->SetScale(Vec2(65, 24));
	BtnUI->SetPos(Vec2(18, 255));
	BtnUI->SetOffset(Vec2(-12, -15));
	BtnUI->SetDelegate(m_pToolLevel, (DELEGATE)&CToolLevel::SaveMap);
	AddChildUI((CUI*)BtnUI);

	// 맵 로드 버튼
	BtnUI = new CBtnUI;
	BtnUI->SetName(L"mpLoadBtn");
	BtnUI->SetIdleTex(LoadBtnIdleTex);
	BtnUI->SetMsOverTex(LoadBtnOverTex);
	BtnUI->SetMsPressTex(LoadBtnPressTex);
	BtnUI->SetScale(Vec2(65, 24));
	BtnUI->SetPos(Vec2(102, 255));
	BtnUI->SetOffset(Vec2(-12, -15));
	BtnUI->SetDelegate(m_pToolLevel, (DELEGATE)&CToolLevel::LoadMap);
	AddChildUI((CUI*)BtnUI);

	// 맵 배경 생성 버튼
	BtnUI = new CBtnUI;
	BtnUI->SetName(L"BgCreateBtn");
	BtnUI->SetIdleTex(BackGrndCreateBtnIdleTex);
	BtnUI->SetMsOverTex(BackGrndCreateBtnOverTex);
	BtnUI->SetMsPressTex(BackGrndCreateBtnPressTex);
	BtnUI->SetPos(Vec2(83, 8));
	BtnUI->SetDelegate(m_pToolLevel, (DELEGATE)&CToolLevel::CreateBackgrnd);
	AddChildUI((CUI*)BtnUI);

	// 맵 이미지 생성 버튼
	BtnUI = new CBtnUI;
	BtnUI->SetName(L"mpCreateBtn");
	BtnUI->SetIdleTex(MapCreateBtnIdleTex);
	BtnUI->SetMsOverTex(MapCreateBtnOverTex);
	BtnUI->SetMsPressTex(MapCreateBtnPressTex);
	BtnUI->SetPos(Vec2(122, 8));
	BtnUI->SetDelegate(m_pToolLevel, (DELEGATE)&CToolLevel::CreateMap);
	AddChildUI((CUI*)BtnUI);

	// 배경음악 생성 버튼
	BtnUI = new CBtnUI;
	BtnUI->SetName(L"bgmCreateBtn");
	BtnUI->SetIdleTex(BGMCreateBtnIdleTex);
	BtnUI->SetMsOverTex(BGMCreateBtnOverTex);
	BtnUI->SetMsPressTex(BGMCreateBtnPressTex);
	BtnUI->SetPos(Vec2(161, 8));
	BtnUI->SetDelegate(m_pToolLevel, (DELEGATE)&CToolLevel::CreateBgm);
	AddChildUI((CUI*)BtnUI);

	// 오브젝트 탭 
	CTab* TabUI = new CTab;
	TabUI->SetName(L"tabobj");
	TabUI->SetIdleTex(ObjTabdeselectedTex);
	TabUI->SetSelectedTex(ObjTabselectedTex); 
	TabUI->SetMod(TOOL_TAP::OBJ);
	TabUI->SetPos(Vec2(7, 5));
	m_pToolMod[(UINT)TOOL_TAP::OBJ] = TabUI;
	AddChildUI((CUI*)TabUI);

	// 몬스터 탭
	TabUI = new CTab;
	TabUI->SetName(L"tabmob");
	TabUI->SetIdleTex(MobTabdeselectedTex);
	TabUI->SetSelectedTex(MobTabselectedTex); 
	TabUI->SetMod(TOOL_TAP::MOB);
	TabUI->SetPos(Vec2(42, 5));
	m_pToolMod[(UINT)TOOL_TAP::MOB] = TabUI;
	AddChildUI((CUI*)TabUI);
}