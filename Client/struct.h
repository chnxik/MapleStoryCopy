#pragma once

struct Vec2
{
	float x;
	float y;

public:
	inline bool IsZero() { return x == 0.f && y == 0.f; }
	inline float Length() { return sqrtf(x * x + y * y); }
	void Normalize() { float fDist = Length(); if (fDist) { x /= fDist; y /= fDist; } }
	float cross(const Vec2& _vOther) { return (x * -(_vOther.y)) - (y * -(_vOther.x)); } // 백터의 외적. 시계방향 : 양수, 반시계방향 : 음수, 평행 : 0

	Vec2 operator + (Vec2 _vOther) { return Vec2(x + _vOther.x, y + _vOther.y); }
	Vec2 operator - (Vec2 _vOther) { return Vec2(x - _vOther.x, y - _vOther.y); }
	Vec2 operator * (Vec2 _vOther) { return Vec2(x * _vOther.x, y * _vOther.y); }
	Vec2 operator / (Vec2 _vOther) { return Vec2(x / _vOther.x, y / _vOther.y); }

	void operator += (Vec2 _vOther) { x += _vOther.x; y += _vOther.y; }
	void operator -= (Vec2 _vOther) { x -= _vOther.x; y -= _vOther.y; }
	void operator *= (Vec2 _vOther) { x *= _vOther.x; y *= _vOther.y; }
	void operator /= (Vec2 _vOther) { x /= _vOther.x; y /= _vOther.y; }

	Vec2 operator + (float _f) { return Vec2(x + _f, y + _f); }
	Vec2 operator - (float _f) { return Vec2(x - _f, y - _f); }
	Vec2 operator * (float _f) { return Vec2(x * _f, y * _f); }
	Vec2 operator / (float _f) { return Vec2(x / _f, y / _f); }

	void operator += (float _f) { x += _f; y += _f; }
	void operator -= (float _f) { x -= _f; y -= _f; }
	void operator *= (float _f) { x *= _f; y *= _f; }
	void operator /= (float _f) { x /= _f; y /= _f; }

	bool operator == (Vec2 _vOther) { return ((this->x == _vOther.x) && (this->y == _vOther.y)); }
	bool operator != (Vec2 _vOther) { return !(*this == _vOther); }

	Vec2 operator - () { return Vec2(-x, -y); }


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{
	}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vec2(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}

	Vec2(short _x, short _y)
		: x((short)_x)
		, y((short)_y)
	{
	}

	Vec2(int _i)
		: x((float)_i)
		, y((float)_i)
	{
	}

	~Vec2()
	{
	}
};


union __LINE
{
	struct
	{
		short Ldx;
		short Ldy;
		short Rdx;
		short Rdy;
	};

	UINT_PTR LINE;
};

struct tEvent
{
	EVENT_TYPE	eType;
	DWORD_PTR	wParam;
	DWORD_PTR	lParam;
};

struct tAnimFrm
{
	Vec2	vLeftTop;		// 이미지 내에서 프레임의 좌상단 위치
	Vec2	vSize;			// 프레임 사이즈
	Vec2	vOffset;		// 추가 이동
	float	fDuration;		// 해당 프레임 노출 시간
};

struct tAnimInfo
{
	wstring				strAnimName;
	wstring				strAtlasKey;
	wstring				strAtlasPath;
	wstring				strSoundKey;
	wstring				strSoundPath;
	bool				bUseSound;
	UINT				iFrmCnt;
	vector<tAnimFrm>	vecFrm;
};

struct tMapObjInfo
{
	UINT id;
	LAYER Layer;
	Vec2 coordinate;
};

struct tMap
{
	wstring _strBGrndKey;
	wstring _strBGrndRelativePath;
	wstring _strMapKey;
	wstring _strMapRelativePath;
	vector<tMapObjInfo> _vecMOInfo;
};

struct tStatus
{
	UINT Lv;
	UINT MaxExp;
	UINT Exp;

	UINT MaxHP;
	int HP;
	UINT MaxMP;
	int MP;

	UINT MAXATK;
	UINT MINATK;
	UINT DEF;

	UINT StatPoint;
	UINT SkillPoint;
};

struct tSkillInfo
{
	float	fCoolTime;
	float	fAcc;
	int		iMP;
	bool	bAble;
	UINT	Key;
};