#pragma once
#include "gameNode.h"

class collisionTest : public gameNode
{
private:
	MYRECT _rect;
	MYRECT _rectMove;

	MYCIRCLE _cir;
	MYCIRCLE _cirMove;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	collisionTest();
	~collisionTest();
};

