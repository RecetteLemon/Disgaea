#pragma once
#include "gameNode.h"
#include "tile.h"
class townScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
public:
	townScene();
	~townScene();
	HRESULT init();
	void release();
	void update();
	void render();
	void loadTile();
	void camControl();
};

