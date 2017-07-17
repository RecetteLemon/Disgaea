#pragma once
#include "gameNode.h"
#include "shipManager.h"

class starcraftScene : public gameNode
{
private:
	shipManager* _sm;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	starcraftScene();
	~starcraftScene();
};

