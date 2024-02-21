#include "pch.h"
#include "CDummy.h"

#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CCamera.h"

#include "CBtnUI.h"
#include "CToolLevel.h"
#include "CLevel.h"
#include "CTexture.h"
#include "CActor.h"

#include "CPlatform.h"
#include "CWall.h"
#include "CRope.h"
#include "CLadder.h"
#include "CLine.h"
#include "CSpawner.h"

UINT CDummy::g_iNextDummyKey = 0;

CDummy::CDummy()
    : m_DummyKey(g_iNextDummyKey++)
    , m_UseTOOL(TOOL_TYPE::NONE)
    , m_LayerInfo(LAYER::END)
    , m_VecInfo1{}
    , m_VecInfo2{}
    , m_binfo(false)
    , m_eInfo(0)
    , m_pActor(nullptr)
{
}

CDummy::~CDummy()
{
}

void CDummy::tick()
{
    SetPos(CCamera::GetInst()->GetRenderPos(m_pActor->GetPos()));
    CUI::tick();
}

void CDummy::SetLineDummy(CLine* _Line, TOOL_TYPE _Tool, LAYER _LAYER)
{
    m_VecInfo1 = _Line->GetLdot();
    m_VecInfo2 = _Line->GetRdot();
    m_UseTOOL = _Tool;
    m_pActor = _Line;
    m_LayerInfo = _LAYER;
    
    switch (_Tool)
    {
    case TOOL_TYPE::DRAWPLATFORM:
    case TOOL_TYPE::DRAWEARTH:
        m_binfo = ((CPlatform*)_Line)->IsEarth();
        break;
    case TOOL_TYPE::DRAWWALL_LEFT:
    case TOOL_TYPE::DRAWWALL_RIGHT:
    case TOOL_TYPE::DRAWMOBWALL_LEFT:
    case TOOL_TYPE::DRAWMOBWALL_RIGHT:
    {
        m_binfo = ((CWall*)_Line)->GetOnlyMob();
        m_eInfo = (UINT)((CWall*)_Line)->GetWallDir();
    }
        break;
    }

    SetPos(CCamera::GetInst()->GetRenderPos(_Line->GetPos()));
    SetScale(_Line->GetScale());
    CreateDeleteBtn();
    SetName(L"LineDummy");
}

void CDummy::SetObjDummy(CActor* _Act, TOOL_TYPE _Tool, LAYER _LAYER)
{
    m_VecInfo1 = _Act->GetPos();
    m_VecInfo2 = _Act->GetScale();
    m_UseTOOL = _Tool;
    m_pActor = _Act;
    m_LayerInfo = _LAYER;

    switch (_Tool)
    {
    case TOOL_TYPE::CREATEMOB:
        m_eInfo = ((CSpawner*)_Act)->GeteMob();
        m_MgrKey = ((CSpawner*)_Act)->GetMobKey();
        break;
    case TOOL_TYPE::CREATENPC:
        break;
    case TOOL_TYPE::CREATEPORTAL:
        break;
    }
    SetPos(CCamera::GetInst()->GetRenderPos(_Act->GetPos()));
    SetScale(_Act->GetScale());
    CreateDeleteBtn();
    SetName(L"MapObjDummy");
}

void CDummy::CreateDeleteBtn()
{
    CTexture* DeleteBtnIdleTex = CResMgr::GetInst()->LoadTexture(L"BtCloseIdle", L"texture\\tool\\BtClose_idle.png");
    CTexture* DeleteBtnOverTex = CResMgr::GetInst()->LoadTexture(L"BtCloseOver", L"texture\\tool\\BtClose_over.png");
    CTexture* DeleteBtnPressTex = CResMgr::GetInst()->LoadTexture(L"BtClosePressed", L"texture\\tool\\BtClose_pressed.png");

    CBtnUI* DeleteBtn = new CBtnUI;

    DeleteBtn->SetName(L"DeleteBtn");
    DeleteBtn->SetIdleTex(DeleteBtnIdleTex);
    DeleteBtn->SetMsOverTex(DeleteBtnOverTex);
    DeleteBtn->SetMsPressTex(DeleteBtnPressTex);
    DeleteBtn->SetDelegate(this, (DELEGATE)&CDummy::SelfDelete);
    DeleteBtn->SetPos(Vec2(0, 0));
    DeleteBtn->SetDebugBtn();
    this->AddChildUI(DeleteBtn);
}

void CDummy::SelfDelete()
{
    CToolLevel* pToolLevel = dynamic_cast<CToolLevel*>(CLevelMgr::GetInst()->GetCurLevel());
    assert(pToolLevel);
    if (pToolLevel)
    {
        pToolLevel->DeleteDummy(m_DummyKey);
    }
}

void CDummy::MouseLbtnDown()
{
}

void CDummy::MouseLbtnClicked()
{
}

void CDummy::MouseOn()
{
}

