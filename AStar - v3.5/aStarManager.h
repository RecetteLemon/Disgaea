#pragma once
#include "singletonBase.h"
#include "aStar.h"
#include <vector>
#include <map>

class aStarManager : public singletonBase<aStarManager>
{
private:
	tagIso* _currentMap;

	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	vector<aStarTile*> _vOpenList;

	vector<aStarTile*> _vCloseList;

	vector<aStarTile*> _vRoadList;


public:
	HRESULT init();
	void release();
	void update();
	void render();
	void deleteAll();

	void setStartTile(int x, int y);

	vector<aStarTile*> getTotalList();
	vector<aStarTile*> addOpenList(aStarTile* currentTile);
	vector<aStarTile*> pathFinder(aStarTile* currentTile);


	aStarManager();
	~aStarManager();
};

