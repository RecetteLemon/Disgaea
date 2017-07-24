#pragma once
#include "gameNode.h"
#include "tile.h"
#include "characterManager.h"


class dungeonScene : public gameNode
{
private:
	tagIso _tile[TILEX * TILEY];
	characterManager* _cm;
	int _tileIndex;

	image* _potal[2]; // ������ ������

	float _alpha;

	bool _alphaChange;

	//���̽�Ÿ��
	int _tileNum;
	bool _isMoveStart;
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
	void aStarMove();

	void coordinateUpdate();
};

