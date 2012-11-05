#ifndef _BULLET_H_
#define _BULLET_H_

#define GRAVITY		0.01

#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"



#pragma once
class bullet : public MyObject
{
protected:
	Sprite* _curSprite;
	//float _vx,_vy;
public:
	bullet(float x, float y,bool turnLeft);
	virtual ~bullet(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void CheckCollision(MyObject* obj);
};

#endif