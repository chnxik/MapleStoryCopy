#pragma once
#include "CPlayerState.h"

class CPlayerWalkRight :
    public CPlayerState
{
private:
    float _acctime = 0;

public:
    virtual void KeyInput(CPlayer* player); // Ű�Է�
    virtual void Update(CPlayer* player);   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter(CPlayer* player);  // ���·� ó�� ��ȯ�� ��
    virtual void Exit(CPlayer* player);   // ���¿��� ���� ��
};