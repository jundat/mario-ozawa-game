#include "TileMap.h"

TileMap* TileMap::_instance = NULL;

TileMap::TileMap(void)
{
}

TileMap::~TileMap(void)
{
}

TileMap* TileMap::GetInst()
{
	if(_instance == NULL)
	{
		_instance = new TileMap();
	}

	return _instance;
}
