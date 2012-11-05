#ifndef _MARIO_H_
#define _MARIO_H_


#include "Sprite.h"
#include "MyObject.h"
#include "Bullet.h"
//#include "Brick.h"
#include <vector>
#define MARIO_VX	0.0002
#define MARIO_VY	2.2
#define GRAVITY		0.01
#define FRICTION_X		0.00001f
#define ACCEL_X		1.5
#define BOTTOM		600
using namespace std;
#pragma once
class Mario : public MyObject
{
protected:
	Sprite* _sprMarioSmaller;
	Sprite* _sprMarioLarger;
	Sprite* _sprMarioFire;

	Sprite* _curSprite;

	//0: Left | 1: Right
	//bool _turnLeft;
	//bool _isJumping;

	//float _vx;
	//float _vy;
	int _TimeTransform;
	int _time;
	vector <bullet*> _listBullet;
public:
	Mario(float x, float y);
	virtual ~Mario(void);

	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Stand();

	void Fire();
	void TransformMario(int x,int y);
	void Transform();
	//override
	virtual void CheckCollision(MyObject* obj);
};

#endif
