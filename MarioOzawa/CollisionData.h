#pragma once
//#include "MyObject.h"
enum EObject
{
	MARIO, // = 0
	BRICK,
	BRICKQUESTION,
	BRICKITEM,
	BRICKBREAK,
	FUNGI,
	TURTLE,
	COIN,
	PIPE,
	ITEM
};
enum EDirect
{
	Left,
	Right,
	Top,
	Bottom,
	None
};
class CollisionData
{
public:
	EObject _ID;
	float _deltaX,_deltaY;
	EDirect _dirCollision;
	float _delta;
	int _indexObject;

	CollisionData(EObject ID,EDirect dirCollision,float deltaX,float deltaY,float delta,int indexObject);
	~CollisionData(void);
};

