#ifndef _BRICKBREAK_H_
#define _BRICKBREAK_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"


#pragma once

//perform brick can be break by mario
// + checkcollision
// + 
class brickBreak : public MyObject
{
protected:
	Sprite* _curSprite;
	int _xBreak1,_xBreak2,_xBreak3,_xBreak4;
	int _yBreak1,_yBreak2,_yBreak3,_yBreak4;
	RECT _rectBreak1,_rectBreak2,_rectBreak3,_rectBreak4;

public:
	brickBreak(float x, float y);
	virtual ~brickBreak(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
	void CheckCollision(MyObject* obj);
};

#endif

