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
	//��ü Ÿ���� ����
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//����Ÿ�� Cost From Start
	tile* _endTile;			//�� Ÿ��	Cost To Goal
	tile* _currentTile;		//���� ��� (Ÿ��)
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

