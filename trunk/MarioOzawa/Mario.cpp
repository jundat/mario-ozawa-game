// tieu nun, fix all

#include "Mario.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "SoundManager.h"
#include "MapLoader.h"
#include "Writer.h"
#include "Turtle.h"
#include "BrickItem.h"
Mario::Mario(float x, float y)	: MyObject(x, y)
{
	_sprMarioSmaller = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioSmaller.png"), 50);
	_sprMarioLarger = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioLarger.png"), 50);
	_sprMarioFire = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioFire.png"), 50);
	_turnLeft = false;
	_curSprite = _sprMarioSmaller;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	GL_CurForm = 0;
	GL_NextForm = 1;
	_State = stand;
	_lastx = _x = x;
	_lasty = _y = y;
	_vx = 0;
	_vy = 0;
	_TimeTransform = 0;
	_ID = EObject::MARIO;

	life = 3;
	gold = 0;
}

Mario::~Mario(void)
{
	delete _sprMarioSmaller;
	delete _sprMarioLarger;
	delete _sprMarioFire;

	_sprMarioSmaller = NULL;
	_sprMarioLarger = NULL;
	_sprMarioFire = NULL;
}

void Mario::Update(int time)
{
	/*int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Update(time);
	}

	Transform();

	_time = time;
	float _NextX = _x + _vx ;
	float _NextY = _y + _vy * _time;

	_vy += GRAVITY * time;
	CheckTitleCollision(_vx,_vy,_NextX,_NextY, GL_Width, GL_Height, _curSprite->_texture->Width,_curSprite->_texture->Height);

	//beforedead -> dead
	if(_State == beforedead)
	{
		_curSprite->SelectIndex(5);
		
		//check is dead
		if(_y > FALL_DEAD_HIGH * GL_MapH)
		{
			_State = dead;

			//reborn
			if(this->life > 0)
			{
				this->life--;
				this->_State = stand;

				this->_vx = 0;
				this->_vy = 0;

				this->_y = _lasty; //MapLoader::_mariox * TILE;
				this->_x = _lastx; //MapLoader::_mariox * TILE;
			}
		}

		return;
	}
	else //dead when fall out of map
	{
		if(_y > GL_MapH && _State != dead && _State != beforedead && _State != beforedead2)
		{
			_State = beforedead;
			this->_vy = -2.5f;
		}
	}

	if(_vx != 0)
	{
		_curSprite->Update(time);
	}
	if(_State == transform)
		return;

	// do when change dir suddenly
	if((_turnLeft == true) && (_vx > 0.0f))
		_curSprite->SelectIndex(4);
	if((_turnLeft == false) && (_vx < 0.0f))
		_curSprite->SelectIndex(4);

	if(_State == jumping){
		_curSprite->SelectIndex(3);
	}

	/*
	{//do not run out of the map
		//right
		if(_x + this->_curSprite->_texture->Width >= GL_MapW)
		{
			_x = GL_MapW - this->_curSprite->_texture->Width;
		}

		//left
		if(_x <= 0)
		{
			_x = 0;
		}
	}
	*/

	//save last position
// 	if(_State == stand || _State == Move)
// 	{
// 		if(abs(_x - _lastx) >= DISTANCE_WITH_LAST_POSITION_X)
// 		{
// 			_lastx = _x;
// 			_lasty = _y;
// 		}
// 	}
}

void Mario::Render()
{
	if(_turnLeft == false)
		_curSprite->Render((int)_x, (int)_y);
	else 
		_curSprite->RenderScaleX((int)_x, (int)_y);

	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Render();
	}
}

void Mario::TurnRight()
{
	if(_State == beforedead)
		return;
	// if press Right, Update _vx
	_vx += FRICTION_X * _time;
	if(_vx >= MAX_MARIO_VX)
		_vx = MAX_MARIO_VX;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	if((_State != transform) && (_State != Move) && (_State != jumping))
	{
		_State = Move;
	}
	_turnLeft = false;
}

