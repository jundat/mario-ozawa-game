#pragma once

#include "gamesence.h"
#define ALL_TIME_INTRO 100

class IntroSence :
	public GameSence
{
public:
	DWORD _startTime;
	bool _stopUpdate;

	IntroSence(Game* game, int timeAni);
	~IntroSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

