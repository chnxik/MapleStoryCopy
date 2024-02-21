#include "pch.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CUIMgr.h"
#include "CSoundMgr.h"
#include "CAnimationMgr.h"
#include "CCsrMgr.h"
#include "CPlayerMgr.h"
#include "CItemMgr.h"

#include "CCamera.h"

#include "CSound.h"
#include "CTexture.h"

CEngine::CEngine()
	: m_hMainWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_arrPen{}
	, m_pMemTex(nullptr)
	, m_arrFont{}
{

}

CEngine::~CEngine()
{
	// MainWnd�� ����� DC ����
	ReleaseDC(m_hMainWnd, m_hDC);

	// ������ PenObj ����
	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	for (UINT i = 0; i < (UINT)FONT_TYPE::END; ++i)
	{
		DeleteObject(m_arrFont[i]);
	}
}

void CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hMainWnd = _hWnd;
	
	// HDC �ʱ�ȭ, ���� ����
	m_hDC = GetDC(m_hMainWnd);

	// ������ ũ�� ����
	ChangeWindowSize(_iWidth, _iHeight);

	// ���� ����ϴ� Pen �� Brush ����
	CreatePenBrush();

	// ��Ʈ ���� �� ����
	CreateMyFont();

	// Manager �ʱ�ȭ

	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSoundMgr::GetInst()->init();
	CAnimationMgr::GetInst()->init();
	CPlayerMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();
	CCsrMgr::GetInst()->init();
	CDebug::GetInst()->init();
}

void CEngine::progress()
{
	tick();

	render();

	// ���� �����ӿ� ����� �̺�Ʈ ó���� ���� �̺�Ʈ �Ŵ��� ȣ��
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	CTimeMgr::GetInst()->tick();

	CKeyMgr::GetInst()->tick();

	CCamera::GetInst()->tick();

	CPlayerMgr::GetInst()->tick();

	CLevelMgr::GetInst()->tick();

	CCollisionMgr::GetInst()->tick();

	CUIMgr::GetInst()->tick();

	CCsrMgr::GetInst()->tick();

	CDebug::GetInst()->tick();
}

void CEngine::render()
{
	// ȭ�� Ŭ����
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// ���� ����
	CLevelMgr::GetInst()->render(m_pMemTex->GetDC());

	// Camera Blind
	CCamera::GetInst()->render(m_pMemTex->GetDC());
	
	CCsrMgr::GetInst()->render(m_pMemTex->GetDC());

	CDebug::GetInst()->render(m_pMemTex->GetDC());

	CTimeMgr::GetInst()->render(m_pMemTex->GetDC());

	// MemBitMap -> MainWindowBitmap
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	// TimeMgr ������
}

void CEngine::ChangeWindowSize(UINT _iWidth, UINT _iHeight)
{
	m_ptResolution.x = _iWidth;
	m_ptResolution.y = _iHeight;

	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };

	HMENU hMenu = GetMenu(m_hMainWnd);

	if (nullptr != hMenu)
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	else
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);


	POINT WindowLeftTopPos = { (GetSystemMetrics(SM_CXSCREEN) - rt.right) / 2,(GetSystemMetrics(SM_CYSCREEN) - rt.bottom) / 2 };
	

	SetWindowPos(m_hMainWnd, nullptr, WindowLeftTopPos.x, WindowLeftTopPos.y, rt.right - rt.left, rt.bottom - rt.top, 0);


	// ����� ����
	if (nullptr == m_pMemTex)
	{
		// ����� �� ��Ʈ�� ����
		m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", m_ptResolution.x, m_ptResolution.y);
	}

	// ����۰� ������, ����� �ػ󵵿� ���߾� ũ�� ������
	else
	{
		m_pMemTex->Resize(m_ptResolution.x, m_ptResolution.y);
	}
}

void CEngine::CreatePenBrush()
{
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	m_arrPen[(UINT)PEN_TYPE::BOLD_RED] = CreatePen(PS_SOLID, 4, RGB(255, 50, 50));
	m_arrPen[(UINT)PEN_TYPE::BOLD_GREEN] = CreatePen(PS_SOLID, 4, RGB(128, 230, 50));
	m_arrPen[(UINT)PEN_TYPE::BOLD_BLUE] = CreatePen(PS_SOLID, 4, RGB(50, 50, 255));
	m_arrPen[(UINT)PEN_TYPE::BOLD_PURPLE] = CreatePen(PS_SOLID, 4, RGB(255, 50, 255));
}

void CEngine::CreateMyFont()
{

	m_arrFont[(UINT)FONT_TYPE::DEBUG] = CreateFont(15, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("����"));
	m_arrFont[(UINT)FONT_TYPE::UINUM] = CreateFont(11, 0, 0, 0, FW_THIN, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, FIXED_PITCH, TEXT("����"));
	
}
