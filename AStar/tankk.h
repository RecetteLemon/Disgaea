#pragma once
#include "gameNode.h"
#include "tile.h"

class aStarTest;

enum TANKDIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};

class tankk : public gameNode
{
private:
	RECT _rc;
	float _x, _y;
	aStarTest* _aStar;
	TANKDIRECTION _dir;
	image* _img;
	tile* _curTile;

	int _count;
	int _indexX, _indexY;
	int _frame;
	bool _isStart;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void key();
	void move();
	void imgFrame();

	POINT getCenter() { return PointMake(_x, _y); }
	RECT getRc() { return _rc; }

	void setAstarMemoryAddressLink(aStarTest* as) { _aStar = as; }
	void setDirection(TANKDIRECTION td) { _dir = td; }
	void setCenter(POINT center) { _x = center.x, _y = center.y; }

	tankk();
	~tankk();
};

