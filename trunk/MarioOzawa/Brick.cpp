
#include "Brick.h"
#include "ResourceManager.h"

brick::brick(float x, float y)	: MyObject(x, y)
{
	_curSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/brick.png"), 0);
	_ID = EObject::BRICK;
}

brick::~brick(void)
{
	delete _curSprite;
}

void brick::Update(int time)
{
	_curSprite->Update(time);
}

void brick::Render()
{
	_curSprite->Render((int)_x, (int)_y);
}

