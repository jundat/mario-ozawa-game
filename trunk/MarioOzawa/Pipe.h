#ifndef _PIPE_H_
#define _PIPE_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"

#pragma once
class pipe : public MyObject
{
protected:
	Sprite* _curSprite;
public:
	pipe(float x, float y);
	virtual ~pipe(void);
	virtual void Update(int time);
	virtual void Render();
	virtual CRECT GetRect();
};

#endif

