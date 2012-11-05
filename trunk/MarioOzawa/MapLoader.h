#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "QuadTree.h"
#include "BackgroundManager.h"
#include "TileMap.h"
#include "Mario.h"

//load map from a bitmap
//+ save it to an array
//+ translate it to obj (add to quadtree, backgroundManader), or tile map(to check collision)
class MapLoader
{
public:
	LPDIRECT3DTEXTURE9 _mapTexture;
	static int _mapW;	//number tile in width
	static int _mapH;	//number tile in heigh
	char **_board ;	//2dimention array to saved id of object in map

	MapLoader(void);
	~MapLoader(void);

	//load map from an bitmap, save id(int) to array **_terrain
	HRESULT LoadMapFormFile (LPCTSTR _file);

	//translate from _board to object, or save to BackgroundManager and TileMap
	void TranslateMap (QuadTree* quadtree, BackgroundManager* background, Mario* mario);
};

