#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class tankk;

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILEX 20
#define TILEY 20

class aStarTest : public gameNode
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

	vector<tile*> _roadList;
	vector<tile*> _moveList;


	tile* _startTile;		//시작타일 Cost From Start
	tile* _endTile;			//끝 타일	Cost To Goal
	tile* _currentTile;		//현재 노드 (타일)
	tile* _roadTile;

	tankk* _tank;

	int _count;
	bool _start;

	int _tileNum;

public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	
	void setTiles();
	vector<tile*> addOpenList(tile* currentTile);
	void pathFinder(tile* currentTile);
	void load();
	void addMoveList(tile* currentTile);
	
	void release();
	void update();
	void render();

	vector<tile*> getTotalTile() { return _vTotalList; }
	vector<tile*> getOpenList() { return _vOpenList; }
	void setTankAddressMemoryLink(tankk* tk) { _tank = tk; }
};

