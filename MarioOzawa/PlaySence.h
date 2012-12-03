#pragma once

#include "gamesence.h"
#include "Mario.h"
#include "QuadTree.h"
#include "Camera.h"
#include "MapLoader.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "ChangeMapSence.h"

#define MARIO_VX_COMPLETE_MAP 7.0f
#define MARIO_DELTA_X_COMPLETE_MAP 400

#define TIME_FOR_LEVEL (150000) //5 minute to complete level (5 * 60 * 500), ~500ms = 1s, không hiểu vì sao thời gian trong game này chậm = 1/2 bình thường


class PlaySence :
	public GameSence
{
public:
	QuadTree*	_QuadTree;
	Camera*		_Camera;
	BackgroundManager*	_BackgroundMng;

	// tieu nun
	Mario*	_mario;
	bool IsVisiable;

	//check if is extiing
	bool _isExitting;
	int _timeForLevel; //time for 1 level, count down from TIME_FOR_LEVEL to zero
	
	PlaySence(Game* game, int timeAni);
	~PlaySence(void);

	virtual void _UpdateRender(int t);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();

	void LoadNewMap(void);
};

