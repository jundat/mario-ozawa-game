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

	int _TimeTransform;
	int _time;

	vector <bullet*> _listBullet;

public:
	int gold;
	int life; //số mạng sống còn lại của mario

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

	void Reset(); //reset position mario to replay level
	void Fire();
	void TransformMario(int x,int y);
	void Transform();
	//override
	virtual void CheckCollision(MyObject* obj);
};

#endif
