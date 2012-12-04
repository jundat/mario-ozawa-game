#include "Bullet.h"
#include "ResourceManager.h"
#include "TileMap.h"
bullet::bullet(float x, float y,bool turnLeft) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Bullet.png"), 100);
	_curSprite->_start = 0;
	_curSprite->_end = 3;
	_vx = 0;
	_vy = 0;
	_turnLeft = turnLeft;
	_State = Move;
}


bullet::~bullet(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void bullet::Update(int time)
{
	if(_State == dead)
		return;

	if(_State == Move)
	{
		
		float _NextX;
		float _NextY; 
		_NextX = _x + _vx * time;
		_NextY = _y + _vy * time;

		CheckTitleCollision(_vx,_vy,_NextX,_NextY,800,600,_curSprite->_texture->Width,_curSprite->_texture->Height - 10);
		if(_turnLeft == true)
			_vx = -0.8;
		else _vx = 0.8;
		_vy = this->_vy + 0.055 ;
	}
	_curSprite->Update(time);
}

void bullet::Render()
{
	if(_State == dead)
		return;
	_curSprite->Render((int)_x, (int)_y);
	if(_curSprite->_index == 9)
		_State = dead;
}

void bullet::CheckCollision(MyObject* obj)
{
	if((_State == dead) || (_State == beforedead))
		return;
	
	/*if(obj->_ID == EObject::BRICK)
	{
		if(obj->_State == dead)
			return;
		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Bottom:
			_y = obj->_y - (_curSprite->_texture->Height - 10 );
			_vy = -0.5;
			break;
		}
	}*/

	if(obj->_ID == EObject::PIPE)
	{
		if(obj->_State == dead)
			return;

		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != None)
		{
			_State = beforedead;
			_curSprite->_start = 7;
			_curSprite->_end = 9;
			_curSprite->_timeAni = 15;
		}
	}

	if((obj->_ID == EObject::FUNGI) || (obj->_ID == EObject::TURTLE))
	{
		if((obj->_State == dead) || (obj->_State == beforedead) || (obj->_State == beforedead2)) 
			return;
		if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) != None)
		{
			obj->_State = beforedead2;
			if(this->GetCollisionDirection(this->GetRect(), obj->GetRect()) == Left)
				obj->_vx = 0.2;
			else obj->_vx = -0.2;
			obj->_vy = -1.1;
			_State = beforedead;
			_curSprite->_start = 7;
			_curSprite->_end = 9;
			_curSprite->_timeAni = 15;
		}
	}
}

CRECT bullet::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height - 10);
}

void bullet::CheckTitleCollision(float &_vx,float &_vy,float _nextX,float _nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if (_vy >= 0)
	{
		// DOWN
		bool iColTer = false;
		for (int j = (_y + _height)/TILE; j <  (_nextY+_height)/TILE ;j++){
			for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					{
						iColTer = true;
			 			this->_vy = -0.6f;
						_y = TILE * (j) - (_curSprite->_texture->Height - 10 );
						break;
					}
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			_y = _nextY;
		}
	}
	_y = _nextY;
	_x = _nextX;
}