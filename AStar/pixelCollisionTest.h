#pragma once
#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
private:
	image* _hill;
	image* _ball;

	RECT _rc;
	float _x, _y;

	//Y Axis ≈ΩªÁ √‡
	int _probeY;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollisionTest();
	~pixelCollisionTest();
};

