#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"

class townScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	characterManager* _cm;
	
	
public:
	townScene();
	~townScene();
	HRESULT init();
	void release();
	void update();
	void render();
	void loadTile();
	void drawTile();
	void camControl();
};

