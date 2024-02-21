#pragma once

class CLevelChange;
class CLevelStateIn;
class CLevelStateOut;
class CLevelStateIdle;

class CLevelState
{
public:
	static CLevelStateIdle Idle;
	static CLevelStateIn In;
	static CLevelStateOut Out;
	static CLevelChange Change;

public:
	virtual void tick() {}
	
	virtual void Enter() {}
	virtual void Exit() {}

	CLONE_DEACTIVATE(CLevelState);

public:
	CLevelState() {}
	virtual ~CLevelState() {}
};