void Mario::TurnLeft()
{
	if(_State == beforedead)
		return;
	// if press Left, Update _vx
	_vx -= FRICTION_X * _time;
	if(_vx <= - MAX_MARIO_VX)
		_vx = - MAX_MARIO_VX;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	if((_State != transform) && (_State != Move) && (_State != jumping))
	{
		_State = Move;
	}
	_turnLeft = true;
}

void Mario::Jump()
{
	if(_State == beforedead)
		return;

	if((_State != jumping)&&(_State != transform)){
		_State = jumping;
		_vy = - MARIO_VY;

		//sound
		SoundManager::GetInst()->PlayEffSound(SOUND_E_JUMP);
	}
}

void Mario::Stand()
{
	if(_State == beforedead)
		return;
	//Not Press , Update _vx to 0.0f
	if(_vx < 0.0f)
		_vx += FRICTION_X/2 * _time;
	else if(_vx > 0.0f) _vx -= FRICTION_X/2 * _time;
	if((_vx <= 0.1f) && (_vx >= - 0.1f))
		_vx = 0.0f;

	//then set Stand frame
	if((_State != jumping) && (_State != transform) && (_vx == 0.0f)){
		_State = stand;
		//_vx = 0;
		_curSprite->SelectIndex(0);
	}
}

//tan long
void Mario::ShitDown()
{
	if(_curSprite == _sprMarioLarger && _State == stand)
	{
		_vx = 0;
		_curSprite->SelectIndex(5);
	}
	else
	{
		//nothing
	}
}


void Mario::Transform()
{
	if(_State == beforedead)
		return;

	if(_State == transform)
	{
		_TimeTransform++;
		if(_TimeTransform % 5 == 0)
		{
			if(GL_NextForm == 0)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioSmaller;
				_curSprite->SelectIndex(_tempIndex);
				//_y += 50;
			}
			if(GL_NextForm == 1)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioLarger;
				_curSprite->SelectIndex(_tempIndex);
				if(GL_CurForm == 0)
				{
					_y -= 50;
					if((_State == transform) && (_turnLeft == false))
					{
						//_x -= 100;
					}
				}
			}
			if(GL_NextForm == 2)
			{
				int _tempIndex = _curSprite->_index;
				_curSprite = _sprMarioFire;
				_curSprite->SelectIndex(_tempIndex);
			}
		}
		else
		{
			if(_TimeTransform % 5 == 2)
			{
				if(GL_CurForm == 0)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite = _sprMarioSmaller;
					_curSprite->SelectIndex(_tempIndex);
					//_y += 50;
					if(GL_NextForm == 1)
					{
						_y +=50;
						if((_State == Move) && (_turnLeft == false))
						{
							//_x += 100;
						}
					}
				}
				if(GL_CurForm == 1)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite =_sprMarioLarger;
					_curSprite->SelectIndex(_tempIndex);
					//_y -= 50;
				}
				if(GL_CurForm == 2)
				{
					int _tempIndex = _curSprite->_index;
					_curSprite = _sprMarioFire;
					_curSprite->SelectIndex(_tempIndex);
				}
			}
		}

		if(_TimeTransform == 30)
		{
			_TimeTransform = 0;
			GL_CurForm = GL_NextForm;
			if(_vy == 0)
				_State = stand;
			else _State = jumping;
		}
	}
}

void Mario::TransformMario(int x, int y)
{
	_State = transform;
	GL_CurForm = x;
	GL_NextForm = y;
	if((GL_CurForm == 0) && (GL_NextForm == 1))
		_y -= 50;

	//SOUND
	SoundManager::GetInst()->PlayEffSound(SOUND_E_GROW);
}

