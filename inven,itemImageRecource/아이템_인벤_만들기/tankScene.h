#pragma once
#include "gameNode.h"
#include "tankMap.h"
#include "tank.h"
#include "inven.h"

class tankScene : public gameNode
{
private:
	tankMap* _tankMap;
	tank* _tank;
	inven* _itemBag;
	bool _invenOn;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	tankScene();
	~tankScene();
};

