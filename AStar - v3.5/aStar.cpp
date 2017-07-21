#include "stdafx.h"
#include "aStar.h"
#include "tankk.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{
	_currentMap = new tagIso[TILEX * TILEY];
	_startTile = new aStarTile;
	_endTile = new aStarTile;
	_currentTile = new aStarTile;

	return S_OK;
}

void aStar::loadCurrentMap(void* tiles)
{
	_currentMap = (tagIso*)tiles;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		aStarTile* node = new aStarTile;

		ZeroMemory(node, sizeof(aStarTile));
		node->setIso(_currentMap[i]);
		_vTotalList.push_back(node);
	}

	_endTile = new aStarTile;
	_endTile->setIso(_vTotalList[18]->getIso());
}

vector<aStarTile*> aStar::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIso().indexX - 1;			// 검사 시작할 좌표 X
	int startY = currentTile->getIso().indexY - 1;			// 검사 시작할 좌표 Y
	int startZ = currentTile->getIso().z / TILESIZEZ - 1;	// 검사 시작할 좌표 Z

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
		node->setIso(_currentMap[(startZ * TILEY * TILEX) + (startY * TILEX) + startX + x + (y * TILEX) + (z * TILEY * TILEX)]);

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

void aStar::pathFinder(aStarTile* currentTile)
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

	pathFinder(_startTile);
}

void aStar::release()
{

}


void aStar::update() 
{
	setStartTile(_tank->getX(), _tank->getY());
//	POINT mouse;
//	mouse.x = _ptMouse.x + CAME
//	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
//	{
//		for (int i = 0; i < _vTotalList.size(); i++)
//		{
//			HRGN hrgn = CreatePolygonRgn(_vTotalList[i]->getIso().line, 4, WINDING);
//			if(PtInRegion(hrgn, ))
//		}
//
//	}
}

void aStar::render() 
{	
	if (_endTile)
	{
		WCHAR str[128];
		swprintf_s(str, L"%d %d", _endTile->getIso().indexX, _endTile->getIso().indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, WINSIZEX - 100, 50, WINSIZEX, 60);
	}
}

void aStar::setStartTile(int x, int y)
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		HRGN hrgn = CreatePolygonRgn(_vTotalList[i]->getIso().line, 4, WINDING);
		if (PtInRegion(hrgn, x, y)) _startTile = _vTotalList[i];
		DeleteObject(hrgn);
	}
}