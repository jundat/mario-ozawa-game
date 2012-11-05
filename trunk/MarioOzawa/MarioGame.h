#ifndef _MARIO_GAME_H_
#define _MARIO_GAME_H_

#include <d3dx9.h>

#include "Global.h"
#include "Game.h"
#include "Sprite.h"
#include "Mario.h"

class MarioGame: public Game
{
public:
	MarioGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate);
	~MarioGame();

	
protected:

	virtual void RenderFrame(int Delta);
	virtual void ProcessInput(int Delta);
	virtual void LoadResources();

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};


#endif