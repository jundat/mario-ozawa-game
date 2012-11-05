#pragma once

#include "MyObject.h"
#include <vector>
using namespace std;

#define MIN_NODE_SIZE	100 //px

class QuadTreeNode
{
protected:
	vector<MyObject*>*	_content;
	QuadTreeNode*		_listChild; //4
	
	void CreateSubNodes ();
	
public:
	CRECT _bound;
	QuadTreeNode();
	~QuadTreeNode(void);

	void Insert (MyObject* obj);

	//get and remove all obj and sub
	vector<MyObject*>* QueryObj (CRECT area);

	//get, NOT remove
	vector<MyObject*>* GetObj (CRECT area);
};

