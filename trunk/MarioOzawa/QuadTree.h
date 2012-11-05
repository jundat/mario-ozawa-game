#pragma once

#include "QuadTreeNode.h"
#include "MyObject.h"
#include "Mario.h"

//size expand camera to update and check collision
#define COLLIDE_EXPAND 5
#define MIN_OBJ_ID 151
#define MAX_OBJ_ID 158

class QuadTree
{
public:
	QuadTreeNode* _rootNode;
	CRECT _bound;

	QuadTree(CRECT bound);
	~QuadTree(void);
	void Insert (MyObject* obj);

	//update all obj in quad tree
	void UpdateRender(CRECT camera, Mario* mario, int time);

};

