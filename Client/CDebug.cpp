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
				(LONG)(vPos.y + 100) };	// 문자가 써질 사각형
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
		SetTextColor(_dc, RGB(0, 255, 0));	// 초록색 글씨
		swprintf_s(szbuff, L"디버그 모드 켜짐\n");

		//	else
		//	{
		//		SetTextColor(_dc, RGB(255, 0, 0));  // 붉은색 글씨
		//		swprintf_s(szbuff, L"디버그 모드 꺼짐\n");
		//	}

			// SetBkMode(_dc, TRANSPARENT);						// 문자 배경 투명 설정
		DrawText(_dc, szbuff, -1, &_rt, DT_RIGHT);		// 문자 출력
		SetTextColor(_dc, RGB(0, 0, 0));					// 검정색으로 색상 초기화

		if (_bDebugText)
		{
			SetTextColor(_dc, RGB(0, 255, 0));	// 초록색 글씨
			swprintf_s(szbuff, L"디버그 텍스트 켜짐\n");
		}
		else
		{
			SetTextColor(_dc, RGB(255, 0, 0));  // 붉은색 글씨
			swprintf_s(szbuff, L"디버그 텍스트 꺼짐\n");
		}

		_rt.top += 16;

		// SetBkMode(_dc, TRANSPARENT);						// 문자 배경 투명 설정
		DrawText(_dc, szbuff, -1, &_rt, DT_RIGHT);		// 문자 출력
	}
	SetTextColor(_dc, RGB(0, 0, 0));					// 검정색으로 색상 초기화
	
	SelectObject(_dc, hOldFont);
}