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
	ITEM,
	TREEMONSTER,
	BOSS,
	BOSSFIRE
};
enum EDirect
{
	Left,
	Right,
	Top,
	Bottom,
	None
};
enum State{
	reborn,
	stand,
	Move,
	alive,
	jumping,
	beforedead,
	beforedead2,
	dead,
	transform,
	attack,
	hasCoin,
	noCoin,
	hasItem,
	moveDown,
	moveUp,
	breaking,
	hurt
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

