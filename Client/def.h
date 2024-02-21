#pragma once

#define SINGLE(type) public:\
					 static type* GetInst()\
						{\
							static type inst;\
							return &inst;\
						}\
					 private:\
						type();\
						~type();

#define DT CTimeMgr::GetInst()->GetDT()

#define ISTAP(key)	CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define ISHOLD(key)	CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::HOLD
#define ISAWAY(key)	CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::AWAY
#define MOUSE_POS	CKeyMgr::GetInst()->GetMousePos()

#define DEL(p)		if(nullptr != p) delete p;
#define PI			M_PI

#define CLONE(type) virtual type* Clone() { return new type(*this); }
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr; }

#define CHANGESTATE(type) (type*)&type

#define MAXSKILLLV 20

#define FLASHGVALUE 50
#define SKILLVOLUME 30
#define HITSOUND 10
#define MOBVOLUME 30

enum class LEVEL_TYPE
{
	LOGO,
	LOGIN,
	TOOL,
	STAGE01,
	STAGE02,
	STAGE03,
	STAGE04,
	STAGE05,
	STAGE06,

	END,
};

enum class FONT_TYPE
{
	DEBUG,
	UINUM,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	BOLD_RED,
	BOLD_GREEN,
	BOLD_BLUE,
	BOLD_PURPLE,

	END,
};

enum class LAYER
{
	BACKGROUND = 0,
	MAP = 1,
	PLATFORM = 2,

	MOB = 3,
	PLAYER = 4,

	MAPOBJ = 5,
	ITEM = 6,
	
	SKILL = 7,

	DAMAGESKIN = 12,
	TOOLUI = 14,
	PLAYERUI = 15,
	END = 16,
};

enum class EVENT_TYPE
{
	CREATE_ACTOR,	// wParam : Actor Adress	lParam : Layer Type
	DELETE_ACTOR,	// wParam : Actor Adress
	LEVEL_CHANGE,	// wParam : LEVEL_TYPE(Next Level Type), lParam : 포탈번호

};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SHAKE,
	NONE,
};

enum class TOOL_TYPE
{
	DRAWPLATFORM,			// 기본 플랫폼, 하향점프 가능
	DRAWEARTH,				// 땅 플랫폼, 하향점프 불가능
	DRAWWALL_LEFT,			// 왼쪽 벽,
	DRAWWALL_RIGHT,			// 오른쪽 벽,
	DRAWMOBWALL_LEFT,		// 몬스터용 왼쪽 벽,
	DRAWMOBWALL_RIGHT,		// 몬스터용 오른쪽 벽,
	DRAWROPE,				// 로프
	DRAWLADDER,				// 사다리
	CREATEMOB,				// Mob spawner 배치
	CREATENPC,
	CREATEPORTAL,
	NONE,
};

enum class CSRSTATE
{
	IDLE,
	IDLE_On,
	GRIP,
	END,
};

enum class TOOL_TAP
{
	OBJ,
	MOB,
	END,
};

enum class LIFTOBJ
{
	ROPE,
	LADDER,
};

enum class eDir
{
	LEFT,
	RIGHT,
	NONE,
};

enum class PORTAL
{
	NONE,
	PORTAL1,
	PORTAL2,
	END,
};

enum class SOUND_ETC
{
	JUMP,
	GETITEM,
	END,
};

enum class MOB_TYPE
{
	SNAIL,
	BLUESNAIL,
	MUSHMOM,
	PRIESTOFMEM,
	END,
};

enum class ITEM_TYPE
{
	REDPOTION,
	BLUEPOTION,
	ELIXIR,
	END,
};

enum class KEYSLOT_TYPE
{
	SKILL,
	ITEM,
	SYSTEM,
	NONE,
};

enum class NUMB
{
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
	_slash,
	_percent,
};

enum class SKILL
{
	STROKE,
	CHASE,
	SHOTGUN,
	KNIFE,
	BAT,
	BRICK,
	END,
};

enum DMG_TYPE
{
	PLAYER,
	MOB,
};