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
	if (IsLbtnDown())								// Lbtn ������
	{
		Vec2 vMove = MOUSE_POS - m_vPressPos;		// ���� ���콺�� ��ġ���� ������ �������ִ� ���콺 ��ġ�� ��, �̵��� ���Ͱ��� ���Ѵ�.

		Vec2 vPos = GetPos();						// UI�� ��ġ�� �����´�.
		vPos += vMove;								// ���콺�� �̵���Ų �Ÿ���ŭ UI�� ��ġ�� �����ش�.
		SetPos(vPos);								// �ٽ� UI�� ��ġ�� ���Ѵ�.

		m_vPressPos = MOUSE_POS;					// �׸��� �������ִ� ��ġ�� ���� ���콺��ġ�� ��ü��Ų��.
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
	m_vPressPos = MOUSE_POS; // ���콺�� ���������� ��, ���콺�� ���� ��ǥ�� �޾ƿ´�.
}

void CPNUI::MouseLbtnClicked()
{
}

void CPNUI::MouseOn()
{
	SetCsrState(CSRSTATE::IDLE_On);
}

