#include "pch.h"
#include "CPNUI.h"

#include "CKeyMgr.h"
#include "CTexture.h"

CPNUI::CPNUI()
{
}

CPNUI::~CPNUI()
{
}

void CPNUI::tick()
{
	if (IsLbtnDown())								// Lbtn 눌리면
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;		// 현재 마우스의 위치에서 기존에 눌려져있던 마우스 위치를 빼, 이동한 벡터값을 구한다.

		Vec2 vPos = GetPos();						// UI의 위치를 가져온다.
		vPos += vMove;								// 마우스로 이동시킨 거리만큼 UI의 위치에 더해준다.
		SetPos(vPos);								// 다시 UI의 위치를 정한다.

		m_vPressPos = MOUSE_POS;					// 그리고 눌려져있는 위치를 현재 마우스위치로 대체시킨다.
	}

	CUI::tick();
}

void CPNUI::render(HDC _dc)
{
	linerender(_dc);

	CTexture* pIdleTex = GetIdleTex();
	
	if (nullptr != pIdleTex)
	{
		OpRender(_dc, pIdleTex, GetFinalPos(), 100);
	}

	render_childUI(_dc);
}

void CPNUI::MouseLbtnDown()
{
	CUI::MouseLbtnDown();
	m_vPressPos = MOUSE_POS; // 마우스가 눌러져있을 때, 마우스의 현재 좌표를 받아온다.
}

void CPNUI::MouseLbtnClicked()
{
}

void CPNUI::MouseOn()
{
	SetCsrState(CSRSTATE::IDLE_On);
}

