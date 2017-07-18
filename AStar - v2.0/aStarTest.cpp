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
	vector<string> vStr = TXTDATA->txtLoad("terrainType.map");
	vector<string> vStr2 = TXTDATA->txtLoad("terrainX.map");
	vector<string> vStr3 = TXTDATA->txtLoad("terrainY.map");

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			tile* node = new tile;
			node->init(j, i);
			node->setAttribute(TR_ROAD);
			node->setTerrainFrameX(atoi(vStr2[i].c_str()));
			node->setTerrainFrameY(atoi(vStr3[i].c_str()));

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

//			if (!_vTotalList[(startY * TILEX) + startX + j + (i * TILEX)]->getIsOpen()) continue;

			tile* node = _vTotalList[(startY * TILEX) + startX + j + (i * TILEX)];

			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == TR_START) continue;
			if (node->getAttribute() == TR_WALL) continue;

			node->setParentNode(_startTile);

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin();_viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//if (node->getAttribute() != TR_END) node->setTerrainFrameX(10);

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
		_vTotalList.clear();
		_vOpenList.clear();
		_vCloseList.clear();
		_roadList.clear();
		setTiles();
		return;
	}

	//템프타일의 속성이 엔드 -> 도착했으면!
	if (tempTile->getAttribute() == TR_END)
	{
		_roadList.insert(_roadList.begin(), tempTile);
		//이때까지 지나온 타일을 색칠해라
		while (_startTile->getParentNode() != NULL)
		{
			_roadList.insert(_roadList.begin(), _startTile);
			_startTile = _startTile->getParentNode();
		}
		_start = true;
		_moveList.clear();
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

void aStarTest::release()
{

}

void aStarTest::update()
{
	for (int i = 0; i < _roadList.size(); i++)
	{
		_roadList[i]->setTerrainFrameX(0);
	}
	for (int i = 0;i < _vTotalList.size();i++)
	{
		if ((_tank->getCenter().x / TILEWIDTH) == _vTotalList[i]->getIdX() &&
			(_tank->getCenter().y / TILEHEIGHT) == _vTotalList[i]->getIdY())
		{
			_startTile = _vTotalList[i];
			_startTile->setAttribute(TR_START);
		}
	}
	
	if (_start)
	{
		if (_roadList.size() != NULL)
		{
			// 타일이 왼쪽에 있을때
			if ((int)(_tank->getCenter().x / TILEWIDTH) > _roadList[_tileNum]->getIdX() &&
				(int)(_tank->getCenter().y / TILEHEIGHT) == _roadList[_tileNum]->getIdY())
			{
				_tank->setDirection(DIR_LEFT);
			}
			else if ((int)(_tank->getCenter().x / TILEWIDTH) < _roadList[_tileNum]->getIdX() &&
				(int)(_tank->getCenter().y / TILEHEIGHT) == _roadList[_tileNum]->getIdY())
			{
				_tank->setDirection(DIR_RIGHT);
			}
			else if ((int)(_tank->getCenter().x / TILEWIDTH) == _roadList[_tileNum]->getIdX() &&
				(int)(_tank->getCenter().y / TILEHEIGHT) > _roadList[_tileNum]->getIdY())
			{
				_tank->setDirection(DIR_UP);
			}
			else if ((int)(_tank->getCenter().x / TILEWIDTH) == _roadList[_tileNum]->getIdX() &&
				(int)(_tank->getCenter().y / TILEHEIGHT) < _roadList[_tileNum]->getIdY())
			{
				_tank->setDirection(DIR_DOWN);
			}

			switch (_tank->getDirection())
			{
			case DIR_LEFT:
				if (_tank->getCenter().x <= _roadList[_tileNum]->getCenter().x)
				{
					_tank->setCenter(_roadList[_tileNum]->getCenter());
					++_tileNum;
				}
				break;
			case DIR_RIGHT:
				if (_tank->getCenter().x >= _roadList[_tileNum]->getCenter().x)
				{
					_tank->setCenter(_roadList[_tileNum]->getCenter());
					++_tileNum;
				}
				break;
			case DIR_UP:
				if (_tank->getCenter().y <= _roadList[_tileNum]->getCenter().y)
				{
					_tank->setCenter(_roadList[_tileNum]->getCenter());
					++_tileNum;
				}
				break;
			case DIR_DOWN:
				if (_tank->getCenter().y >= _roadList[_tileNum]->getCenter().y)
				{
					_tank->setCenter(_roadList[_tileNum]->getCenter());
					++_tileNum;
				}
				break;
			}

			if (_tileNum < _roadList.size())
			{
				if (_startTile->getAttribute() != TR_WALL) _tank->move();
			}
			else 
			{
				_vTotalList.clear();
				_roadList.clear();
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
	else
	{
		addMoveList(_startTile);
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
		if (_roadList.size())
		{
			_vTotalList.clear();
			_vOpenList.clear();
			_vCloseList.clear();
			_roadList.clear();
			setTiles();
		}

		for (int i = 0; i < _moveList.size(); i++)
		{
			if (PtInRect(&_moveList[i]->getRect(), _ptMouse))
			{
				_endTile = _moveList[i];
				_endTile->setAttribute(TR_END);
				pathFinder(_startTile);
				break;
			}
		}
	}
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
	char str[128];
	sprintf(str, "%d %d", _startTile->getIdX(), _startTile->getIdY());
	TextOut(getMemDC(), 0, 0, str, strlen(str));
}

void aStarTest::load()
{

}

void aStarTest::addMoveList(tile* currentTile)
{
	int startX = _startTile->getIdX() - 5;
	int startY = _startTile->getIdY() - 5;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			tile* node = _vTotalList[(startY * TILEX) + startX + j + (i * TILEX)];

			if (node->getAttribute() == TR_WALL) continue;

			node->setTerrainFrameX(1);

			_moveList.push_back(node);
		}
	}

}