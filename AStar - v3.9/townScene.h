#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"
#include "animation.h"
class townScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	characterManager* _cm;
	image* _npc;
	animation* _npcFrame;
	int _tileIndex;
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
	void playerTileCol();
	void aStarMove();
};

