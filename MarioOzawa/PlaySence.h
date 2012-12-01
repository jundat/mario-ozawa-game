#pragma once

#include "gamesence.h"
#include "Mario.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"


class PlaySence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Mario*	_mario;

	//check if is extiing
	bool _isExitting;

	PlaySence(Game* game, int timeAni);
	~PlaySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
};

