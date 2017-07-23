#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"


class dungeonScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	characterManager* _cm;

	bool _findWay;
	int _tileNum;
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

