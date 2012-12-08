#pragma once

#include "gamesence.h"

class LoseGameSence :
	public GameSence
{
public:
	LoseGameSence(Game* game, int timeAni);
	~LoseGameSence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

