#pragma once

class CTexture;
class CActor;

bool IsValid(CActor*& _pTarget);

void Instantiate(CActor* _pNewAct, LAYER _eLayer);
void Instantiate(CActor* _pNewAct, Vec2 _vPos, LAYER _eLayer);
void Instantiate(CActor* _pNewAct, Vec2 _Ldot, Vec2 _Rdot, LAYER _eLayer);
void ChangeLevel(LEVEL_TYPE _eNextLevel, UINT _iPortalNo);
void Saturate(float& _float);

short GetDegree(Vec2 _Vec1, Vec2 _Vec2);
float GetVerticalPos(Vec2 _vTrgtPos, Vec2 _vPStrt, Vec2 _vVel);

void OpRender(HDC _dc, CTexture* _pTex, Vec2 _vPos, UINT _Opacity = 100);
void OpRender(HDC _dc, CTexture* _pTex, Vec2 _vPos, Vec2 _Offset, UINT _Opacity = 100);