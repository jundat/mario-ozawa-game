#pragma once

#include "Rect.h"

#define MIN_TILE_ID 101
#define MAX_TILE_ID 106

//Save an array of byte to check if have any obj in a position in map
//+ do not Render any thing
//+ all things in this will be Rendered by background manager
class TileMap
{
public:
	int _mapW; //chiều rộng của map theo ô (1 ô 50x50px)
	int _mapH;

	//array 2 dimention type char
	int **_board;
	static TileMap* _instance;
	static TileMap* GetInst();

	~TileMap(void);

private:
	TileMap(void);
};
