
#include "Coin.h"
#include "ResourceManager.h"

coin::coin(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Coin.png"), 100);
	_ID = EObject::COIN;
}

coin::~coin(void)
{
	delete _curSprite;
}

void coin::Update(int time)
{
	if(_State == dead)
		return;
	_curSprite->Update(time);
}

void coin::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x, (int)_y);
}

void coin::CheckCollision(MyObject* obj)
{
	if(_State == dead)
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if(this->GetCollisionDirection(obj->GetRect(), this->GetRect()) != None)
		{
			_State = dead;
			// tien tang
		}
	}
}

CRECT coin::GetRect()
{
	return CRECT(_x + 12, _y, _x + _curSprite->_texture->Width - 24, _y + _curSprite->_texture->Height);
}