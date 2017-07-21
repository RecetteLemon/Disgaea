#include "stdafx.h"
#include "aStarManager.h"


aStarManager::aStarManager()
{
}


aStarManager::~aStarManager()
{
}

HRESULT aStarManager::init()
{
	

	return S_OK;
}

void aStarManager::release()
{
	deleteAll();
}

void aStarManager::update()	
{

}

void aStarManager::render()	
{

}

void aStarManager::deleteAll()
{
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	_vRoadList.clear();
}


vector<aStarTile*> aStarManager::getTotalList()
{

	return _vTotalList;
}

vector<aStarTile*> aStarManager::addOpenList(aStarTile* currentTile)
{

	return _vOpenList;
}

vector<aStarTile*> aStarManager::pathFinder(aStarTile* currentTile)	
{

	return _vRoadList;
}

void aStarManager::setStartTile(int x, int y)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{

	}
}