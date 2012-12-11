#include "SelectWorldSence.h"
#include "MenuSence.h"
#include "PlaySence.h"
#include "MapLoader.h"
#include "Writer.h"
#include "SoundManager.h"
#include "ZoomSence.h"


SelectWorldSence::SelectWorldSence(Game* game, int timeAni)
	: GameSence(game, timeAni)
{
	//no play sound
}

SelectWorldSence::~SelectWorldSence(void)
{
	if(_QuadTree != NULL)
	{
		delete _QuadTree;
		_QuadTree = NULL;
	}

	if(_MapLoader != NULL)
	{
		delete _MapLoader;
		_MapLoader = NULL;
	}

	if(_Camera != NULL)
	{
		delete _Camera;
		_Camera = NULL;
	}

	if(_mario != NULL)
	{
		delete _mario;
		_mario = NULL;
	}

	if(_BackgroundMng != NULL)
	{
		delete _BackgroundMng;
		_BackgroundMng = NULL;
	}

	if(_effectMoveDown != NULL)
	{
		delete _effectMoveDown;
		_effectMoveDown = NULL;
	}
}

void SelectWorldSence::_Load()
{
	_mario = new Mario(50, 50);

	_effectMoveDown = NULL;
	_isExitting = false;

	_MapLoader = new MapLoader();
	_MapLoader->LoadMapFormFile(0, true, true, true, true);
	
	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);

	_QuadTree = new QuadTree(mapRECT);
	_BackgroundMng = new BackgroundManager();
	int tempNoNeed = 0;
	_MapLoader->TranslateMap(_QuadTree, _BackgroundMng, _mario, tempNoNeed);
	_BackgroundMng->Translate();
	_Camera = new Camera(CRECT(GL_WndSize));

	_mario->_x = 100;
	_mario->_y = 100;
}

// nhan 1 lan
void SelectWorldSence::_OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_ESCAPE:
		{
			_state = TransOff;
			MenuSence* mn = new MenuSence(_game, 100);
			_game->AddSence(mn);

			/*SoundManager::GetInst()->StopBgSound(SOUND_B_MENU);
			SoundManager::GetInst()->StopBgSound(SOUND_B_GAME1);
			SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU, true, true);*/
		}
		break;

	case DIK_SPACE:
		_mario->Jump();
		break;

	case DIK_UP:
		_mario->Jump();
		break;

	case DIK_DOWN:
		{
			int col = (int)(_mario->_x / TILE);
			int row = (int)(_mario->_y / TILE);

			if(_mario->_State == stand || _mario->_State == Move)
			if((col == 9 || col == 10 || col == 13 || col == 14 || col == 17|| col == 18 )&&
				(row == 3 || row == 4 || row == 5))
			{
				_effectMoveDown = new MarioMoveDown(_mario->_turnLeft, _mario->_curSprite, _mario->_x, _mario->_y);
				//e_boss_hurt
				SoundManager::GetInst()->PlayEffSound(SOUND_E_BOSS_BEFORE_DIE);//e_boss_before_die
			}
		}
		break;

	case DIK_Q:
		_mario->TransformMario(0,1);
		break;
	case DIK_W:
		_mario->TransformMario(1,2);
		break;
	case DIK_E:
		_mario->TransformMario(2,0);
		break;
	}
}

//nhan 1 lan
void SelectWorldSence::_OnKeyUp(int keyCode)
{
	
}

// nhan va giu
void SelectWorldSence::_ProcessInput()
{
	if (_game->IsKeyDown(DIK_RIGHT))
	{
		_mario->TurnRight();
	}	
	else if (_game->IsKeyDown(DIK_LEFT))
	{
		_mario->TurnLeft();
	}
	else if(_game->IsKeyDown(DIK_DOWN))
	{ 
		_mario->ShitDown();
	}
	else
	{
		_mario->Stand();
	}
}

void SelectWorldSence::_UpdateRender(int time)
{
#pragma region Begin Render
	//translate camera
	D3DXMATRIX mat;
	float x = _Camera->GetRect().Left;
	float y = _Camera->GetRect().Top;
	D3DXVECTOR2 trans(- x, - y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, 0.0f, &trans);
	GLSpriteHandler->SetTransform(&mat);
	GLSpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
#pragma endregion
	//------------------------------------------------------------------------
	_Camera->Update(_mario);

	RECT r = GL_WndSize;
	r.top = GL_Height - _alpha * GL_Height;

	ResourceMng::GetInst()->GetSurface("image/imgBgGame.png")->Render(NULL, &r);
	_BackgroundMng->UpdateRender(_Camera->GetCameraExpand(), time);

	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _mario, time);

	//effect
	if(_effectMoveDown != NULL)
	{
		_effectMoveDown->Update(time);
		_effectMoveDown->Render();

		//complete effect
		if(_effectMoveDown->IsVisiable == false && _isExitting == false)
		{
			_isExitting = true;

			//stop and play new sound
			SoundManager::GetInst()->StopBgSound(SOUND_B_MENU);
			SoundManager::GetInst()->PlayEffSound(SOUND_E_PIPE);

			//goto play game
			PlaySence* pl = new PlaySence(_game, 0);
			ZoomSence* zs = new ZoomSence(_game, 500, this, pl);
			_game->AddSence(zs);
		}
	}
	else
	{
		//_mario->Update(time);

		{//do not run out of the map
			//right
			if(_mario->GetRect().Right >= GL_MapW)
			{
				_mario->_x = GL_MapW - _mario->_curSprite->_texture->Width;
			}

			//left
			if(_mario->_x <= 0)
			{
				_mario->_x = 0;
			}
		}
		_mario->Render();
	}

	//text
	Writer::RenderFont2("world 1", 420, 150, 0.7);
	Writer::RenderFont2("world 2", 620, 150, 0.7);
	Writer::RenderFont2("world 3", 820, 150, 0.7);

	Writer::RenderFont2("cost 1 live", 29 * 50 + 10, 5 * 50, 0.7);
	Writer::RenderFont2("cost 2 lives", 33 * 50 + 10, 5 * 50, 0.7);

	Writer::RenderFont2("you can exchange some lives for one of goodie!!!", 23 * 50 + 25, 1 * 50, 0.7);
	Writer::RenderFont2("but be careful sometimes lives is more important than that stuff.", 22 * 50 - 20, 2 * 50, 0.7);

	//------------------------------------------------------------------------
#pragma region End Render
	//translate camera back
	D3DXMATRIX matDefaut;
	D3DXMatrixTransformation2D(&matDefaut, NULL, 0.0f, NULL, NULL, 0.0f, NULL); 
	GLSpriteHandler->SetTransform(&matDefaut);
	//
	
	//end Render
	GLSpriteHandler->End();
#pragma endregion
}

