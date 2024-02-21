#pragma once

// State �������̽�

class CPlayer;

class CPlayerStandLeft;
class CPlayerStandRight;
class CPlayerWalkLeft;
class CPlayerWalkRight;
class CPlayerProneLeft;
class CPlayerProneRight;
class CPlayerJumpLeft;
class CPlayerJumpRight;
class CPlayerRope;
class CPlayerLadder;
class CPlayerAlertLeft;
class CPlayerAlertRight;

class CPlayerSkillStroke;
class CPlayerSkillStroke2;
class CPlayerSkillShotgun1;
class CPlayerSkillShotgun2;
class CPlayerSkillShotgun3;
class CPlayerSkillBrick1;
class CPlayerSkillBrick2;
class CPlayerSkillBrick3;
class CPlayerSkillBrick4;

class CPlayerState
{
public:
    static CPlayerStandLeft standleft;
    static CPlayerStandRight standright;
    static CPlayerWalkLeft  walkleft;
    static CPlayerWalkRight walkright;
    static CPlayerProneLeft proneleft;
    static CPlayerProneRight proneright;
    static CPlayerJumpLeft jumpleft;
    static CPlayerJumpRight jumpright;
    static CPlayerRope rope;
    static CPlayerLadder ladder;
    static CPlayerAlertLeft alertleft;
    static CPlayerAlertRight alertright;
    static CPlayerSkillStroke Storke;
    static CPlayerSkillStroke2 Stroke2;
    static CPlayerSkillShotgun1 shotgun1;
    static CPlayerSkillShotgun2 shotgun2;
    static CPlayerSkillShotgun3 shotgun3;
    static CPlayerSkillBrick1 brick1;
    static CPlayerSkillBrick2 brick2;
    static CPlayerSkillBrick3 brick3;
    static CPlayerSkillBrick4 brick4;


public:
    virtual void KeyInput(CPlayer* player) {}
    virtual void Update(CPlayer* player) {}   // �ش� ������ �ʿ� ������Ʈ

public:
    virtual void Enter(CPlayer* player) {}  // ���·� ó�� ��ȯ�� ��
    virtual void Exit(CPlayer* player) {}   // ���¿��� ���� ��

public:
    CPlayerState() {}
    virtual ~CPlayerState() {}
};

