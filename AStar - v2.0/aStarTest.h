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
	//��ü Ÿ���� ����
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	vector<tile*> _roadList;
	vector<tile*> _moveList;


	tile* _startTile;		//����Ÿ�� Cost From Start
	tile* _endTile;			//�� Ÿ��	Cost To Goal
	tile* _currentTile;		//���� ��� (Ÿ��)
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

