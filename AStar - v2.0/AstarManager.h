#pragma once
#include "singletonBase.h"

class tile;

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILEX 20
#define TILEY 20

class AstarManager : public singletonBase<AstarManager>
{
private:
	//전체 타일을 담을
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 길을 담을
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 빠른 길을 담을
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//시작타일 Cost From Start
	tile* _endTile;			//끝 타일	Cost To Goal
	tile* _currentTile;		//현재 노드 (타일)
	tile* _roadTile;

	int _count;
	bool _start;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setTiles(int tileXNum, int tileYNum, const char* fileName);

	vector<tile*> addOpenList(tile* currentTile);
	void pathFinder(tile* currentTile);

	AstarManager();
	~AstarManager();
};

