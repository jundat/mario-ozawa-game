
#include "BrickQuestion.h"
#include "ResourceManager.h"

brickQuestion::brickQuestion(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Question.png"), 500);
	_coin = new Sprite(ResourceMng::GetInst()->GetTexture("image/Coin.png"), 1);
	_ID = EObject::BRICK;
	_curSprite->SelectIndex(1);
	_curSprite->_start = 1;
	_curSprite->_end = 2;
	_State = hasCoin;
	_drawCoin = false;
	_xCoint = x ;
	_yCoint = y - 40;
}


brickQuestion::~brickQuestion(void)
{
	delete _curSprite;
}

void brickQuestion::Update(int time)
{
	if(_State == noCoin)
	{
		if(_drawCoin == false)
		{
			_coin->Update(time);
			_yCoint-= 0.45 * time;
			if(_yCoint <= (_y - 100))
				_drawCoin = true;
		}
		return;
	}
	_curSprite->Update(time);
}

void brickQuestion::Render()
{
	_curSprite->Render((int)_x, (int)_y);
	if(_State == noCoin)
	{
		if(_drawCoin == false)
		{
			_coin->Render((int)_xCoint, (int)_yCoint);
		}
	}
}

void brickQuestion::CheckCollision(MyObject* obj)
{
	if(_State == noCoin)
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == beforedead) || (obj->_State == dead))
			return;
		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Bottom:
			if(_State == hasCoin)
			{
				_State = noCoin;
				_curSprite->SelectIndex(0);
				// tien tang
			}
			break;
		}
	}
}

/*
CRECT brickQuestion::GetRect()
{
	return CRECT(_x + 5, _y, _x + _curSprite->_texture->Width - 10, _y + _curSprite->_texture->Height);
}*/