
#include "SoundManager.h"
#include "BrickItem.h"
#include "ResourceManager.h"
#include "TileMap.h"

brickItem::brickItem(float x, float y,EBrickItemKind kindOfItem) : MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Question.png"), 500);
	_ID = EObject::BRICKITEM;
	_curSprite->SelectIndex(1);
	_curSprite->_start = 1;
	_curSprite->_end = 2;
	_State = hasItem;
	_item = kindOfItem;
	_xItem = x;
	_yItem = y;
	_vxItem = 0.2;
	_vyItem = 0.2;

	if(_item == EBrickItemKind::FLOWER)
		_itemSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Flower.png"), 400);

	if(_item == EBrickItemKind::LARGER)
	{
		_itemSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Lager.png"), 0);
		//_itemSprite->_start = 0;
		//_itemSprite->_end = 0;
		_itemSprite->SelectIndex(0);
		_turnLeft = false;
	}

	if(_item == EBrickItemKind::SHOOTER)
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
	_curSprite = NULL;
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
		if(_item == EBrickItemKind::FLOWER)
			_itemSprite->Update(time);
	}

	if(_State == Move)
	{
		if((_item == EBrickItemKind::LARGER) || (_item == EBrickItemKind::SHOOTER))
		{

			/*_xItem += _vxItem * time;
			_yItem += _vyItem * time;
			if(_turnLeft == true)
				_vxItem = - 0.2;
			else _vxItem = 0.2;
			_vyItem += GRAVITY * time;
			*/
			//float _nextxItem = _xItem + _vxItem * time;
			
		/*float _nextxItem = _xItem;

		float _nextyItem = _xItem + _vyItem * time;
		if(_turnLeft == true)
			_vxItem = - 0.2;
		else _vxItem = 0.2;
		_vyItem += GRAVITY * time;*/
		
		float _nextxItem = _xItem +_vxItem * time ;
		float _nextyItem = _yItem + _vyItem * time;
		
		if(_turnLeft == true)
			_vxItem = - 0.2;
		else _vxItem = 0.2;
		_vyItem += GRAVITY * time;

		
		if(_State == Move)
		{
			switch(this->GetCollisionDirection(this->GetItemRect(),this->GetRect()))
			{
				case Top:
					_nextyItem = _y + TILE + 1;
				break;
				case Bottom:
					_nextyItem = _y - _itemSprite->_texture->Height;
					break;
				case Left:
					_nextxItem = _x + TILE ;
					_turnLeft = false;
					break;
				case Right:
					_nextxItem = _x - this->_itemSprite->_texture->Width ;
					_turnLeft = true;
					break;
			}
		}
		//_vxItem = _nextxItem;
		//_vyItem = _nextyItem;
		CheckTitleCollision(_vxItem,_vyItem,_nextxItem,_nextyItem,GL_Width,GL_Height,_curSprite->_texture->Width,_curSprite->_texture->Height);
		
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

		// cho nay la doi. gach ra item
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
					if((GL_CurForm == 0) && (GL_NextForm == 1))
						obj->_y -= 50;
				}// player transform or + heart khi nhat dc item here
			}
		}
	}
	if((obj->_ID == EObject::BRICK) || (obj->_ID == EObject::BRICKITEM))
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

void brickItem::CheckTitleCollision(
	float &_vxItem, float &_vyItem, 
	float _nextX, float _nextY, 
	float _maxWidth, float _maxHeight, 
	int _width,int _height)
{
	if((_State == beforedead2) || (_State == beforedead) || (_State == dead))
	{
		_xItem = _nextX;
		_yItem = _nextY;
		return;
	}

	if (_vxItem > 0)
	{
		bool iColTerX1 = false;
		for (int i = (_xItem + _width)/TILE ; i <  (_nextX + _width)/TILE; i++)
		{
			for (int j = _yItem/TILE;j < (int)((_yItem+_height-1)/TILE) +1;j++ )
			{
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					iColTerX1 = true;
					_xItem = TILE * (i) - _width;
					_turnLeft = true;
					break;
				}
			}
			if (iColTerX1 == true)
			{
				break;
			}
		}

		if (iColTerX1 == false){
			_xItem = _nextX;
		}

	}
	else
	{
		if (_vxItem <= 0){

			if (_nextX <= 0)
			{
				_nextX = 0;
			}
			bool iColTerX2 = false;
			for (int i = _xItem/TILE-1; i >  _nextX/TILE-1;i--) // 
			{
				for (int j = _yItem/TILE ;j < int((_yItem+_height-1)/TILE) +1 ; j++ )
				{
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						iColTerX2 = true;
						_xItem = TILE * (i+1);
						_turnLeft = false;
						break;
					}
				} 
				if (iColTerX2 == true)
				{
					break;
				}
			}

			if (iColTerX2 == false)
			{
				_xItem = _nextX;
			}
		}	
	}

	if (_vyItem >= 0){
		// DOWN
		bool iColTer = false;
		for (int j = (_yItem + _height)/TILE; j <  (_nextY+_height)/TILE ;j++){
			for (int i = _xItem/TILE;i < (_xItem+_width)/TILE;i++ ){
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					//if(checkY == false)
					{
						iColTer = true;
						_yItem = TILE * (j) - _height;
						_vyItem = 0;
						break;
					}
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			_yItem = _nextY;
		}

	}else{
		// UP
		int n = (_nextY/TILE);
		int m = (_yItem/TILE);
		if (n!=m ){

			bool iColTerY = false;
			for (int j = _yItem/TILE-1; j >  _nextY/TILE-1;j--){
				for (int i = _xItem/TILE;i < (_xItem+_width)/TILE;i++ ){
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						//if(checkY == true)
						{
							iColTerY = true;
							_yItem = TILE * (j+1);
							_vyItem = 0;//fabs(_vyItem);
							break;
						}
					}
				}
				if (iColTerY == true){
					break;
				}
			}

			if (iColTerY == false){
				_yItem = _nextY;
			}

		}else{
			_yItem = _nextY;
		}

	}
}