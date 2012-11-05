#ifndef _BRICK_H_
#define _BRICK_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"

#pragma once

//class perform normal brick
// + can not break
// + just check collision + draw
class brick : public MyObject
{
protected:
	Sprite* _curSprite;
public:
	brick(float x, float y);
	virtual ~brick(void);
	virtual void Update(int time);
	virtual void Render();
};

#endif

