
#include "BrickBreak.h"
#include "ResourceManager.h"
#include "Global.h"
#include "SoundManager.h"
#include "TileMap.h"

brickBreak::brickBreak(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/Brick_Break.png"), 500);
	_ID = EObject::BRICKBREAK;
	_State = stand;
	up = true;
	_yOri = y;
	_rectBreak1.left = 0;
	_rectBreak1.top = 0;
	_rectBreak1.right = _rectBreak1.left + TILE/2;
	_rectBreak1.bottom = _rectBreak1.top + TILE/2;

	_rectBreak2.left = TILE/2;
	_rectBreak2.top = 0;
	_rectBreak2.right = _rectBreak2.left + TILE/2;
	_rectBreak2.bottom = _rectBreak2.top + TILE/2;

	_rectBreak3.left = 0;
	_rectBreak3.top = TILE/2;
	_rectBreak3.right = _rectBreak3.left + TILE/2;
	_rectBreak3.bottom = _rectBreak3.top + TILE/2;

	_rectBreak4.left = TILE/2;
	_rectBreak4.top = TILE/2;
	_rectBreak4.right = _rectBreak4.left + TILE/2;
	_rectBreak4.bottom = _rectBreak4.top + TILE/2;

	_xBreak1 = _x;
	_yBreak1 = _y;

	_xBreak2 = _x + TILE/2;
	_yBreak2 = _y;

	_xBreak3 = _x;
	_yBreak3 = _y + TILE/2;

	_xBreak4 = _x + TILE/2;
	_yBreak4 = _y + TILE/2;

}


brickBreak::~brickBreak(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void brickBreak::Update(int time)
{
	return;
	if(_State == breaking)
	{
		if((_x - _xBreak1) < 50)
		//	_State = dead;
		{
			_xBreak1 -= 0.7*time;
			_xBreak2 += 0.7*time;
			_xBreak3 -= 0.7*time;
			_xBreak4 += 0.7*time;

			_yBreak1 -= 0.8*time;
			_yBreak2 -= 0.8*time;
			_yBreak3 -= 0.4*time;
			_yBreak4 -= 0.4*time;
		}
		else
		{
			_xBreak1 -= 0.4*time;
			_xBreak2 += 0.4*time;
			_xBreak3 -= 0.4*time;
			_xBreak4 += 0.4*time;

			_yBreak1 += 0.5*time;
			_yBreak2 += 0.5*time;
			_yBreak3 += 1.0*time;
			_yBreak4 += 1.0*time;
		}
		if((_x - _xBreak1) > 100)
		{
			_State = dead;
			TileMap::GetInst()->RemoveTileAt(_x,_y);
		}
	}
	if(_State == Move)
	{
		if(up == true)
		{
			_nexty -= 0.22f * time;
			if(_nexty <= (_yOri - 25))
			{
				_nexty = _yOri - 25;
				up = false;
			}
		}
		if(up == false)
		{
			_nexty+= 0.22f * time;
			if(_nexty >= _yOri)
			{
				_nexty = _yOri;
				up = true;
				_State = stand;
			}
		}
		_y = _nexty;
	}
	//_curSprite->Update(time);
}

void brickBreak::UpdateRealTimeCollision(int time,vector<MyObject*>*listcollision)
{
	_listCollisionData.clear();
	if(_State == breaking)
	{
		if((_x - _xBreak1) < 50)
			//	_State = dead;
		{
			_xBreak1 -= 0.7*time;
			_xBreak2 += 0.7*time;
			_xBreak3 -= 0.7*time;
			_xBreak4 += 0.7*time;

			_yBreak1 -= 0.8*time;
			_yBreak2 -= 0.8*time;
			_yBreak3 -= 0.4*time;
			_yBreak4 -= 0.4*time;
		}
		else
		{
			_xBreak1 -= 0.4*time;
			_xBreak2 += 0.4*time;
			_xBreak3 -= 0.4*time;
			_xBreak4 += 0.4*time;

			_yBreak1 += 0.5*time;
			_yBreak2 += 0.5*time;
			_yBreak3 += 1.0*time;
			_yBreak4 += 1.0*time;
		}
		if((_x - _xBreak1) > 100)
		{
			_State = dead;
			TileMap::GetInst()->RemoveTileAt(_x,_y);
		}
	}
	if(_State == Move)
	{
		if(up == true)
		{
			_nexty -= 0.22f * time;
			if(_nexty <= (_yOri - 25))
			{
				_nexty = _yOri - 25;
				up = false;
			}
		}
		if(up == false)
		{
			_nexty+= 0.22f * time;
			if(_nexty >= _yOri)
			{
				_nexty = _yOri;
				up = true;
				_State = stand;
			}
		}

		int size1 = listcollision->size();

		if((_State != beforedead2) && (_State != beforedead) && (_State != dead))
		{
			for(int k = 0 ; k < size1; ++k)
			{
				if(listcollision->at(k) == this)
					continue;
				if((listcollision->at(k)->_ID == EObject::FUNGI) || (listcollision->at(k)->_ID == EObject::TURTLE))
					this->RealTimeCollision1(this->GetRect(),listcollision->at(k),k,time);
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

				if((idobject == EObject::FUNGI) || (idobject == EObject::TURTLE))
				{
					listcollision->at(index)->_vy = -0.85f;
					listcollision->at(index)->_State = beforedead2;
				}
			}
		} 
		_y = _nexty;
	}
	//_curSprite->Update(time);
}


void brickBreak::Render()
{
	if((_State == stand) || (_State == Move))
		_curSprite->Render((int)_x, (int)_y);
	if(_State == breaking)
	{
		_curSprite->RenderRect((int)_xBreak1,(int)_yBreak1,_rectBreak1);
		_curSprite->RenderRect((int)_xBreak2,(int)_yBreak2,_rectBreak2);
		_curSprite->RenderRect((int)_xBreak3,(int)_yBreak3,_rectBreak3);
		_curSprite->RenderRect((int)_xBreak4,(int)_yBreak4,_rectBreak4);
	}
}
CRECT brickBreak::GetRect()
{
	return CRECT(_x , _y, _x + _curSprite->_texture->Width , _y + _curSprite->_texture->Height );
	//return CRECT(_x + 13, _y, _x + _curSprite->_texture->Width - 26, _y + _curSprite->_texture->Height );
}
void brickBreak::CheckCollision(MyObject* obj)
{
	/*
	if(_State != stand)
		return;

	if(obj->_ID == EObject::MARIO)
	{
		if((obj->_State == beforedead) || (obj->_State == dead))
			return;

		if(GL_CurForm == 0)
			return;
		EDirect dir = this->GetCollisionDirection(this->GetRect(), obj->GetRect());

		switch(dir)
		{
		case Bottom:
			if(_State == stand)
			{
				_State = breaking;
				SoundManager::GetInst()->PlayEffSound(SOUND_E_BROKEN);
			}
			break;
		case Top:
			break;

		case Left:
			break;

		case Right:
			break;
			
		case None:
			break;
		}
	} */
}


