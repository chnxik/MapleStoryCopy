#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
    Vec2    m_vForce;           // 힘
    Vec2    m_vVelocity;        // 속도 ( vector )
    float   m_fMass;            // 질량

    float   m_fFriction;        // 마찰력
    float   m_fFrictionScale;   // 마찰계수

    float   m_fVelocityLimit;   // 제한 속도
    float   m_fGravityVLimit;   // 중력에 의한 제한 속도


    float   m_fGravityAccel;    // 중력 가속도 설정
    bool    m_bGround;          // 땅 체크

    Vec2    m_vGrndDir;         // 그라운드에서 라인이동방향

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }                                // Force에 원하는 만큼의 힘을 더한다
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }                // 속도 제한 설정
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }         // 중력에 의한 속도 제한 설정

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }                     // 속도 직접 설정
    Vec2 GetVelocity() { return m_vVelocity; }                                          // 현재 설정 반환
    
    void SetCurGrndDir(Vec2 _vDir) { m_vGrndDir = _vDir; }                              // 현재 접촉한 땅의 기울기 설정

    void AddVelocity(Vec2 _vAddV) { m_vVelocity += _vAddV; }                            // 속도 직접 가산

    void SetFriction(float _f) { m_fFriction = _f; }                                    // 마찰력 설정
    void SetFrictionScale(float _f) { m_fFrictionScale = _f; }                          // 마찰 계수 설정
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }                  // 중력 가속도값 설정
    void SetGrnd(bool _bGround);                                                      // 땅 체크
    bool IsGrnd() { return m_bGround; }


public:
    CLONE(CRigidbody);

public:
    CRigidbody(CActor* _pOwner);
    CRigidbody(const CRigidbody& _other);
    virtual ~CRigidbody();
};
