
#include "TileMap.h"
#include "SoundManager.h"
#include "BrickItem.h"
#include "ResourceManager.h"

brickItem::brickItem(float x, float y,int kindOfItem) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Question.png"), 500);
	_ID = EObject::BRICK;
	_curSprite->SelectIndex(1);
	_curSprite->_start = 1;
	_curSprite->_end = 2;
	_State = hasItem;
	_item = kindOfItem;
	_xItem = x;
	_yItem = y;
	_vxItem = 0;
	_vyItem = 0;
	if(_item == 0)
		_itemSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Flower.png"), 400);
	if(_item == 1)
	{
		_itemSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Lager.png"), 0);
		//_itemSprite->_start = 0;
		//_itemSprite->_end = 0;
		_itemSprite->SelectIndex(0);
		_turnLeft = false;
	}

	if(_item == 2)
	{
		_itemSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Lager.png"), 0);
		//_itemSprite->_start = 1;
		//_itemSprite->_end = 1;
		_itemSprite->SelectIndex(1);
		_turnLeft = false;
	}
}


brickItem::~brickItem(void)
{
	delete _curSprite;
}

void brickItem::Update(int time)
{
	if(_State == stand)
		return;

	if(_State == hasItem)
		_curSprite->Update(time);

	if(_State == transform)
	{
		//if(_item == 0)
		{
			_yItem -= 3;
			if(_yItem <= (_y - 50))
			{
				_yItem = _y - 50;
				_State = Move;
			}
		}
	}
	
	if((_State == Move) || (_State == transform))
	{
		if(_item == 0)
			_itemSprite->Update(time);
	}

	if(_State == Move)
	{
		if((_item == 1) || (_item == 2))
		{
			// tan long xoá
			//_xItem += _vxItem * time;
			//_yItem += _vyItem * time;
			
			//tan long
			float _NextX;
			float _NextY;
			{
				_NextX = _xItem + _vxItem * time;
				_NextY = _yItem + _vyItem * time;
			}
			
			if(_turnLeft == true)
				_vxItem = - 0.2;
			else 
				_vxItem = 0.2;
			_vyItem += GRAVITY * time;

			//tan long
			CheckTitleCollision(_vxItem, _vyItem, _xItem, _yItem, _NextX, _NextY, _itemSprite->_texture->Width, _itemSprite->_texture->Height);
		}
	}
}

void brickItem::Render()
{
	
	if((_State == Move) || (_State == transform))
	{
		//if(_item == 0)
			_itemSprite->Render((int)_xItem , (int)_yItem);
	}
	_curSprite->Render((int)_x, (int)_y);
}

void brickItem::CheckCollision(MyObject* obj)
{
	if(_State == stand)
		return;
	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == beforedead) || (obj->_State == dead))
			return;
		if(_State == hasItem)
		{
			switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
			{
				case Bottom:
					{
						_State = transform;
						_curSprite->SelectIndex(0);

						//sound
						SoundManager::GetInst()->PlayEffSound(SOUND_E_UP);
					}
					break;
			}
		}

		//check collision with item
		if(_State == Move)
		{
			if(this->GetCollisionDirection(this->GetResizeItemRect(), obj->GetRect()) != None)
			{
				_State = stand;
				if(GL_CurForm != 2)
				{
					obj->_State = transform;
					GL_NextForm = GL_CurForm + 1;
				}// player transform or + heart khi nhat dc item here
			}
		}
	}
	if(obj->_ID == EObject::BRICK)
	{
		//if(_State != Move)
		//	return;
		//if(obj->_State == dead)
		//	return;
		switch(this->GetCollisionDirection(this->GetItemRect(), obj->GetRect()))
		{
		case Top:
			{
				_vyItem = 0;
				_yItem = obj->_y + TILE + 1;
			}
			break;
		case Bottom:
			{
				_vyItem = 0;
				_yItem = obj->_y - _itemSprite->_texture->Height;
			}
			break;
		case Left:
			{
				_xItem = obj->_x + TILE ;
				_turnLeft = false;
			}
			break;
		case Right:
			{
				_xItem = obj->_x - this->_itemSprite->_texture->Width ;
				_turnLeft = true;
			}
			break;
		}
	}

	if(obj->_ID == EObject::PIPE)
	{
		if(_State != Move)
			return;
		if(obj->_State == dead)
			return;
		switch(this->GetCollisionDirection(this->GetItemRect(), obj->GetRect()))
		{
		case Top:
			{
				_vyItem = 0;
				_yItem = obj->_y + 100 + 1;
			}
			break;
		case Bottom:
			{
				_vyItem = 0;
				_yItem = obj->_y - _itemSprite->_texture->Height;
			}
			break;
		case Left:
			{
				_xItem = obj->_x + 100 ;
				_turnLeft = false;
			}
			break;
		case Right:
			{
				_xItem = obj->_x - this->_itemSprite->_texture->Width ;
				_turnLeft = true;
			}
			break;
		}
	}
}


CRECT brickItem::GetResizeItemRect()
{
	return CRECT(_xItem + 10, _yItem, _xItem + _itemSprite->_texture->Width - 20, _yItem + _itemSprite->_texture->Height);
}

CRECT brickItem::GetItemRect()
{
	return CRECT(_xItem , _yItem, _xItem + _itemSprite->_texture->Width , _yItem + _itemSprite->_texture->Height);
}

//tan long
void brickItem::CheckTitleCollision(float &vx, float &vy, float &posX, float &posY, float nextX, float nextY, int width, int height)
{
	bool isOK = true;	
	for (int i = posX/TILE ; i <  (nextX + width - 1)/TILE; i++)
	{
		for (int j = posY/TILE; j < (nextY + height - 1)/TILE; j++ )
		{
			if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
			{
				isOK = false;
			}
		}
	}

	if(isOK)
	{
		posX = nextX;
		posY = nextY;
	}

}