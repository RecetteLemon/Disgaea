#include "stdafx.h"
#include "aStarTest.h"
#include "tankk.h"

aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{
}

HRESULT aStarTest::init()
{
	_start = _count = 0;
	_tileNum = 0;

	return S_OK;
}

void aStarTest::setTiles()
{
	vector<string> vTerrainX = TXTDATA->txtLoad("terrainX.map");
	vector<string> vTerrainY = TXTDATA->txtLoad("terrainY.map");
	vector<string> vTerrainType = TXTDATA->txtLoad("terrainType.map");

	for (int i = 0;i < TILEY;i++)
	{
		for (int j = 0;j < TILEX;j++)
		{
			tile* node = new tile;
			node->init(j, i);
			node->setTerrainFrameX(atoi(vTerrainX[i].c_str()));
			node->setTerrainFrameY(atoi(vTerrainY[i].c_str()));
			node->setAttribute((TERRAIN)atoi(vTerrainType[i].c_str()));

			_vTotalList.push_back(node);
		}
	}
}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (i == 0 && j == 0) continue;
			if (i == 2 && j == 0) continue;
			if (i == 0 && j == 2) continue;
			if (i == 2 && j == 2) continue;
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			tile* node = _vTotalList[(startY * TILEX) + startX + j + (i * TILEX)];

			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == TR_START) continue;
			if (node->getAttribute() == TR_WALL) continue;

			node->setParentNode(_roadTile);

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin();_viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != TR_END) node->setTerrainFrameX(1);

			if (!addObj) continue;

			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void aStarTest::pathFinder(tile* currentTile)
{
	float tempTotalCost = 5000;
	tile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX())
			+ abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		_vOpenList[i]->setCostFromStart(10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//가장 비용이 작은 애를 색출
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				continue;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	//tempTile->setTerrainFrameX(2);

	//템프타일의 속성이 엔드 -> 도착했으면!
	if (tempTile->getAttribute() == TR_END)
	{
		//이때까지 지나온 타일을 색칠해라
		while (_roadTile->getParentNode() != NULL)
		{
			_roadTile = _roadTile->getParentNode();
			_tile.push_back(_roadTile);
			for (int i = 0; i < _tile.size(); ++i)
			{
				_tile[i]->setTerrainFrameX(0);
			}

			//_vCloseList.push_back(tempTile);
		}
		_start = true;
		return;
	}

	
	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_roadTile = tempTile;

	pathFinder(_roadTile);
}

void aStarTest::release()
{

}

void aStarTest::update()
{
	
		for (int i = 0;i < _vTotalList.size();i++)
		{
			if ((_tank->getCenter().x / TILEWIDTH) == _vTotalList[i]->getIdX() &&
				(_tank->getCenter().y / TILEHEIGHT) == _vTotalList[i]->getIdY())
			{
				_startTile = _vTotalList[i];
				_roadTile = _startTile;
				_startTile->setAttribute(TR_START);
			}
		}
	
	if (_start)
	{
		if (_tile.size() != NULL)
		{
			if (_tank->getCenter().y / TILEHEIGHT == _tile[_tileNum]->getIdY())
			{
				_tank->setDirection((((int)_tank->getCenter().x / TILEWIDTH > _tile[_tileNum]->getIdX()) ? DIR_LEFT : DIR_RIGHT));
			}
			else
			{
				_tank->setDirection((((int)_tank->getCenter().y / TILEHEIGHT > _tile[_tileNum]->getIdY()) ? DIR_UP : DIR_DOWN));
			}

			if (_tank->getCenter().y / TILEHEIGHT == _tile[_tileNum]->getIdY() && _tank->getCenter().x / TILEWIDTH == _tile[_tileNum]->getIdX())
				++_tileNum;

			if (_tileNum < _tile.size() - 1)
			{
				if (_tile[_tileNum]->getAttribute() != TR_WALL) _tank->move();
			}
			else 
			{
				_vTotalList.clear();
				_tile.clear();
				_vOpenList.clear();
				setTiles();
				_tileNum = 0;
				_start = false;
			}
		}
		else
		{
			_tileNum = 0;
			_start = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				_vTotalList[i]->setAttribute(TR_WALL);
				_vTotalList[i]->setTerrainFrameX(4);
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_vCloseList.clear();
		for (int i = 0; i < _vTotalList.size();i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				_endTile = _vTotalList[i];
				_endTile->setAttribute(TR_END);
			}
		}
		pathFinder(_roadTile);
	}

}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}

void aStarTest::load()
{

}