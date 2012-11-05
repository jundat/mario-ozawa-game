#pragma once

#ifndef __RM_H__
#define __RM_H__

#include "Texture.h"
#include "Surface.h"

#include "Sprite.h"
#include <vector>
using namespace std;


class ResourceMng
{
private:
	//load all resource
	ResourceMng();

	//unique instance
	static ResourceMng* _instance;

	//-------------------- RESOURCE ----------------------
	//List of surface
	vector<SURFACE*> _listSurface;

	//List of texture
	vector<TEXTURE*> _listTexture;

public:
	//release all resource
	~ResourceMng(void);

	void Release();

	//get the unique instance
	static ResourceMng* GetInst();

	//get surface, if don't have, it will be loaded
	SURFACE* GetSurface(char* fileName);

	//get texture, if don't have, it will be loaded
	TEXTURE* GetTexture(char* fileName);
};



#endif