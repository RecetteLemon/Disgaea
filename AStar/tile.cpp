#include "stdafx.h"
#include "tile.h"
#include "aStarTest.h"


tile::tile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),
	_idX(0), _idY(0)
{
}


tile::~tile()
{

}

HRESULT tile::init(int idX, int idY)
{
	_center = PointMake(idX * TILEWIDTH + (TILEWIDTH / 2),
		idY * TILEHEIGHT + (TILEHEIGHT / 2));

	_idX = idX;
	_idY = idY;
	


	_rc = RectMakeCenter(_center.x, _center.y, TILEWIDTH, TILEHEIGHT);


	return S_OK;
}

void tile::release(void)
{

}

void tile::update(void)	
{

}

void tile::render(void)	
{
	IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _rc.left, _rc.top, _terrainFrameX, _terrainFrameY);
}
