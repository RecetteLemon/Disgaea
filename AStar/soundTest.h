#pragma once
#include "gameNode.h"

class soundTest : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();


	soundTest();
	~soundTest();
};

