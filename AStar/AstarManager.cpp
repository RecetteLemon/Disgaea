#include "stdafx.h"
#include "AstarManager.h"
#include "tile.h"


AstarManager::AstarManager()
{
}


AstarManager::~AstarManager()
{
}

HRESULT AstarManager::init()
{


	return S_OK;
}

void AstarManager::release()
{

}

void AstarManager::update()
{

}

void AstarManager::render()
{

}


void AstarManager::setTiles(int tileXNum, int tileYNum, const char* fileName)
{
	for (int i = 0; i < tileXNum; i++)
	{
		for (int j = 0; j < tileYNum; j++)
		{
			tile* node = new tile;
		}
	}
}

vector<tile*> AstarManager::addOpenList(tile* currentTile)
{

	return _vOpenList;
}

void AstarManager::pathFinder(tile* currentTile)
{

}
