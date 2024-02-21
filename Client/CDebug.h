#pragma once
class CDebug
{
	SINGLE(CDebug)
private:
	bool _bDebug;
	bool _bDebugText;
	RECT _textRT;

public:
	void init();
	void tick();
	void render(HDC _dc);

public:
	bool IsDebugOn() { return _bDebug; }
	bool IsDebugTextOn() { return _bDebugText; }
};

