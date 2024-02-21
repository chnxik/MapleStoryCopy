#include "pch.h"
#include "CDebug.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"


CDebug::CDebug()
	: _bDebug(false)
	, _bDebugText(false)
	, _textRT{}
{
}

CDebug::~CDebug()
{
}


void CDebug::init()
{
	Vec2 vPos = CEngine::GetInst()->GetResolution();

	_textRT = { (LONG)(vPos.x - 400),
				(LONG)(10),
				(LONG)(vPos.x - 10),
				(LONG)(vPos.y + 100) };	// ���ڰ� ���� �簢��
}

void CDebug::tick()
{
	if (ISTAP(KEY::F1))
	{
		if (_bDebug == true)
		{
			_bDebug = false;
			_bDebugText = false;
		}
		else
		{
			_bDebug = true;
		}
	}

	if (_bDebug == true)
	{
		if (ISTAP(KEY::F2))
		{
			if (_bDebugText == true)
			{
				_bDebugText = false;
			}
			else
			{
				_bDebugText = true;
			}
		}
	}
}

void CDebug::render(HDC _dc)
{
	wchar_t szbuff[256] = {};
	RECT _rt = _textRT;

	HFONT hOldFont;
	hOldFont = (HFONT)SelectObject(_dc, CEngine::GetInst()->GetFONT(FONT_TYPE::DEBUG));

	if (_bDebug)
	{
		SetTextColor(_dc, RGB(0, 255, 0));	// �ʷϻ� �۾�
		swprintf_s(szbuff, L"����� ��� ����\n");

		//	else
		//	{
		//		SetTextColor(_dc, RGB(255, 0, 0));  // ������ �۾�
		//		swprintf_s(szbuff, L"����� ��� ����\n");
		//	}

			// SetBkMode(_dc, TRANSPARENT);						// ���� ��� ���� ����
		DrawText(_dc, szbuff, -1, &_rt, DT_RIGHT);		// ���� ���
		SetTextColor(_dc, RGB(0, 0, 0));					// ���������� ���� �ʱ�ȭ

		if (_bDebugText)
		{
			SetTextColor(_dc, RGB(0, 255, 0));	// �ʷϻ� �۾�
			swprintf_s(szbuff, L"����� �ؽ�Ʈ ����\n");
		}
		else
		{
			SetTextColor(_dc, RGB(255, 0, 0));  // ������ �۾�
			swprintf_s(szbuff, L"����� �ؽ�Ʈ ����\n");
		}

		_rt.top += 16;

		// SetBkMode(_dc, TRANSPARENT);						// ���� ��� ���� ����
		DrawText(_dc, szbuff, -1, &_rt, DT_RIGHT);		// ���� ���
	}
	SetTextColor(_dc, RGB(0, 0, 0));					// ���������� ���� �ʱ�ȭ
	
	SelectObject(_dc, hOldFont);
}