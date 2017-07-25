#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"


class dungeonScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	dungeonManager* _dm;
	int _tileIndex[5];

	//에이스타용
	int _tileNum;
	bool _isMoveStart;
	bool _findPlayer;
	int _selectPlNum;

	RECT _rcEdge;
	int _edgeNum;
	bool _edgeMouseMove;
	int _edgeMouseY;
	image* _edge;
	image* _edgeMouse;

	image* _potal[2];
	
	float _alpha;

	bool _alphaChange;

	WCHAR str[128];
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
	void aStarMove(int plNum);

	void coordinateUpdate();
	void characterTileUpdate();
};

