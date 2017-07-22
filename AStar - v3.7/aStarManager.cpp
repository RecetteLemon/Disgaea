#include "stdafx.h"
#include "aStarManager.h"

aStarTile::aStarTile()
	: _totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL)
{
}

aStarTile::~aStarTile()
{
}

aStarManager::aStarManager()
	: _startTile(NULL), _currentTile(NULL),
	_endTile(NULL)
{
}

aStarManager::~aStarManager()
{
}


HRESULT aStarManager::init()
{
//	_currentMap = new tagIso[TILEX * TILEY * TILEZ];
	_startTile = new aStarTile;
	_endTile = new aStarTile;

	return S_OK;
}

void aStarManager::loadCurrentMap(tagIso* tiles)
{
	_vTotalList.clear();
	_startTile = NULL;
	_currentTile = NULL;
	_endTile = NULL;

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		aStarTile* node = new aStarTile;

		node->setIso(tiles[i]);
		node->setTotalCost(0);
		node->setCostFromStart(0);
		node->setCostToGoal(0);
		node->setIsOpen(1);

		_vTotalList.push_back(node);
	}
}

vector<aStarTile*> aStarManager::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIso().indexX - 1;	// �˻� ������ ��ǥ X
	int startY = currentTile->getIso().indexY - 1;	// �˻� ������ ��ǥ Y
//	int startZ = currentTile.z / TILESIZEZ - 1;		// �˻� ������ ��ǥ Z

	// �ڽ��� �ֺ�Ÿ���� �˻��ؾߵǱ� ������ ���� �ΰ� �����ϴ�.
	for (int y = 0; y < 3; ++y) for (int x = 0; x < 3; ++x)
	{
		// �迭�� ������ �ǰų� �Ѿ�� ������
		if (startX + x < 0 || startY + y < 0) continue;
		if (startX + x >= TILEX || startY + y >= TILEY) continue;

		if (y == 0 && x == 0) continue;
		if (y == 0 && x == 2) continue;
		if (y == 2 && x == 0) continue;
		if (y == 2 && x == 2) continue;

		// ���¸���Ʈ�� ������
		aStarTile* node = _vTotalList[(startY * TILEX) + startX + x + (y * TILEX)];

		if (!node->getIsOpen()) continue;
		if (node == _startTile) continue;
		//		if (node->getAttribute() == TR_WALL) continue;

		//		node->setIso(_currentMap[startX + k][startY + j][startZ + i]);
		//		(startY * TILEX) + startX + j + (i * TILEX)
		//		node->setIso(_currentMap[(startZ * TILEY * TILEX) + (startY * TILEX) + startX + x + (y * TILEX) + (z * TILEY * TILEX)]);

		node->setParentNode(_currentTile);

		// �߰��Ұ��� ���Ұ��� �˻��� �ӽú���
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

void aStarManager::pathFinder(aStarTile* currentTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIso().indexX - _vOpenList[i]->getIso().indexX)
			+ abs(_endTile->getIso().indexY - _vOpenList[i]->getIso().indexY)) * 10);

		_vOpenList[i]->setCostFromStart(10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//���� ����� ���� �ָ� ����
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		//���¸���Ʈ�� ��� Ÿ���� ����Ÿ���̸�(���� ª�� ���̸�)
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				//addObj ����
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
		vectorClear();
		return;
	}

	//����Ÿ���� �Ӽ��� ���� -> ����������!
	if (tempTile == _endTile)
	{
		_vMoveList.insert(_vMoveList.begin(), tempTile->getIso());
		//�̶����� ������ Ÿ���� ��ĥ�ض�
		while (_currentTile->getParentNode() != NULL)
		{
			_vMoveList.insert(_vMoveList.begin(), _currentTile->getIso());
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}

	//����� Ÿ�� ��� ���Ϳ� ����Ÿ�� Ǫ�ù�
	_vCloseList.push_back(tempTile);

	//���¸���Ʈ�߿� ����� Ÿ���� ������ ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	pathFinder(_currentTile);
}

void aStarManager::render()
{
	WCHAR str[64];

	for (int i = 0; i < _vMoveList.size(); ++i)
	{
		wsprintf(str, L"%d %d", _vMoveList[i].indexX, _vMoveList[i].indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, WINSIZEX - 200, i * 25 + 25, WINSIZEX - 100, i * 25 + 25);
	}

	if (_startTile)
	{
		wsprintf(str, L"%d %d", _startTile->getIso().indexX, _startTile->getIso().indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, _startTile->getIso().x - CAMERAMANAGER->getX(), _startTile->getIso().y - CAMERAMANAGER->getY(),
		_startTile->getIso().x + 150 - CAMERAMANAGER->getX(), _startTile->getIso().y + 100 - CAMERAMANAGER->getY());
	}

	if (_endTile)
	{
		wsprintf(str, L"%d %d", _endTile->getIso().indexX, _endTile->getIso().indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, _endTile->getIso().x - CAMERAMANAGER->getX(), _endTile->getIso().y - CAMERAMANAGER->getY(),
			_endTile->getIso().x + 150 - CAMERAMANAGER->getX(), _endTile->getIso().y + 100 - CAMERAMANAGER->getY());
	}

//	for (int i = 0; i < TILEX * TILEY; i++)
//	{
//		for (int j = 0; j <= _vTotalList[i]->getIso().z; j++)
//		{
//			IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_vTotalList[i]->getIso().x - TILESIZEX / 2,
//				_vTotalList[i]->getIso().y - j * TILESIZEZ,
//				_vTotalList[i]->getIso().terFrame.x, _vTotalList[i]->getIso().terFrame.y, true, 1.0f);
//		}
//
//	}
//	for (int i = 0; i < TILEX * TILEY; i++)
//	{
//		if (_vTotalList[i]->getIso().obj == OBJ_ERASE) continue;
//		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_vTotalList[i]->getIso().x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
//			_vTotalList[i]->getIso().y - _vTotalList[i]->getIso().z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
//			_vTotalList[i]->getIso().objFrame.x, _vTotalList[i]->getIso().objFrame.y, true, 1.0f);
//	}
}

void aStarManager::vectorClear()
{
	_vOpenList.clear();
	_vCloseList.clear();
	_vMoveList.clear();
}