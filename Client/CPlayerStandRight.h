#pragma once
#include "CPlayerState.h"

class CPlayerStandRight :
    public CPlayerState
{
public:
    virtual void KeyInput(CPlayer* player);
    virtual void Update(CPlayer* player);   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter(CPlayer* player);  // ���·� ó�� ��ȯ�� ��
    virtual void Exit(CPlayer* player);   // ���¿��� ���� ��
};