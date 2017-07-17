#pragma once
#include "gameNode.h"
#include "tankMap.h"

enum TANKDIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;

	TANKDIRECTION _direction;

	image* _image;
	RECT _rc;

	float _x, _y;
	float _speed;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void tankMove();

	void setTankPosition();

	void setTankMapMemoryAddressLink(tankMap* tm) { _tankMap = tm; }



	tank();
	~tank();
};

