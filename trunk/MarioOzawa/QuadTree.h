#pragma once

#include "QuadTreeNode.h"
#include "MyObject.h"
#include "Mario.h"

//size expand camera to update and check collision
#define COLLIDE_EXPAND 5
#define MIN_OBJ_ID 151
#define MAX_OBJ_ID 159

class QuadTree
{
public:
	static QuadTreeNode* _rootNode;
	static CRECT _bound;

	QuadTree(CRECT bound);
	~QuadTree(void);
	static void Insert (MyObject* obj);

	//update all obj in quad tree
	void UpdateRender(CRECT camera, Mario* mario, int time);
};

