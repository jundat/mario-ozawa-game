#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "Texture.h"

class Sprite {
public: 
	TEXTURE* _texture;

	int _start;
	int _end;
	int _index;			// Current sprite index
	int _timeAni;
	int _timeLocal;

	Sprite::Sprite(){}
	Sprite::Sprite(TEXTURE* texture, int timeAnimation);
	Sprite::Sprite(TEXTURE* texture, int start, int end, int timeAnimation);

	void Next();
	void Reset();
	void SelectIndex(int index);

	//update animation
	void Update(int time);

	// Render current sprite at location (X,Y) at the target surface
	void Render(int x, int y);
	
	//Render with scale (-1, 1)
	void RenderScale(int x, int y);

	// tieu nun
	//render with scale (1, -1)
	void RenderScaleY(int x, int y);

	// tieu nun
	//Render Rect of texture at (x,y)
	void RenderRect(int X, int Y,RECT Rect);

	//Render with detail
	void RenderTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth);
	~Sprite();
};



#endif