#pragma once
#include "gameNode.h"

class characterSelectScene : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	characterSelectScene();
	~characterSelectScene();
};

