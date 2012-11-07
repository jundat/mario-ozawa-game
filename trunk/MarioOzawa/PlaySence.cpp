#include "PlaySence.h"
#include "MenuSence.h"
#include "MapLoader.h"
#include "Writer.h"
#include "SoundManager.h"

PlaySence::PlaySence(Game* game, int timeAni)
	: GameSence(game, timeAni)
{
	SoundManager::GetInst()->PlayBgSound(SOUND_B_GAME1);
}

PlaySence::~PlaySence(void)
{
	if(_QuadTree != NULL)
		delete _QuadTree;

	if(_MapLoader != NULL)
		delete _MapLoader;
	
	if(_Camera != NULL)
		delete _Camera;

	if(_mario != NULL)
		delete _mario;

	if(_BackgroundMng != NULL)
		delete _BackgroundMng;
}

void PlaySence::_Load()
{
	_mario = new Mario(50, 50);

	_MapLoader = new MapLoader();
	_MapLoader->LoadMapFormFile("map/map.png");
	
	CRECT mapRECT = CRECT(0, 0, GL_MapW, GL_MapH);

	_QuadTree = new QuadTree(mapRECT);
	_BackgroundMng = new BackgroundManager();
	
	_MapLoader->TranslateMap(_QuadTree, _BackgroundMng, _mario);
	_BackgroundMng->Translate();
	
	_Camera = new Camera(CRECT(GL_WndSize));
}

// nhan 1 lan
void PlaySence::_OnKeyDown(int keyCode){
	switch(keyCode){
	case DIK_ESCAPE:
		{
			_state = TransOff;
			MenuSence* mn = new MenuSence(_game, 100);
			_game->AddSence(mn);

			SoundManager::GetInst()->StopBgSound(SOUND_B_GAME1);
			SoundManager::GetInst()->PlayBgSound(SOUND_B_MENU, true, true);
			//PostQuitMessage(0);
		}
		break;

	case DIK_SPACE:
		_mario->Jump();
		break;

	case DIK_UP:
		_mario->Jump();
		break;
	case DIK_Q:
		_mario->TransformMario(1,0);
		break;
	case DIK_W:
		_mario->TransformMario(1,2);
		break;
	case DIK_E:
		_mario->TransformMario(2,1);
		break;
	case DIK_Z:
		_mario->Fire();
		break;
	}
}

//nhan 1 lan
void PlaySence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void PlaySence::_ProcessInput()
{
	if (_game->IsKeyDown(DIK_RIGHT))
	{
		_mario->TurnRight();
	}	
	else if (_game->IsKeyDown(DIK_LEFT))
	{
		_mario->TurnLeft();
	}
	else 
	{ 
		_mario->Stand();
	}
}

void PlaySence::_UpdateRender(int time)
{
#pragma region Begin Render
	D3DXMATRIX mat;
	float x = _Camera->GetRect().Left;
	float y = _Camera->GetRect().Top;
	D3DXVECTOR2 trans(- x, - y);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, NULL, 0.0f, &trans);
	GLSpriteHandler->SetTransform(&mat);
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
#pragma endregion
	//------------------------------------------------------------------------
	_Camera->Update(_mario);

	RECT r = GL_WndSize;
	r.top = GL_Height - _alpha * GL_Height;

	ResourceMng::GetInst()->GetSurface("image/imgBgGame.png")->Draw(NULL, &r);
	_BackgroundMng->UpdateRender(_Camera->GetCameraExpand(), time);
	
	/* Fix Lan 1
	Ly do : sai thu tu vong lap logic
	_mario->Update(time);
	_mario->Render();

	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _mario, time);
	*/

	// fix thanh
	// =>
	_mario->Update(time);

	_QuadTree->UpdateRender(_Camera->GetCameraExpand(), _mario, time);
	_mario->Render();

	//------------------------------------------------------------------------
#pragma region End Render
	GLSpriteHandler->End();
	D3DXMATRIX matDefaut;
	D3DXMatrixTransformation2D(&matDefaut, NULL, 0.0f, NULL, NULL, 0.0f, NULL); 
	GLSpriteHandler->SetTransform(&matDefaut);
#pragma endregion
}



