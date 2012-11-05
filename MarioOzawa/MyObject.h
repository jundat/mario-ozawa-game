#pragma once

#include "Rect.h"

// tieu nun
enum State{
	stand,
	Move,
	alive,
	jumping,
	beforedead,
	beforedead2,
	dead,
	transform,
	attack,
	hasCoin,
	noCoin,
	hasItem,
	breaking
};

// tieu nun
enum EObject
{
	MARIO, // = 0
	BRICK,
	FUNGI,
	TURTLE,
	COIN,
	PIPE
};

enum EDirect
{
	Left,
	Right,
	Top,
	Bottom,
	None
};

class MyObject
{
public:
	State _State;
	
	// tieu nun
	float _x;
	float _y;
	
	float _vx;
	float _vy;
	
	EObject _ID;
	
	//0: Left | 1: Right
	bool _turnLeft;
	//end tieu nun

	MyObject(float x, float y);
	//MyObject(const MyObject* obj);
	virtual ~MyObject(void);

	virtual CRECT GetRect();

	//obj can check collision with other or not
	virtual bool CanCollide();

	virtual bool IsAlive();

	virtual void Update(int time);

	virtual void Render();

	virtual void CheckCollision(MyObject* obj);

	// tieu nun
	virtual void CheckTitleCollision(float &_vx,float &_vy,float _nextX,float _nextY,float _maxWidth,float _maxHeight,int _width,int _height);

	EDirect GetCollisionDirection(CRECT r1, CRECT r2);
};

