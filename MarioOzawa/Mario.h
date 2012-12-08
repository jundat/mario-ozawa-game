﻿#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"
#include "Bullet.h"
//#include "Brick.h"
#include <vector>
#define MARIO_VX	0.0001f
#define MARIO_VY	2.2f
#define MAX_MARIO_VX 8.0f
#define MAX_MARIO_VY 2.0f
#define GRAVITY		0.01f
#define FRICTION_X		0.00001f
#define ACCEL_X		1.5f
#define BOTTOM		600
#define DISTANCE_WITH_LAST_POSITION_X 400 //distance between the current position and last position to update last position
#define FALL_DEAD_HIGH 4	//the high mario fall out of game before reborn
#define DELTA_RECT_X 0 //delta to sub in x when call getRect
#define DELTA_RECT_Y 0 //delta to sub in y when call getRect

#define EXP_FOR_BRICK 5 //point for exp
#define EXP_FOR_OBJECT 10
#define TIME_REBORN 1000

using namespace std;
#pragma once
class Mario : public MyObject
{
protected:
	
	int _TimeTransform;
	int _time;

	int _startx; //the start position when mario init
	int _starty;

	vector <bullet*> _listBullet;

public:
	Sprite* _sprMarioSmaller;
	Sprite* _sprMarioLarger;
	Sprite* _sprMarioFire;
	Sprite* _curSprite;

	int gold;
	int life; //số mạng sống còn lại của mario
	int exp;

	Mario(float x, float y);
	virtual ~Mario(void);

	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stand();

	//tan long
	void ShitDown();
	
	//call when you want mario die
	void RunBeforeDie();

	//fire bullets
	void Fire();

	//check transform transform
	void TransformMario(int x,int y);

	//effect transform mario from: small->big->fire
	void Transform();

	//override
	virtual void CheckCollision(MyObject* obj);
};

#endif
