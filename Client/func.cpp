#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
#include "CLevelMgr.h"

#include "CActor.h"
#include "CTexture.h"

#include "CPlatform.h"
#include "CLevelState.h"

bool IsValid(CActor*& _pTarget)
{
	if (nullptr == _pTarget)
	{
		return false;
	}
	else if (_pTarget->IsDead())
	{
		_pTarget = nullptr;
		return false;
	}

	return true;
}

void Instantiate(CActor* _pNewAct, LAYER _eLayer)
{
	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_ACTOR;
	_evn.wParam = (DWORD_PTR)_pNewAct;
	_evn.lParam = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(_evn);
}

void Instantiate(CActor* _pNewAct, Vec2 _vPos, LAYER _eLayer)
{
	_pNewAct->SetPos(_vPos);

	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_ACTOR;
	_evn.wParam = (DWORD_PTR)_pNewAct;
	_evn.lParam = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(_evn);
}

void Instantiate(CActor* _pNewAct, Vec2 _Ldot, Vec2 _Rdot, LAYER _eLayer)
{
	CLine* pLine = dynamic_cast<CLine*>(_pNewAct);
	assert(pLine);

	pLine->SetLine(_Ldot, _Rdot);

	tEvent _evn = {};
	_evn.eType = EVENT_TYPE::CREATE_ACTOR;
	_evn.wParam = (DWORD_PTR)pLine;
	_evn.lParam = (DWORD_PTR)_eLayer;

	CEventMgr::GetInst()->AddEvent(_evn);
}

void ChangeLevel(LEVEL_TYPE _eNextLevel, UINT _iPortalNo)
{
	CLevelMgr::GetInst()->SetChangeInfo(_eNextLevel, _iPortalNo);
	CLevelMgr::GetInst()->ChangeState((CLevelState*)&CLevelState::Out);
}

void Saturate(float& _float)
{
	if (1.f < _float)
		_float = 1.f;
	if (_float < 0.f)
		_float = 0.f;
}

short GetDegree(Vec2 _Plf, Vec2 _Act)
{
	// 단위벡터로 변환
	_Act.Normalize();
	_Plf.Normalize();

	Vec2 Act = _Act;
	Vec2 Plf = _Plf;

	if (_Act.x < 0)
		Plf *= -1;

	// 두 벡터사이의 내적을 구한다.
	float theta = _Act.x * Plf.x + _Act.y * Plf.y;
	theta = acos(theta);

	// 각도로 변환하여 반환한다.
	short degree = (short)(theta * (180 / PI));


	float ExPro = _Plf.cross(_Act);
	if (0 > _Plf.x && 0 < ExPro || 0 < _Plf.x && 0 > ExPro)
		degree *= -1;
	// 외적으로 부호 판단

	return degree;
}

float GetVerticalPos(Vec2 _vTrgtPos, Vec2 _vPStrt, Vec2 _vVel)
{
	// 비교하는 선분중 같은 x좌표 부분의 y좌표를 구함
	float fDist = _vTrgtPos.x - _vPStrt.x;
	_vVel.Normalize();
	_vVel *= fDist / _vVel.x;

	return _vPStrt.y + _vVel.y;
}

void OpRender(HDC _dc, CTexture* _pTex, Vec2 _vPos, UINT _Opacity)	// 투명도 렌더
{
	if (_Opacity > 100)
		_Opacity = 100;

	float fOpacity = _Opacity * 0.01f;

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fOpacity);

	AlphaBlend(_dc
		, (int)_vPos.x,(int) _vPos.y
		, _pTex->Width()
		, _pTex->Height()
		, _pTex->GetDC()
		, 0, 0
		, _pTex->Width()
		, _pTex->Height()
		, tBlend);
}

void OpRender(HDC _dc, CTexture* _pTex, Vec2 _vPos, Vec2 _Offset, UINT _Opacity)
{
	if (_Opacity > 100)
		_Opacity = 100;

	float fOpacity = _Opacity * 0.01f;

	BLENDFUNCTION tBlend = {};

	tBlend.AlphaFormat = AC_SRC_ALPHA;
	tBlend.BlendFlags = 0;
	tBlend.BlendOp = AC_SRC_OVER;
	tBlend.SourceConstantAlpha = (int)(255.f * fOpacity);

	AlphaBlend(_dc
		, (int)_vPos.x + (int)_Offset.x, (int)_vPos.y + (int)_Offset.y
		, _pTex->Width()
		, _pTex->Height()
		, _pTex->GetDC()
		, 0, 0
		, _pTex->Width()
		, _pTex->Height()
		, tBlend);
}

