#pragma once
#include "gameNode.h"
#include "inven.h"
#include "townInven.h"

class testScene : public gameNode
{
private:
	inven* _itemBag_battle;
	townInven* _townInven;

	bool _invenOn_battle;
	bool _invenOn_town;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	testScene();
	~testScene();
};

