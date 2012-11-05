#pragma once

#include "Rect.h"
#include "Sprite.h"

//Quản lý các đối tượng
// + Ko di chuyển
// + Ko xét va chạm
// + Có animation
class BackgroundManager
{
public:
	int _mapW;
	int _mapH;

	// mảng 2 chiều lưu id của các obj là background
	// chỉ dùng cho việc vẽ
	char **_board;
	//board[i][j]   ^
	// i: 0-> mapH  |
	// j: 0-> mapW --->

	Sprite*** _boardSprite;

	//translate backgroundObj
	void Translate();
	void UpdateRender(CRECT camera, int time);
	~BackgroundManager(void);

	BackgroundManager(void);
};

