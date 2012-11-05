

#ifndef __GAMESENCE_H__
#define __GAMESENCE_H__

#include "Game.h"
#include "ISence.h"
#include "ResourceManager.h"

enum SenceState{
	TransOn = 0,
	On = 1,
	TransOff = 2,
	Off = 3,
};

class GameSence : public ISence
{
public:
	Game*			_game;
	SenceState		_state;
	float			_alpha;
	float			_timeAni;

	GameSence(Game* game, int timeAni);
	virtual ~GameSence(void);

	//được bên ngoài gọi
	void UpdateRender(int t);
	void ProcessInput();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void Load();
	bool IsDead();

protected:
	//sẽ được thừa kế ở các lớp con
	virtual void _UpdateRender(int i);
	virtual void _ProcessInput();
	virtual void _OnKeyDown(int keyCode);
	virtual void _OnKeyUp(int keyCode);
	virtual void _Load();
	//
};


#endif __GAMESENCE_H__