void Mario::CheckCollision(MyObject* obj)
{	
	
	int size = _listBullet.size();
	bullet* sf;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		//sf->CheckCollision(obj);
	}

	if((_State == beforedead) || (_State == dead))
		return;
	/*
	if((obj->_ID == EObject::BRICKITEM) || (obj->_ID == EObject::BRICKQUESTION) || (obj->_ID == EObject::BRICKBREAK) )
	{
		//if(_State == transform)
		//	return;
		if(obj->_State == dead)
			return;

		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Top:
			_vy = 0;
			_y = obj->_y + TILE + 1 ;
			break;

		case Bottom:
			_vy = 0;
			_y = obj->_y - _curSprite->_texture->Height ;
			if(_State != transform)
				_State = stand;
			break;

		case Left:
			//_vx = 0;
			_x = obj->_x + TILE ;
			break;

		case Right:
			//_vx = 0;
			_x = obj->_x - this->_curSprite->_texture->Width ;
			break;
		}
	}
	*/

	/*
	if((obj->_ID == EObject::FUNGI) || (obj->_ID == EObject::TURTLE))
	{
		if(_State == transform)
			return;

		if(obj->_State == dead)
			return;

		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
			case Bottom:
				{
					_vy = -1.5;
					_State = jumping;

				//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);
				}				
				break;
		}
	}*/
}

CRECT Mario::GetRect()
{
	return CRECT(
		_x + DELTA_RECT_X, 
		_y + DELTA_RECT_Y, 
		_x + _curSprite->_texture->Width - 2 * DELTA_RECT_X, 
		_y + _curSprite->_texture->Height - 2 * DELTA_RECT_Y);
}

CRECT Mario::GetRect1()
{
	return CRECT(
		_x + DELTA_RECT_X + 5, 
		_y + DELTA_RECT_Y, 
		_x + _curSprite->_texture->Width - 2 * DELTA_RECT_X - 10, 
		_y + _curSprite->_texture->Height - 2 * DELTA_RECT_Y);
}

void Mario::Fire()
{
	if(GL_CurForm != 2)
		return;
	if((_State == stand) || (_State == jumping))
	{
		bullet* sf;
		if(_turnLeft == true)
			sf = new bullet(_x - 30,_y + 35,_turnLeft);
		else sf = new bullet(_x + 50,_y + 35,_turnLeft);
		_listBullet.push_back(sf);
	}
}

