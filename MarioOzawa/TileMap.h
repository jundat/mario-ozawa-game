#pragma once

#include "Rect.h"
#include "Global.h"

#define MIN_TILE_ID 101
#define MAX_TILE_ID 106

//Save an array of byte to check if have any obj in a position in map
//+ do not Render any thing
//+ all things in this will be Rendered by background manager
class TileMap
{
public:
	static int _mapW; //chiều rộng của map theo ô (1 ô 50x50px)
	static int _mapH;

	//array 2 dimention type char
	static int **_board;
	static TileMap* _instance;
	static TileMap* GetInst();

	//delete a tile in position (int posxPixel, int posyPixel)
	static void RemoveTileAt(int posxPixel, int posyPixel);

	~TileMap(void);

private:
	TileMap(void);
};
