#include "OptionSence.h"
#include "MenuSence.h"
#include "SoundGame.h"
#include "CreditSence.h"


int OptionSence::_curSelect = 0;

OptionSence::OptionSence(Game* game, int timeAni)
	:GameSence(game, timeAni)
{
	//_curSelect = 0;
}


OptionSence::~OptionSence(void)
{
}


void OptionSence::_Load()
{
	_sprMarioHead = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgMarioHead.png"), 1500);
}

// nhan 1 lan
void OptionSence::_OnKeyDown(int keyCode){
	switch(keyCode){
		case DIK_RETURN:
			{
				//GL_HasBgSound
				//GL_HasEffSound
				//Credit
				//Exit
				switch(_curSelect)
				{
				case 0:
					GL_HasBGSound = !GL_HasBGSound;
					if(GL_HasBGSound == false)
					{
						SoundGame::GetInst()->StopAllBgSound();
					}else
					{
						SoundGame::GetInst()->PlayBgSound(SOUND_B_MENU);
					}
					SoundGame::GetInst()->PlayEffSound(SOUND_E_SLIDE);
					break;

				case 1:
					GL_HasEffectSound = !GL_HasEffectSound;
					if(GL_HasEffectSound == false)
					{
						SoundGame::GetInst()->StopAllEffSound();
					}
					SoundGame::GetInst()->PlayEffSound(SOUND_E_SLIDE);
					break;

				case 2://credit
					{
						SoundGame::GetInst()->PlayEffSound(SOUND_E_SLIDE);
						_state = SenceState::TransOff;
						CreditSence* crd = new CreditSence(_game, 100);
						_game->AddSence(crd);
					}
					break;

				case 3:
					{
						SoundGame::GetInst()->PlayEffSound(SOUND_E_SLIDE);

						SoundGame::GetInst()->PlayBgSound(SOUND_B_MENU);

						_state = TransOff;
						MenuSence* mn = new MenuSence(_game, 100);
						_game->AddSence(mn);
					}					
					break;

				}
			}
			break;

		case DIK_UP:
			if(_curSelect > 0)
			{
				SoundGame::GetInst()->PlayEffSound(SOUND_E_CLICK);
				_curSelect--;
			}
			break;

		case DIK_DOWN:
			if(_curSelect < COUNT_OPTION - 1)
			{
				SoundGame::GetInst()->PlayEffSound(SOUND_E_CLICK);
				_curSelect++;
			}
			break;
	}
}

void OptionSence::_OnKeyUp(int keyCode)
{
}

// nhan va giu
void OptionSence::_ProcessInput()
{
}

void OptionSence::_UpdateRender(int t)
{
	//--------------------------------------------UPDATE------------------------------
	if(_sprMarioHead->_index == 1 && _sprMarioHead->_timeLocal >= _sprMarioHead->_timeAni/7)
		_sprMarioHead->SelectIndex(0);
	_sprMarioHead->Update(t);


	//--------------------------------------------RENDER------------------------------
	GLSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//
	RECT destRect = GL_WndSize;
	destRect.top = GL_Height - _alpha * GL_Height;

	ResourceMng::GetInst()->GetSurface("image/imgBgOption.png")->Draw(&destRect, &destRect);

	//mario head
	_sprMarioHead->Render(432, 193 + _curSelect * 65);

	//
	if(GL_HasBGSound)
	{
		ResourceMng::GetInst()->GetTexture("image/imgYes.png")->Draw(530, 200);
	}
	else
	{
		ResourceMng::GetInst()->GetTexture("image/imgNo.png")->Draw(530, 200);
	}

	if(GL_HasEffectSound)
	{
		ResourceMng::GetInst()->GetTexture("image/imgYes.png")->Draw(530, 265);
	}
	else
	{
		ResourceMng::GetInst()->GetTexture("image/imgNo.png")->Draw(530, 265);
	}

	//
	GLSpriteHandler->End();
}