void Mario::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{

	_listCollisionData.clear();
	int size = _listBullet.size();
	bullet* sf;
	bool _deadListBullet = true;
	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		if(sf->_State != dead)
			_deadListBullet = false;
		//sf->Update(time);
		sf->UpdateRealTimeCollision(time,listcollision);
	}

	if(_deadListBullet == true)
		_listBullet.clear();

	Transform();
			
	_nextx = _x + _vx * _time;
	_nexty = _y + _vy * _time;
	
	int size1 = listcollision->size();

	//MyObject* temp;
	if((_State != beforedead) && (_State != dead))
	{
		for(int k = 0 ; k < size1; ++k)
		{
			//////////////////////////////////////////////////////////////////////////
			if(listcollision->at(k)== this)
				continue;
			//////////////////////////////////////////////////////////////////////////

			if((listcollision->at(k)->_State == dead) || (listcollision->at(k)->_State == beforedead) || (listcollision->at(k)->_State == beforedead2))
				continue;
			if((listcollision->at(k)->_ID == EObject::TURTLE) || (listcollision->at(k)->_ID == EObject::BRICKBREAK) || (listcollision->at(k)->_ID == EObject::TREEMONSTER))
			{
				this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,_time);
			}
			else 
				if((listcollision->at(k)->_ID == EObject::BRICKITEM) && (listcollision->at(k)->_State != hasItem))
				{
					this->RealTimeCollisionWithItem(this->GetRect1(),(brickItem*)listcollision->at(k),k,_time);
					this->RealTimeCollision1(this->GetRect1(),listcollision->at(k),k,_time);
				}
				else this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,_time);
		}
	}
	bool check = _listCollisionData.check();
	if(check == true) // co va cham
	{
		bool backPosition = false;
		int a = _listCollisionData._listNewData.size();
		for(int m = 0;m < _listCollisionData._listNewData.size();m++)
		{
			int index = _listCollisionData._listNewData.at(m)->_indexObject;
			int idobject = _listCollisionData._listNewData.at(m)->_ID;
			EDirect dir = _listCollisionData._listNewData.at(m)->_dirCollision;
			State stateObject = listcollision->at(index)->_State;

			if(backPosition == false)
			{
				if((idobject == EObject::BRICKBREAK) || (idobject == EObject::BRICKITEM) || (idobject == EObject::BRICKQUESTION) || (idobject == EObject::BRICK))
				{
					// newwwwwwwwwwwwwwww
					_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
					_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
					backPosition = true;
				}
			}
			if(idobject == EObject::BRICKBREAK)
			{
				if((stateObject == breaking) || (stateObject == dead))
					break;
				if(dir == Top)
				{
					_vy = 0.0f;
					if(GL_CurForm == 0)
					{
						//break;
						listcollision->at(index)->_State = Move;
						break;
					}
					listcollision->at(index)->_State = breaking;
					SoundManager::GetInst()->PlayEffSound(SOUND_E_BROKEN);
					continue;
				}
				if(dir == Bottom)
				{
					_vy = 0.0f;
					if(_State != transform)
						_State = stand;
					continue;
				}
			}
			if(idobject == EObject::BRICKQUESTION)
			{
				if(dir == Top)
				{
					_vy = 0.0f;
					if(stateObject == hasCoin)
					{
						listcollision->at(index)->_State = noCoin;
						//listcollision->at(index)->_curSprite->SelectIndex(0);
						this->gold++;
						SoundManager::GetInst()->PlayEffSound(SOUND_E_COIN);
						continue;
					}
				}
				if(dir == Bottom)
				{
					_vy = 0.0f;
					if(_State != transform)
						_State = stand;
					continue;
				}
			}
			if(idobject == EObject::BRICKITEM)
			{
				if(dir == Top)
				{
					_vy = 0.0f;
					if(stateObject != hasItem)
						continue;
					listcollision->at(index)->_State = stand;
					((brickItem*)listcollision->at(index))->_curSprite->SelectIndex(0);
					//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_UP);
					continue;
				}
			}
			if(idobject == EObject::COIN)
			{
				if(stateObject == dead)
					break;
				listcollision->at(index)->_State = dead;
				// tien tang
				this->gold++;
				//sound
				SoundManager::GetInst()->PlayEffSound(SOUND_E_COIN);
				continue;
			}
			if(idobject == ITEM)
			{
				((brickItem*)listcollision->at(index))->_item->_State = dead;
				if(GL_CurForm != 2)
				{
					_State = transform;
					GL_NextForm = GL_CurForm + 1;
					if((GL_CurForm == 0) && (GL_NextForm == 1))
						_y -= 50;
				}// player transform or + heart khi nhat dc item here
			}
			if(idobject == EObject::TREEMONSTER)
			{
				_State = transform;
				if(GL_CurForm != 0)
					GL_NextForm = GL_CurForm - 1;
				if(GL_CurForm == 0)
				{
					_vy = -2.0;
					_State = beforedead;
				}
				break;
			}
			if(idobject == EObject::FUNGI)
			{
				if(_State == transform)
					break;
				if((stateObject == dead) || (stateObject == beforedead) || (stateObject == beforedead2))
					break;
				if(dir == Bottom)
				{
					_vy = -1.5;
					_State = jumping;
					listcollision->at(index)->_State = beforedead;
				//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);
					if(backPosition == false)
					{
						{
							_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
							_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
							backPosition = true;
						}
					}
					continue;
				}
				else
				{
					_State = transform;
					if(GL_CurForm != 0)
						GL_NextForm = GL_CurForm - 1;
					if(GL_CurForm == 0)
					{
						_vy = -2.0;
						_State = beforedead;
					}
					continue;
				}
			}
			if(idobject == EObject::TURTLE)
			{
				if(_State == transform)
					break;
				if(stateObject == dead)
					break;
				if(dir == Bottom)
				{
					if((stateObject == stand) || (stateObject == attack))
					{
						_nexty += 10;
					}
					_vy = -1.5;
					_State = jumping;
					//sound
					SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);

					if(backPosition == false)
					{
						{
							_nextx -= _listCollisionData._listNewData.at(m)->_deltaX;
							_nexty -= _listCollisionData._listNewData.at(m)->_deltaY;
							backPosition = true;
						}
					}
					if((stateObject == Move) || (stateObject == attack))
					{
						listcollision->at(index)->_State = stand;
						//(turtle*)listcollision->at(index)->_curSprite->SelectIndex(2);
						((turtle*)listcollision->at(index))->_curSprite->SelectIndex(2);
						((turtle*)listcollision->at(index))->_TimeStand = 0;
						((turtle*)listcollision->at(index))->_TimeAttack = 0;
					}
					continue;
				}
				if(dir != EDirect::Bottom)
				{
					if((stateObject == Move) || (stateObject == attack))
					{
						if(((turtle*)listcollision->at(index))->_TimeAttack < 15)
							break;
						/*
						obj->_State = transform;
						// player bi mat mau
						// set next form
						*/
						_State = transform;
						if(GL_CurForm != 0)
							GL_NextForm = GL_CurForm - 1;
						if(GL_CurForm == 0)
						{
							_vy = -2.0;
							_State = beforedead;
							break;
						}
						continue;
					}
				}
				if((dir == Right) || (dir == Left))
				{
					if((stateObject == stand) && (((turtle*)listcollision->at(index))->_TimeStand > 20))
					{
						((turtle*)listcollision->at(index))->_curSprite->_start = 2;
						((turtle*)listcollision->at(index))->_curSprite->_start = 4;
						listcollision->at(index)->_State = attack;
						((turtle*)listcollision->at(index))->_TimeAttack = 0;
						if(dir == Left)							
							listcollision->at(index)->_turnLeft = true;
						if(dir == Right)
							listcollision->at(index)->_turnLeft = false;
						continue;
					}
				}
			}
		}
	} 
			
	_vy += GRAVITY * time;
	_time = time;
	CheckTitleCollision(_vx,_vy,_nextx,_nexty, GL_Width, GL_Height, _curSprite->_texture->Width,_curSprite->_texture->Height);
	//if(_vy != 0.0f)
	//	int S = 0;
	_x = _nextx;
	_y = _nexty;

	//beforedead -> dead
	if(_State == beforedead)
	{
		_curSprite->SelectIndex(5);
		
		//check is dead
		if(_y > FALL_DEAD_HIGH * GL_MapH)
		{
			_State = dead;

			//reborn
			if(this->life > 0)
			{
				this->life--;
				this->_State = stand;

				this->_vx = 0;
				this->_vy = 0;

				this->_y = _lasty; //MapLoader::_mariox * TILE;
				this->_x = _lastx; //MapLoader::_mariox * TILE;
			}
		}

		return;
	}
	else //dead when fall out of map
	{
		if(_y > GL_MapH && _State != dead && _State != beforedead && _State != beforedead2)
		{
			_State = beforedead;
			this->_vy = -2.5f;
		}
	}

	if(_vx != 0)
	{
		_curSprite->Update(time);
	}
	if(_State == transform)
		return;

	// do when change dir suddenly
	if((_turnLeft == true) && (_vx > 0.0f))
		_curSprite->SelectIndex(4);
	if((_turnLeft == false) && (_vx < 0.0f))
		_curSprite->SelectIndex(4);

	if(_State == jumping){
		_curSprite->SelectIndex(3);
	}

	
	{//do not run out of the map
		//right
		if(_x + this->_curSprite->_texture->Width >= GL_MapW)
		{
			_x = GL_MapW - this->_curSprite->_texture->Width;
		}

		//left
		if(_x <= 0)
		{
			_x = 0;
		}
	}
	

	//save last position
	if(_State == stand || _State == Move)
	{
		if(abs(_x - _lastx) >= DISTANCE_WITH_LAST_POSITION_X)
		{
			_lastx = _x;
			_lasty = _y;
		}
	}
}


