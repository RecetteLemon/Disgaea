#include "stdafx.h"
#include "collisionTest.h"


collisionTest::collisionTest()
{
}


collisionTest::~collisionTest()
{

}

HRESULT collisionTest::init()
{
	//_rect.left = 200;
	//_rect.top = 200;
	//_rect.right = 300;
	//_rect.bottom = 300;
	//
	//_rectMove.left = 400;
	//_rectMove.top = 400;
	//_rectMove.right = 450;
	//_rectMove.bottom = 450;

	_cir.x = WINSIZEX / 2;
	_cir.y = WINSIZEY / 2;
	_cir.r = 100;

	_cirMove.x = 50;
	_cirMove.y = 50;
	_cirMove.r = 50;


	return S_OK;
}

void collisionTest::release()
{

}

void collisionTest::update() 
{
	//_rectMove.setCenterPos(_ptMouse.x, _ptMouse.y);
	//
	//if (isCollisionReaction(_rect, _rectMove))
	//{
	//
	//}

	_cirMove.x = _ptMouse.x;
	_cirMove.y = _ptMouse.y;

	if (isCollisionReaction(_cir, _cirMove))
	{

	}
	else
	{

	}
}

void collisionTest::render() 
{
	//_rect.render(getMemDC());
	//_rectMove.render(getMemDC());

	_cir.render(getMemDC());
	_cirMove.render(getMemDC());
}
