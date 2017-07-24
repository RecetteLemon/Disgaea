#pragma once
#include "gameNode.h"
class menu : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	menu();
	~menu();
};

