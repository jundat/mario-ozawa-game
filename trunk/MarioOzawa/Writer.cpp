#include "Writer.h"

void Writer::Render(char* text, int x, int y)
{
	static Sprite* _sprText;
	_sprText = new Sprite(ResourceMng::GetInst()->GetTexture("image/imgChar.png"), 0);

	int CHAR_W = _sprText->_texture->Width - 18;
	int CHAR_H = _sprText->_texture->Height;
	int len = strlen(text);
	int index = 0;
	//
	for(int i = 0; i < len; ++i)
	{
		index = text[i] - ' ';
		_sprText->SelectIndex(index);
		_sprText->Render(x + i * CHAR_W, y);
	}
}