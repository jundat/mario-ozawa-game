// tieu nun, fix all

#include "Mario.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "SoundManager.h"

#define START_LIFE 4

Mario::Mario(float x, float y)	: MyObject(x, y)
{

	_sprMarioSmaller = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioSmaller.png"), 50);
	_sprMarioLarger = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioLarger.png"), 50);
	_sprMarioFire = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioFire.png"), 50);
	_turnLeft = false;
	_curSprite = _sprMarioLarger;
	_curSprite->_start = 0;
	_curSprite->_end = 2;
	GL_CurForm = 1;
	GL_NextForm = 0;
	_State = stand;
	_x = x;
	_y = y;
	_vx = 0;
	_vy = 0;
	_TimeTransform = 0;
	_ID = EObject::MARIO;

	gold = 0;
	life = START_LIFE;

	//_listBullet = new vector <bullet*> ;

	//bullet *aa;
	//aa = new bullet(0,0,true);
	//_listBullet->push_back(aa);
}

Mario::~Mario(void)
{
	delete _sprMarioSmaller;
	delete _sprMarioLarger;
	delete _sprMarioFire;
}

void Mario::Update(int time)
{
	int size = _listBullet.size();
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

	if(_State == beforedead)
	{
		_curSprite->SelectIndex(5);
		return;
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
}

void Mario::Render()
{
	int size = _listBullet.size();
	bullet* sf;

	for(int i = 0 ; i < size; ++i)
	{
		sf = _listBullet[i];
		sf->Render();
	}

	if(_turnLeft == false)
		_curSprite->Render((int)_x, (int)_y);
	else _curSprite->RenderScale((int)_x, (int)_y);
}

void Mario::TurnRight()
{
	if(_State == beforedead)
		return;
	// if press Right, Update _vx
	_vx += FRICTION_X * _time;
	if(_vx >= 12.0f)
		_vx = 12.0f;
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
	if(_vx <= -12.0f)
		_vx = -12.0f;
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
				_curSprite = _sprMarioSmaller;
			}
			if(GL_NextForm == 1)
			{
				_curSprite = _sprMarioLarger;
			}
			if(GL_NextForm == 2)
			{
				_curSprite = _sprMarioFire;
			}
		}
		else
		{
			if(_TimeTransform % 5 == 2)
			{
				if(GL_CurForm == 0)
				{
					_curSprite = _sprMarioSmaller;
				}
				if(GL_CurForm == 1)
				{
					_curSprite =_sprMarioLarger;
				}
				if(GL_CurForm == 2)
				{
					_curSprite = _sprMarioFire;
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
		sf->CheckCollision(obj);
	}
	if((_State == beforedead) || (_State == dead))
		return;
	if(obj->_ID == EObject::BRICK)
	{
		//if(_State == transform)
		//	return;
		if(obj->_State == dead)
			return;
		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Top:
			_vy = 0;
			_y = obj->_y + TILE + 1;
			break;

		case Bottom:
			_vy = 0;
			_y = obj->_y - _curSprite->_texture->Height;
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

	if(obj->_ID == EObject::PIPE)
	{
		if(obj->_State == dead)
			return;
		switch(this->GetCollisionDirection(this->GetRect(), obj->GetRect()))
		{
		case Top:
			_vy = 0;
			_y = obj->_y + 100 + 1;
			break;
		case Bottom:
			_vy = 0;
			_y = obj->_y - _curSprite->_texture->Height ;
			if((_vy == 0) && (_State != transform))
				_State = stand;
			break;
		case Left:
			//_vx = 0;
			_x = obj->_x + 100 ;
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
				_vy = -1.5;
				_State = jumping;
				break;
		}
	}
}

CRECT Mario::GetRect()
{
	return CRECT(
		_x, 
		_y, 
		_x + _curSprite->_texture->Width, 
		_y + _curSprite->_texture->Height);
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