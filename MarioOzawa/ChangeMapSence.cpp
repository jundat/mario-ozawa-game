#include "ChangeMapSence.h"
#include "MenuSence.h"
#include "SoundManager.h"

ChangeMapSence::ChangeMapSence(Game* game, bool* isVisible, int curlevel, int timeAni)
	:GameSence(game, timeAni)
{
	this->IsVisiable = isVisible;
	*this->IsVisiable = false;
	CurrentLevel = curlevel;

	StationX[0] = 3;
	StationX[1] = 183;
	StationX[2] = 183;
	StationX[3] = 403;
	StationX[4] = 403;
	StationX[5] = 703;

	StationY[0] = 225;
	StationY[1] = 225;
	StationY[2] = 405;
	StationY[3] = 405;
	StationY[4] = 225;
	StationY[5] = 225;
}

ChangeMapSence::~ChangeMapSence(void)
{
}

void ChangeMapSence::_Load()
{
	mario = new Sprite(ResourceMng::GetInst()->GetTexture("image/MarioLarger.png"), 100);
	mario->_start = 0;
	mario->_end = 2;
}

// nhan 1 lan
void ChangeMapSence::_OnKeyDown(int keyCode)
{
	switch(keyCode){
	case DIK_RETURN:
		break;

	case DIK_UP:
		{
			SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			_state = TransOff;
			*this->IsVisiable = true;
		}
		break;

	case DIK_SPACE:
		{
			SoundManager::GetInst()->PlayEffSound(SOUND_E_SLIDE);
			_state = TransOff;
			*this->IsVisiable = true;
		}
		break;

	case DIK_DOWN:
		break;
	}
}

void ChangeMapSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void ChangeMapSence::_ProcessInput()
{
}

void ChangeMapSence::_UpdateRender(int time)
{
	static int count = 0;
	count++;

	//render
	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * _alpha), 255, 255, 255);
	D3DCOLOR finalColor = color;

	GLDevice->ColorFill(GLBackBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	ResourceMng::GetInst()->GetSurface("image/change_map.png")->Render(0, 0);
	
	//fire to start
	if(count >= 0 && count < 10)
	{
		ResourceMng::GetInst()->GetTexture("image/fire_to_start.png")->Render(228, 547);
	}
	else if(count >= 20)
	{
		count = 0;
	}

	//line
	int i = 0;
	for (i = 1; i < CurrentLevel; ++i)
	{
		if(i >= MAX_LEVEL)
			break;

		this->DrawLines(StationX[i-1], StationY[i-1], StationX[i], StationY[i]);
	}

	//mario
	float scale = 0.5f;
	mario->Update(time);
	mario->RenderTransform(StationX[i-1] - scale*mario->_texture->Width + 10, 
		StationY[i-1] - scale*mario->_texture->Height, 
		D3DXVECTOR2(scale, scale), 
		0.0f);

	GLSpriteHandler->End();
}

void ChangeMapSence::DrawLines(int x, int y, int nx, int ny)
{
	float d = sqrt((double)((nx-x)*(nx-x) + (ny-y)*(ny-y)));
	float vx = (nx-x) / d;
	float vy = (ny-y) / d;

	float xx = x;
	float yy = y;
	float DELTA = 20;

	while((xx-nx)*(x-nx) >= 0 && (yy-ny)*(y-ny) >= 0)
	{
		ResourceMng::GetInst()->GetTexture("image/ball.png")->Render(xx, yy);
		
		xx += DELTA * vx;
		yy += DELTA * vy;
	}
}

