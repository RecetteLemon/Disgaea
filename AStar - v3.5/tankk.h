#pragma once
#include "gameNode.h"
#include "aStar.h"

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
	TANKDIRECTION _dir;
	image* _img;

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

	void setPosition(int x, int y);
	void setDirection(TANKDIRECTION td) { _dir = td; }
	void setCenter(POINT center) { _x = center.x, _y = center.y; }

	TANKDIRECTION getDirection() { return _dir; }
	int getX() { return _x; }
	int getY() { return _y; }

	tankk();
	~tankk();
};

