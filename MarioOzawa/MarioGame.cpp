#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "Surface.h"
#include "ResourceManager.h"
#include "MenuSence.h"
#include "PlaySence.h"
#include "IntroSence.h"
#include "SoundManager.h"

MarioGame::MarioGame(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate):
	Game(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	//TODO: Init game
}

MarioGame::~MarioGame()
{
	//TODO: Release game
	if(_listSence.empty())
		_listSence.clear();
}

void MarioGame::LoadResources()
{
	SoundManager::GetInst();

	IntroSence* mn = new IntroSence(this, 2000);
	this->AddSence(mn);
}

void MarioGame::RenderFrame(int t)
{
	//TODO: UPDATE-------------------------------------------------------
	//GameObject->Update(t);
}

void MarioGame::ProcessInput(int t)
{
	//State
	//Nhan phim va giu
	
}

void MarioGame::OnKeyDown(int KeyCode)
{
	//Buffer
	//Nhấn 1 lần
	
}

void MarioGame::OnKeyUp(int KeyCode)
{
	//Buffer
	//Nhấn 1 lần
}