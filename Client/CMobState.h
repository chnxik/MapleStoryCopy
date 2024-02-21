#pragma once

// State 인터페이스

class CMob;

class CMobIdleLeft;
class CMobIdleRight;
class CMobDead;
class CMobAlert;
class CMobDamaged;
class CMobSpawn;
class CMobWalkRight;
class CMobWalkLeft;

class CMobState
{
public:
	static CMobIdleLeft idleleft;
	static CMobIdleRight idleright;
	static CMobDead dead;
	static CMobAlert alert;
	static CMobDamaged damaged;
	static CMobSpawn spawn;
	static CMobWalkRight walkright;
	static CMobWalkLeft walkleft;

public:
	virtual void Update(CMob* _pMob) {}

public:
	virtual void Enter(CMob* _pMob) {}
	virtual void Exit(CMob* _pMob) {}

public:
	CMobState() {}
	virtual ~CMobState() {}
};

