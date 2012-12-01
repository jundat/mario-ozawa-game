
#include "Pipe.h"
#include "ResourceManager.h"

pipe::pipe(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/pipe.png"), 0);
	_ID = EObject::PIPE;
}


pipe::~pipe(void)
{
	delete _curSprite;
	_curSprite = NULL;
}

void pipe::Update(int time)
{
	_curSprite->Update(time);
}

void pipe::Render()
{
	_curSprite->Render((int)_x, (int)_y);
}

CRECT pipe::GetRect()
{
	return CRECT(_x, _y, _x + _curSprite->_texture->Width, _y + _curSprite->_texture->Height);
}

