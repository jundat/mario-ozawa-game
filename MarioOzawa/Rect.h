#pragma once

#include <d3d9.h>

class CRECT
{
public:
	float Left, Top, Right, Bottom;
	
	CRECT(void);
	CRECT(RECT rect);
	CRECT(float _left, float _top, float _right, float _bottom);
	~CRECT(void);
	RECT ToRECT();

	//collision
	bool IsCollision (CRECT _Rect);

	void SetX(float x);
	void SetY(float y);
	void Move(float x, float y);
};

