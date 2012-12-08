// tieu nun, fix all

#include "Mario.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "SoundManager.h"
#include "MapLoader.h"


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
	_startx = _x = x;
	_starty = _y = y;
	_vx = 0;
	_vy = 0;
	_TimeTransform = 0;
	_ID = EObject::MARIO;

	life = 3;
	gold = 0;
	exp = 0;
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
	//bullets
	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Update(time);
	}


	//check if transfoming
	Transform();

	static int timeReborn = TIME_REBORN + 1;

	_time = time;

	float _NextX = _x + _vx ;
	float _NextY = _y + _vy * _time;

	_vy += GRAVITY * time;

	//if mario move so fast, collision is not true
	if(_vy > MAX_MARIO_VY)
		_vy = MAX_MARIO_VY;
	CheckTitleCollision(_vx, _vy, _NextX,_NextY, GL_Width, GL_Height, _curSprite->_texture->Width,_curSprite->_texture->Height);

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
				timeReborn = 0;

				this->life--;
				this->_State = stand;

				this->_vx = 0;
				this->_vy = -2.0f;

				this->_y = _starty; //MapLoader::_mariox * TILE;
				this->_x = _startx; //MapLoader::_mariox * TILE;

				this->Jump();

				_State = reborn;
			}
		}

		return;
	}
	else //dead when fall out of map
	{
		if(_y > GL_MapH && _State != dead && _State != beforedead && _State != beforedead2)
		{
			RunBeforeDie();
		}
	}

	//change sprite
	if(GL_CurForm == 0) // smaller
	{
		_curSprite = _sprMarioSmaller;
	}
	else if(GL_CurForm == 1) // larger
	{
		_curSprite = _sprMarioLarger;
	}
	else					// fire
	{
		_curSprite = _sprMarioFire;
	}

	//new tan long
	if(abs(_vy) >= 0.5f && _State != reborn && _State != beforedead && _State != beforedead2 && _State != dead)
	{
		_State = jumping;
	}

	//reborn state
	timeReborn += _time;
	if(timeReborn < TIME_REBORN)
	{
		_State = reborn;
	}else
	{
		timeReborn = TIME_REBORN + 1;
	}

	//update sprite
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

	//save last position
	if(_State == State::stand || _State == State::Move || _State == State::alive)
	{
		if(abs(_x - _startx) >= DISTANCE_WITH_LAST_POSITION_X)
		{
			_startx = _x;
			_starty = _y;
		}
	}
}

void Mario::Render()
{
	//reborn alpha
	if(_State == reborn)
		_curSprite->_color = D3DCOLOR_ARGB(100, 255, 255, 255);
	else
		_curSprite->_color = D3DCOLOR_ARGB(255, 255, 255, 255);

	if(_turnLeft == false)
	{
		_curSprite->Render((int)_x, (int)_y + 1);
	}
	else 
	{
		_curSprite->RenderScaleX((int)_x, (int)_y + 1);
	}

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

void Mario::RunBeforeDie()
{
	_State = beforedead;
	this->_vy = -2.5f;
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
					_y -= 50;
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
						_y +=50;
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

void Mario::TransformMario(int curForm, int nextForm)
{
	_State = transform;
	GL_CurForm = curForm;
	GL_NextForm = nextForm;

	//Jump();

	//if((GL_CurForm == 0) && (GL_NextForm == 1))
	_vy -= 0.5f;

	//SOUND
	SoundManager::GetInst()->PlayEffSound(SOUND_E_GROW);
}

void Mario::CheckCollision(MyObject* obj)
{	
	//check collision bullet with object
	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->CheckCollision(obj);
	}

	//check collision mario
	if(_State == beforedead || _State == dead || _State == beforedead2 || _State == reborn)
		return;
	
	if((obj->_ID == EObject::BRICKITEM) || (obj->_ID == EObject::BRICKQUESTION) || (obj->_ID == EObject::BRICKBREAK) )
	{
		if(_State == transform)
			return;

		//debug
		if(obj->_State == dead)
			return;

		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Top:
			_vy = GRAVITY * _time;
			_y = obj->_y + TILE;

			//add exp
			exp += EXP_FOR_BRICK;

			//gold
			if(obj->_ID == BRICKQUESTION)
			{
				this->gold++;
			}
			break;

		case Bottom:
			_vy = 0;
			_y = obj->_y - _curSprite->_texture->Height ;
			if(_State != transform)
				_State = stand;
			break;

		case Left:
			//_vx = 0;
			_x = obj->_x + TILE;
			break;

		case Right:
			//_vx = 0;
			_x = obj->_x - this->_curSprite->_texture->Width ;
			break;
		}
	}

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
					if(obj->_ID == EObject::FUNGI && obj->_State == beforedead2)
					{
					}
					else
					{
						_vy = -1.5;
						_State = jumping;

						//tan long
						//add exp
						exp += EXP_FOR_OBJECT;

						//sound
						SoundManager::GetInst()->PlayEffSound(SOUND_E_TOUCH_TIRTLE);
					}
				}				
				break;
		}
	}
}

CRECT Mario::GetRect()
{
	return CRECT(
		_x, //+ DELTA_RECT_X, 
		_y, //+ DELTA_RECT_Y, 
		_x + _curSprite->_texture->Width,// - 2 * DELTA_RECT_X, 
		_y + _curSprite->_texture->Height);// - 2 * DELTA_RECT_Y);
}

void Mario::Fire()
{
	if(GL_CurForm != 2)
		return;

	if((_State == stand) || (_State == jumping) || (_State == Move))
	{
		bullet* sf;
		if(_turnLeft == true)
			sf = new bullet(_x - 30,_y + 35,_turnLeft);
		else sf = new bullet(_x + 50,_y + 35,_turnLeft);
		_listBullet.push_back(sf);
	}
}