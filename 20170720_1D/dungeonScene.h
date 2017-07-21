#pragma once
#include "gameNode.h"
#include "tile.h"
class dungeonScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
public:
	dungeonScene();
	~dungeonScene();
	HRESULT init();
	void release();
	void update();
	void render();

	void loadFile();
	void drawTile();
	void camControl();

	void coordinateUpdate();
};

