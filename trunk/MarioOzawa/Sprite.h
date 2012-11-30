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
	void Render(int x, int y, float depth = 0.5f);
	
	//Render with scale (-1, 1)
	void RenderScaleX(int x, int y, float depth = 0.5f);

	// tieu nun
	//render with scale (1, -1)
	void RenderScaleY(int x, int y, float depth = 0.5f);

	// tieu nun
	//Render Rect of texture at (x,y)
	void RenderRect(int x, int y, RECT Rect, float depth = 0.5f);

	//Render with detail
	void RenderTransform(int x, int y, D3DXVECTOR2 scale, float degRotate, float depth = 0.5f);
	~Sprite();
};



#endif