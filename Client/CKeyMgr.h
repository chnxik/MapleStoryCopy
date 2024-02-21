#pragma once

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,

	LBTN,
	RBTN,

	DEL,

	Q,
	W,
	E,
	R,

	A,
	S,
	D,
	F,

	Z,
	X,
	C,
	V,

	T,
	Y,
	G,
	H,
	B,
	N,

	U,
	I,
	O,
	P,
	J,
	K,
	L,
	M,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	END,

	
};

enum class KEY_STATE
{
	TAP,
	HOLD,
	AWAY,
	NONE,
};

struct tKeyInfo
{
	KEY			key;
	KEY_STATE	state;
	bool		bPrev;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vMousePos;

public:
	void init();
	void tick();


public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKey[(UINT)_key].state; }
	Vec2 GetMousePos() { return m_vMousePos; }
};

