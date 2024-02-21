#pragma once
#include "CComponent.h"

class CRigidbody :
    public CComponent
{
private:
    Vec2    m_vForce;           // ��
    Vec2    m_vVelocity;        // �ӵ� ( vector )
    float   m_fMass;            // ����

    float   m_fFriction;        // ������
    float   m_fFrictionScale;   // �������

    float   m_fVelocityLimit;   // ���� �ӵ�
    float   m_fGravityVLimit;   // �߷¿� ���� ���� �ӵ�


    float   m_fGravityAccel;    // �߷� ���ӵ� ����
    bool    m_bGround;          // �� üũ

    Vec2    m_vGrndDir;         // �׶��忡�� �����̵�����

public:
    virtual void tick() override;
    virtual void final_tick() override;
    virtual void render(HDC _dc) override;

public:
    void AddForce(Vec2 _vForce) { m_vForce += _vForce; }                                // Force�� ���ϴ� ��ŭ�� ���� ���Ѵ�
    void SetVelocityLimit(float _fLimit) { m_fVelocityLimit = _fLimit; }                // �ӵ� ���� ����
    void SetGravityVelocityLimit(float _fLimit) { m_fGravityVLimit = _fLimit; }         // �߷¿� ���� �ӵ� ���� ����

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }                     // �ӵ� ���� ����
    Vec2 GetVelocity() { return m_vVelocity; }                                          // ���� ���� ��ȯ
    
    void SetCurGrndDir(Vec2 _vDir) { m_vGrndDir = _vDir; }                              // ���� ������ ���� ���� ����

    void AddVelocity(Vec2 _vAddV) { m_vVelocity += _vAddV; }                            // �ӵ� ���� ����

    void SetFriction(float _f) { m_fFriction = _f; }                                    // ������ ����
    void SetFrictionScale(float _f) { m_fFrictionScale = _f; }                          // ���� ��� ����
    void SetGravityAccel(float _fAccel) { m_fGravityAccel = _fAccel; }                  // �߷� ���ӵ��� ����
    void SetGrnd(bool _bGround);                                                      // �� üũ
    bool IsGrnd() { return m_bGround; }


public:
    CLONE(CRigidbody);

public:
    CRigidbody(CActor* _pOwner);
    CRigidbody(const CRigidbody& _other);
    virtual ~CRigidbody();
};
