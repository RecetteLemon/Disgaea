#pragma once
#include "gameNode.h"
#include "aStarTest.h"
#include "tankk.h"

class aStarScene : public gameNode
{
private:
	aStarTest* _ast;
	tankk* _tank;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	aStarScene();
	~aStarScene();
};

