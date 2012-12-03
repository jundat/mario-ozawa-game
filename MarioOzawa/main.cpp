// File:		main.cpp
// Project:		MarioOzawa
// Create:		Pham Tan Long


#include <windows.h>
#include "MarioGame.h"
#include "Global.h"
#include "ResourceManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MarioGame game(hInstance,
		"Mario",
		GL_RESOLUTION_800_600_24,
		0,
		60);
	game.Init();
	game.Run();

	return 0;
}


