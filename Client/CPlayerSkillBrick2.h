#pragma once
#include "CPlayerState.h"
class CPlayerSkillBrick2 :
    public CPlayerState
{
private:
    float _facc = 0.f;
    float _fDelay = 0.f;

public:
    virtual void KeyInput(CPlayer* player); // Ű�Է�
    virtual void Update(CPlayer* player);   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter(CPlayer* player);  // ���·� ó�� ��ȯ�� ��
    virtual void Exit(CPlayer* player);   // ���¿��� ���� ��
};