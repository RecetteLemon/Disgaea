#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"
#include "animation.h"
#include "menuUI.h"

class townScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	menuUI* _mUI;
	characterManager* _cm;
	int _tileNum;
	int _tileIndex;
	image* _npc;
	animation* _npcFrame;
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

