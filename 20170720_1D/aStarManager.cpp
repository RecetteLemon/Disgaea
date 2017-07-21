#include "stdafx.h"
#include "aStarManager.h"


HRESULT aStarManager::init()
{
	_currentMap = new tagIso[TILEX * TILEY * TILEZ];

	return S_OK;
}

void aStarManager::loadCurrentMap(tagIso* tiles)
{
	_currentMap = tiles;
}

vector<aStarTile*> aStarManager::addOpenList(tagIso currentTile)
{
	int startX = currentTile.indexX - 1;			// 검사 시작할 좌표 X
	int startY = currentTile.indexY - 1;			// 검사 시작할 좌표 Y
//	int startZ = currentTile.z / TILESIZEZ - 1;	// 검사 시작할 좌표 Z

	// 2D 평면에서는 자신의 주변, 총 3 * 3 의 타일을 검사했다면
	// 아이소매트릭에서는 3D 큐브가 있다 치고 x, y 좌표뿐만이 아닌 z 좌표도 검사해야 하므로
	// 자신의 좌표의 주변인 높이도 포함하여 총 3 * 3 * 3 의 27타일을 검사하게 됩니다.
	for (int z = 0; z < 3; ++z) for (int y = 0; y < 3; ++y) for (int x = 0; x < 3; ++x)
	{
		// 오픈리스트에 담을거
		aStarTile* node = new aStarTile;

		//		if (!node->getIsOpen()) continue;
		//		if (node->getAttribute() == TR_START) continue;
		//		if (node->getAttribute() == TR_WALL) continue;

		//		node->setIso(_currentMap[startX + k][startY + j][startZ + i]);
		//		(startY * TILEX) + startX + j + (i * TILEX)
		//		node->setIso(_currentMap[(startZ * TILEY * TILEX) + (startY * TILEX) + startX + x + (y * TILEX) + (z * TILEY * TILEX)]);
		node->setIso(_currentMap[(startY * TILEX) + startX + x + (y * TILEX)]);

		// 추가할건지 안할건지 검사할 임시변수
		bool addObj = true;

		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == node)
			{
				addObj = false;
				break;
			}
		}

		if (!addObj) continue;

		_vOpenList.push_back(node);
	}

	return _vOpenList;
}

void aStarManager::pathFinder(tagIso currentTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX())
			+ abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		_vOpenList[i]->setCostFromStart(10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//가장 비용이 작은 애를 색출
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		//오픈리스트에 담긴 타일이 템프타일이면(가장 짧은 길이면)
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				//addObj 폴스
				addObj = false;
				continue;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	if (addOpenList(currentTile).size() == NULL)
	{
		_vOpenList.clear();
		_vCloseList.clear();
		return;
	}

	//템프타일의 속성이 엔드 -> 도착했으면!
	if (tempTile->getIso().ter == TER_WALL)
	{
		_vMoveList.insert(_vMoveList.begin(), tempTile->getIso());
		//이때까지 지나온 타일을 색칠해라
		while (_startTile->getParentNode() != NULL)
		{
			_vMoveList.insert(_vMoveList.begin(), _startTile->getIso());
			_startTile = _startTile->getParentNode();
		}
		return;
	}

	//가까운 타일 담는 벡터에 템프타일 푸시백
	_vCloseList.push_back(tempTile);

	//오픈리스트중에 가까운 타일이 있으면 삭제
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_startTile = tempTile;

	pathFinder(_startTile->getIso());
}

void aStarManager::render()
{
	WCHAR str[64];

	for (int i = 0; i < _vMoveList.size(); ++i)
	{
		wsprintf(str, L"%d %d", _vMoveList[i].indexX, _vMoveList[i].indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, WINSIZEX - 200, i * 50 + 50, WINSIZEX - 100, i * 50 + 100);
	}
}