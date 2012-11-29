#include "QuadTree.h"
#include "Global.h"

QuadTree::QuadTree(CRECT bound)
{
	_bound = bound;
	_rootNode = new QuadTreeNode();
	_rootNode->_bound = bound;
}

QuadTree::~QuadTree(void)
{
	if(_rootNode != NULL)
		delete _rootNode;
}

void QuadTree::Insert (MyObject* obj)
{
	_rootNode->Insert(obj);
}

void QuadTree::UpdateRender(CRECT camera, Mario* mario, int time)
{
#pragma region create rect camera
	CRECT cameraCollision = camera;
	if(cameraCollision.Left >= COLLIDE_EXPAND)
		cameraCollision.Left -= COLLIDE_EXPAND;
	else
		cameraCollision.Left = 0;

	if(cameraCollision.Right <= GL_MapW - COLLIDE_EXPAND)
		cameraCollision.Right += COLLIDE_EXPAND;
	else
		cameraCollision.Right = GL_MapW;

	if(cameraCollision.Top >= COLLIDE_EXPAND)
		cameraCollision.Top -= COLLIDE_EXPAND;
	else
		cameraCollision.Top = 0;

	if(cameraCollision.Bottom <= GL_MapH - COLLIDE_EXPAND)
		cameraCollision.Bottom += COLLIDE_EXPAND;
	else
		cameraCollision.Bottom = GL_MapH;
#pragma endregion

	vector<MyObject*>* listCollision = this->_rootNode->GetObj(cameraCollision);
	vector<MyObject*>* listUpdate = this->_rootNode->QueryObj(camera);
	
	for (std::vector<MyObject*>::iterator i = listUpdate->begin(); 
		i != listUpdate->end(); ++i)
	{
		//update
		(*i)->Update(time);

		//check collision
		if((*i)->CanCollide())
		{
			//check collision with mario
			(*i)->CheckCollision(mario);
			mario->CheckCollision((*i));

			for (std::vector<MyObject*>::iterator j = listCollision->begin(); 
				j != listCollision->end(); ++j)
			{
				if(*i != *j)
				{
					(*i)->CheckCollision(*j);
				}
			}
		}

		// fix lan 1
		// render
		(*i)->Render();
		
		// insert again
		if((*i)->IsAlive())
		{
			this->Insert(*i);
		}
	}	
}
