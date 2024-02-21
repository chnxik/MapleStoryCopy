#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"

int g_arrVK[(UINT)KEY::END]
=
{
	 VK_UP,
	 VK_DOWN,
	 VK_LEFT,
	 VK_RIGHT,

	 VK_SPACE,
	 VK_RETURN,
	 VK_ESCAPE,
	 VK_LMENU,
	 VK_LCONTROL,
	 VK_LSHIFT,
	 VK_TAB,

	 VK_LBUTTON,
	 VK_RBUTTON,

	 VK_DELETE,

	'Q',
	'W',
	'E',
	'R',

	'A',
	'S',
	'D',
	'F',

	'Z',
	'X',
	'C',
	'V',

	'T',
	'Y',
	'G',
	'H',
	'B',
	'N',

	'U',
	'I',
	'O',
	'P',
	'J',
	'K',
	'L',
	'M',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_F1,
	VK_F2,
	VK_F3,
	VK_F4,
	VK_F5,
	VK_F6,
	VK_F7,
	VK_F8,
	VK_F9,
	VK_F10,
	VK_F11,
	VK_F12,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE });
	}
}

void CKeyMgr::tick()
{
	if (GetFocus())
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			// Cur Tap
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				// Prev NONE
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				// Prev HOLD
				else
				{
					m_vecKey[i].state = KEY_STATE::HOLD;
				}
			}

			// Cur NONE
			else
			{
				// Prev NONE
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				// Prev HOLD
				else
				{
					m_vecKey[i].state = KEY_STATE::AWAY;
					m_vecKey[i].bPrev = false;
				}
			}
		}

		// Mouse 위치 갱신
		POINT ptMousePos = {};
		GetCursorPos(&ptMousePos);	// 마우스의 좌표값을 얻어온다 (모니터 좌상단 기준)
		ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMousePos); // 마우스좌표값을 현재 윈도우창의 좌상단 기준으로 설정
		m_vMousePos = ptMousePos;
	}

	// 이 window가 focus 상태가 아니다
	else
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKey[i].state
				|| KEY_STATE::HOLD == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::AWAY;
				m_vecKey[i].bPrev = false;
			}

			else if (KEY_STATE::AWAY == m_vecKey[i].state)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}

