
#pragma once

#include "Rect.h"
#include "MyObject.h"

#define DELTA_CAMERA_X		10
#define DELTA_CAMERA_Y		100
#define EXPAND_CAMERA		100

#include <d3dx9.h>

class Camera
{
protected:
public:
	CRECT _rectCamera;		//bound

	float _vx;				//velocity 
	float _vy;

	Camera(CRECT rect);
	~Camera(void);

	void Update(MyObject* player);
	
	CRECT GetRect()
	{
		return _rectCamera;
	}

	CRECT GetCameraExpand();
};

