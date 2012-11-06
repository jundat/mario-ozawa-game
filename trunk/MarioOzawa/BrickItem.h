#ifndef _BRICKITEM_H_
#define _BRICKITEM_H_


#include "Sprite.h"
#include "MyObject.h"
//#include "Mario.h"
#define GRAVITY		0.01


#pragma once

//perform brick have item hide on
// + can not break
// + collision
// + have item in it
class brickItem : public MyObject
{
protected:
	Sprite* _curSprite;
	Sprite* _itemSprite;
	float _xItem,
		_yItem;
	// 0 : hoa, 1 : nam do, 2 : nam xanh
	float _vxItem;
	float _vyItem;
	int _item;

public:
	//kindOfItem = 0:hoa | 1:nam do | 2:namxanh 
	brickItem(float x, float y,int kindOfItem);
	virtual ~brickItem(void);
	virtual void Update(int time);
	virtual void Render();
	virtual void CheckCollision(MyObject* obj);
	CRECT GetItemRect();
	CRECT GetResizeItemRect();

	//tan long
	virtual void CheckTitleCollision(float &vx, float &vy, float &posX, float &posY, float nextX, float nextY, int width, int height);
};

#endif

