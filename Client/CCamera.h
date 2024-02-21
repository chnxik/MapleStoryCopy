#pragma once

class CTexture;
class CLevel;
class CActor;
class CMap;

struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;
	float			m_fAccTime;
	float			m_fMaxTime;
};

class CCamera
{
	SINGLE(CCamera);
private:
	Vec2				m_vLook;
	Vec2				m_vDiff;
	CTexture*			m_pBlindTex;
	CActor*				m_pTarget;

	list<tCamEffect>	m_CamEffectList;
	float				m_fRatio;

	Vec2				m_vOffset;

	float				m_fShakeRatio;

	Vec2				m_vVelocity;		// 카메라 속도
	float				m_fFriction;		// 마찰력
	float				m_fVelocityLimit;	// 속도제한
	

public:
	void tick();
	void render(HDC _dc);

public:
	void SetLook(Vec2 _vLook) { m_vLook = _vLook; }
	Vec2 GetLook() { return m_vLook; }
	Vec2 GetDiff() { return m_vDiff; }

	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);
	void Shake(float _fTerm);
	
	void SetTarget(CActor* _pTarget) { m_pTarget = _pTarget; }
	CActor* GetTarget() { return m_pTarget; }

	void SetSafyArea(CMap* _pCurMap, Vec2 vResolution);


public:
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

private:
	void CameraEffect();
};

