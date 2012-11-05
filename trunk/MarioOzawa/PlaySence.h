#pragma once

#include "gamesence.h"
#include "Mario.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"

// tieu nun
#include "Brick.h"
#include "BrickBreak.h"
#include "BrickItem.h"
#include "Coin.h"
#include "Fungi.h"
#include "Turtle.h"
#include "Pipe.h"

class PlaySence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	MapLoader*	_MapLoader;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Mario*	_mario;

	PlaySence(Game* game, int timeAni);
	~PlaySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