void Mario::CheckTitleCollision(float &_vx,float &_vy,float &_nextX,float &_nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if((_State == beforedead) || (_State == dead))
	{
		//_x = _nextX;
		_nextY = _nextY;
		return;
	}	
	bool jump = true;
	if (_vy >= 0.0f){
		// DOWN
		_nextY ;
		bool iColTer = false;
		for (int j = (_y + _height)/TILE; j <=  (_nextY+_height + 1)/TILE ;j++){
			for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
			if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					//if(checkY == false)
					{
						jump = false;
						this->_vy = 0;
						iColTer = true;
						_nextY = TILE * (j) - _height - 1 ;
						if(_State != transform)
							_State = stand;
						break;
					}
				}
			}
			if (iColTer == true){
				break;
			}

		}
		if (iColTer == false){
			_nextY = _nextY ;
		}

	}else{
		// UP
		int n = (_nextY/TILE);
		int m = (_y/TILE);
		if (n!=m ){

			bool iColTerY = false;
			for (int j = _y/TILE-1; j >  _nextY/TILE-1;j--){
				for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						//if(checkY == true)
						{
							jump = false;
							iColTerY = true;
							_nextY = TILE * (j+1);
							_vy = 0;//fabs(_vy);
							break;
						}
					}
				}
				if (iColTerY == true){
					break;
				}
			}

			if (iColTerY == false){
				_nextY = _nextY;
			}

		}else{
			_nextY = _nextY;
		}
	}
	if((_State != transform) && (_State != dead) && (_State != beforedead) && (_State != beforedead2))
	{
		if(jump == true)
			_State = jumping;
	}

	if (_vx > 0)
	{
		bool iColTerX1 = false;
		for (int i = (_x + _width)/TILE ; i <  (_nextX+_width)/TILE;i++)
		{
			for (int j = _y/TILE;j < (int)((_y+_height-1)/TILE) +1;j++ )
			{
				if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
				{
					iColTerX1 = true;
					_nextX = TILE * (i) - _width;
					break;
				}
			}
			if (iColTerX1 == true)
			{
				break;
			}
		}

		if (iColTerX1 == false){
			_nextX = _nextX;
		}

	}
	else
	{
		if (_vx <= 0){

			if (_nextX <= 0)
			{
				_nextX = 0;
			}
			bool iColTerX2 = false;
			for (int i = _x/TILE-1; i >  _nextX/TILE-1;i--) // 
			{
				for (int j = _y/TILE ;j < int((_y+_height-1)/TILE) +1 ; j++ )
				{
					if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
					{
						iColTerX2 = true;
						_nextX = TILE * (i+1);
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
				_nextX = _nextX;
			}

		}		
	}
}




void Mario::RealTimeCollisionWithItem(CRECT r1, brickItem *obj,int indexObject,int time)
{
	if(obj->_State == hasItem)
		return;
	if(obj->_item->_State == dead)
		return;
	float x0, y0, x1, y1, X, Y;
	bool _left2right = true;
	bool _up2down = true;
	
	bool _collision = false;
	bool _rightleft = false;
	// khoang cach lui ve theo truc x, va truc y
	float deltaX = 0.0f;
	float deltaY = 0.0f;

	// khoang cach tu diem xuat phat den giao diem
	float delta = 0.0f; // xet chon object va cham
	EDirect _dirCollision = EDirect::None;

	if(_vx > 0) // left -> right
	{
		_left2right = true;
		x0 = r1.Right;
		X = obj->_item->GetRect().Left;
	}
	else // right -> left
	{
		_left2right = false;
		x0 = r1.Left;
		X = obj->_item->GetRect().Right;
	}

	if(_vy > 0) // top -> down
	{
		_up2down = true;
		y0 = r1.Bottom;
		Y = obj->_item->GetRect().Top;
	}
	else // down -> top
	{
		_up2down = false;
		y0 = r1.Top;
		Y = obj->_item->GetRect().Bottom;
	}
	//x1 = _x + _vx; // next position after moving
	//y1 = _y + _vy; // next position after moving
	//if(_vx > 0 )
		x1 = x0 + (_nextx - _x);
	//else x1 = x0 - (_nextx - _x);
	//if(_vy > 0 )
		y1 = y0 + (_nexty - _y);
	//else y1 = y0 - (_nexty - _y);

	// xet ngang

	float giaodiemX, giaodiemX2, giaodiemY, giaodiemY2;
	giaodiemY = (_vy / _vx) * (X - x0) + y0;
	giaodiemX = X;
	if(_vy > 0)
		giaodiemY2 = giaodiemY - (r1.Bottom - r1.Top);
	else giaodiemY2 = giaodiemY + (r1.Bottom - r1.Top);

	if ((obj->_item->GetRect().Top <= giaodiemY) && (giaodiemY <= obj->_item->GetRect().Bottom))
	{
		if (_left2right == true)
		{
			//x1 = _nextx + (r1.Right - r1.Left);
			if ((x0 <= giaodiemX) && (giaodiemX <= x1))
				// diem o tren cua ball
			{
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
			//x1 = _nextx;
		}
		else
		{
			if ((x0 >= giaodiemX) && (giaodiemX >= x1))
				// diem o tren cua ball
			{
				// va cham left
				_collision = true;
				_dirCollision = EDirect::Left;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		// diem o duoi
		//xet giao diem 2, cach giaodiemY 1 doan = chieu cao cua ball
		//giaodiemY += 100.0f;
		if ((obj->_item->GetRect().Top <= giaodiemY2) && (giaodiemY2 <= obj->_item->GetRect().Bottom))
		{
			if (_left2right == true)
			{
				//x1 = _nextx + (r1.Right - r1.Left);
				if ((x0 <= giaodiemX) && (giaodiemX <= x1))
					// diem o tren cua ball
				{
					// va cham right
					_collision = true;
					_dirCollision = EDirect::Right;
					delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
				}
				//x1 = _nextx;
			}
			else
			{
				if ((x0 >= giaodiemX) && (giaodiemX >= x1))
					// diem o tren cua ball
				{
					// va cham left
					_collision = true;
					_dirCollision = EDirect::Left;
					delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
				}
			}
		}
	}

	if (_left2right == true)
	{
		//x1 = _nextx + (r1.Right - r1.Left);
		if ((x0 <= giaodiemX) && (giaodiemX <= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < obj->_item->GetRect().Top) && (giaodiemY2 > obj->_item->GetRect().Bottom))
			{
				// va cham right
				_collision = true;
				_dirCollision = EDirect::Right;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
		//x1 = _nextx;
	}
	else
	{
		if ((x0 >= giaodiemX) && (giaodiemX >= x1))
			// diem o tren cua ball
		{
			if ((giaodiemY < obj->_item->GetRect().Top) && (giaodiemY2 > obj->_item->GetRect().Bottom))
			{
				// va cham left
				_collision = true;
				_dirCollision = EDirect::Left;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	/*
	{
		if (_vx > 0)
			deltaX = (x1 - giaodiemX); //+ (r1.Right - r1.Left);
		if (_vx < 0)
			deltaX = (x1 - giaodiemX) - (r1.Right - r1.Left);
		if(_vx == 0)
			deltaX = 0.0f;

	}
	*/
	if(_collision == true)
	{
		deltaX = (x1 - giaodiemX);
		_rightleft = true;
	}
	
	// xet doc

	giaodiemX = x0 + (_vx / _vy) * (Y - y0);
	giaodiemY = Y;
	if(_vx > 0)
		giaodiemX2 = giaodiemX - (r1.Right - r1.Left);
	else
		giaodiemX2 = giaodiemX + (r1.Right - r1.Left);
	if ((obj->_item->GetRect().Left <= giaodiemX) && (giaodiemX <= obj->_item->GetRect().Right))
	{
		if (_up2down == true)
		{
			//y1 = _nexty + (r1.Bottom - r1.Top);
			if ((giaodiemY >= y0) && (giaodiemY <= y1))
			{
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);

			}
			//y1 = _nexty;
		}
		else
		{
			if ((giaodiemY <= y0) && (giaodiemY >= y1))
			{
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}
	else
	{
		if ((obj->_item->GetRect().Left <= giaodiemX2) && (giaodiemX2 <= obj->_item->GetRect().Right))
		{
			if (_up2down == true)
			{
				//y1 = _nexty + (r1.Bottom - r1.Top);
				if ((giaodiemY >= y0) && (giaodiemY <= y1))
				{
					// va cham down
					_collision = true;
					_dirCollision = EDirect::Bottom;
					delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
				}
				//y1 = _nexty;
			}
			else
			{
				if ((giaodiemY <= y0) && (giaodiemY >= y1))
				{
					// va cham top
					_collision = true;
					_dirCollision = EDirect::Top;
					delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
				}
			}
		}
	}

	if (_up2down == true)
	{
		//y1 = _nexty + (r1.Bottom - r1.Top);
		if ((giaodiemY >= y0) && (giaodiemY <= y1))
		{
			if ((giaodiemX < obj->_item->GetRect().Left) && (giaodiemX2 > obj->_item->GetRect().Right))
			{
				// va cham down
				_collision = true;
				_dirCollision = EDirect::Bottom;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
		//y1 = _nexty;
	}
	else
	{
		if ((giaodiemY <= y0) && (giaodiemY >= y1))
		{
			if ((giaodiemX < obj->_item->GetRect().Left) && (giaodiemX2 > obj->_item->GetRect().Right))
			{
				// va cham top
				_collision = true;
				_dirCollision = EDirect::Top;
				delta = KhoangCach(x0,y0,giaodiemX,giaodiemY);
			}
		}
	}

	//if (_collision == true)
// 	{
// 
// 		if (_vy > 0)
// 			deltaY = (y1 - giaodiemY); //+ (r1.Bottom - r1.Top);
// 		if (_vy < 0)
// 			deltaY = (y1 - giaodiemY);
// 		if(_vy == 0)
// 			deltaY = 0.0f;
// 	}
	//if((_vy > 0.0f ) && (_vx == 0.0f))
		if((_vy != 0.0f ) && (_vx == 0))
			deltaY = (y1 - giaodiemY);
	//if((_vy < 0.0f ) && (_vx == 0.0f))
		//deltaY = (y1 - giaodiemY);
		//if(_vy != 0.0f)
			//deltaX = (x1 - giaodiemX);
		//if(_vy == 0.0f)
		//	deltaY = 0.0f;
//		if(_vx == 0.0f)
	//		deltaX = 0.0f;
		if(_collision == true)
		{
			if((_vx != 0.0f) && (_vy != 0.0f))
			{
				deltaY = (y1 - giaodiemY);

				if(_rightleft == false)
				{
					if((_vy >= (0.01*(time - 1))) && (_vy <= (0.01*(time + 1))))
					{

					}
					else
					{
						if(_vx > 0.0f)
							deltaX = x1 - giaodiemX;
						if(_vx < 0.0f)
							deltaX = -(x1 - giaodiemX);
					}
				}
			}
			if(_vy == 0.0f)
				deltaY = 0.0f;
			/*if(_vx > 0)
				deltaX +=1;
			if(_vx < 0)
				deltaX -=1;
			if(_vy > 0)
				deltaY +=1;
			if(_vx < 0)
				deltaY -=1;*/
			if(_dirCollision == Right)
				deltaY = 0.0f;
			if(_dirCollision == Left)
				deltaY = 0.0f;
			if(_vx == 0.0f)
				deltaX = 0.0f;
			//deltaX = (x1 - giaodiemX2);
			//deltaX = (x1 - X);
		}


	if (_collision == true)
	{
		//CollisionData
		if(_dirCollision == Right)
			int v =0;
		if(_dirCollision == Left)
			int d=0;
		_listCollisionData.add(new CollisionData(EObject::ITEM,_dirCollision,deltaX,deltaY,delta,indexObject));
		//_nextx -= (deltaX );
		//_nexty -= (deltaY );
		//_nexty += 1;
		//_vy = 0;
	}

	// luu IDobject : de xu li logic,state neu co va cham
	// luu deltaX,deltaY : de xu li cap nhat position
	// _dirCollision : luu huong va cham : uu tien top,bottom -> xu li logic,state neu co va cham theo huong
	// luu delta : de chon object nao va cham
	// index cua object trong ListObject
	// toan bo luu vo 1 list
	// cuoi cung lay list nay ra xet lai. chon nhung object thuc su va cham roi xu li
}
