#pragma once
#include "CLevelState.h"
class CLevelStateIn :
    public CLevelState
{
private:
    float _facc = 0.f;

public:
    virtual void tick();   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter();  // ���·� ó�� ��ȯ�� ��
    virtual void Exit();   // ���¿��� ���� ��
};

