#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "aStar.h"
#include "tankk.h"

class dungeonScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	aStar* _aStar;
	tankk* _tank;
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

