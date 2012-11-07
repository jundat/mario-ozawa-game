#include "MyObject.h"
#include "Global.h"
#include "ResourceManager.h"
#include <math.h>
#include "TileMap.h"

MyObject::MyObject(float xx, float yy)
{
	_x = xx;
	_y = yy;
	_State = State::alive;
}


MyObject::~MyObject(void)
{

}

//MyObject::MyObject(const MyObject* obj)
//{
//
//}

CRECT MyObject::GetRect()
{
	return CRECT(_x, _y, _x + TILE, _y + TILE);
}

bool MyObject::CanCollide(){
	return true;
}

bool MyObject::IsAlive(){
	return true;
}

void MyObject::Update(int time)
{
}

void MyObject::Render()
{

}

void MyObject::CheckCollision(MyObject* obj)
{
	switch(this->GetCollisionDirection(obj->GetRect(), this->GetRect()))
	{
	case Top:
		break;

	case Bottom:
		break;

	case Left:
		break;

	case Right:
		break;

	case None:
		break;
	}
}

EDirect MyObject::GetCollisionDirection(CRECT r1, CRECT r2)
{
	if (r1.IsCollision(r2))
	{
		float top = abs(r1.Top - r2.Bottom);
		float botom = abs(r1.Bottom - r2.Top);
		float left = abs(r1.Left - r2.Right);
		float right = abs(r1.Right - r2.Left);
		
		float minRL = right < left ? right : left;
		float minTB = top < botom ? top : botom;
		float rs = minRL < minTB ? minRL : minTB;

		if (rs == top)
		{
			return EDirect::Top;
		}
		if (rs == botom)
		{
			return EDirect::Bottom;
		}
		if (rs == left)
		{
			return EDirect::Left;
		}
		if (rs == right)
		{
			return EDirect::Right;
		}
	}

	return EDirect::None;
}

void MyObject::CheckTitleCollision(float &_vx,float &_vy,float _nextX,float _nextY,float _maxWidth,float _maxHeight,int _width,int _height)
{
	if((_State == beforedead) || (_State == dead))
	{
		//_x = _nextX;
		_y = _nextY;
		return;
	}
	


	if (_vy >= 0){
	// DOWN
	bool iColTer = false;
	for (int j = (_y + _height)/TILE; j <  (_nextY+_height)/TILE ;j++){
		for (int i = _x/TILE;i < (_x+_width)/TILE;i++ ){
			if (i >= 0 && i < GL_MapTileW && j >= 0 && j < GL_MapTileH && TileMap::GetInst()->_board[j][i] != 0)
			{
				//if(checkY == false)
				{
					_vy = 0;
					iColTer = true;
					_y = TILE * (j) - _height;
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
		_y = _nextY;
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
						iColTerY = true;
						_y = TILE * (j+1);
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
			_y = _nextY;
		}

	}else{
		_y = _nextY;
	}

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
					_x = TILE * (i) - _width;
					break;
				}
			}
			if (iColTerX1 == true)
			{
				break;
			}
		}

		if (iColTerX1 == false){
			_x = _nextX;
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
						_x = TILE * (i+1);
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
				_x = _nextX;
			}

		}		
	}
}