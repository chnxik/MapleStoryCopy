#pragma once
#include "CLevelState.h"
class CLevelChange :
    public CLevelState
{
public:
    virtual void tick();   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter();  // ���·� ó�� ��ȯ�� ��
    virtual void Exit();   // ���¿��� ���� ��

public:
    void ChangeLevel();
};

