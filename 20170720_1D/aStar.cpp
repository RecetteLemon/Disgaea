#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{
	_currentMap = new tagIso[TILEX * TILEY * TILEZ];

	return S_OK;
}

void aStar::loadCurrentMap(tagIso* tiles)
{
	_currentMap = tiles;

//	for (int i = 0; i < (TILEX * TILEY * TILEZ); ++i)
//	{
//		_currentMap[i] = tiles[i];
//	}

//	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
//	{
//		aStarTile* node = new aStarTile;
//
//		node->setIso(tiles[x + (y * TILEX) + (z * (TILEX * TILEY))]);
//
//		_vTotalList.push_back(node);
//	}
}

vector<aStarTile*> aStar::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIso().indexX - 1;			// �˻� ������ ��ǥ X
	int startY = currentTile->getIso().indexY - 1;			// �˻� ������ ��ǥ Y
	int startZ = currentTile->getIso().z / TILESIZEZ - 1;	// �˻� ������ ��ǥ Z

	// 2D ��鿡���� �ڽ��� �ֺ�, �� 3 * 3 �� Ÿ���� �˻��ߴٸ�
	// ���̼Ҹ�Ʈ�������� 3D ť�갡 �ִ� ġ�� x, y ��ǥ�Ӹ��� �ƴ� z ��ǥ�� �˻��ؾ� �ϹǷ�
	// �ڽ��� ��ǥ�� �ֺ��� ���̵� �����Ͽ� �� 3 * 3 * 3 �� 27Ÿ���� �˻��ϰ� �˴ϴ�.
	for (int z = 0; z < 3; ++z) for (int y = 0; y < 3; ++y) for (int x = 0; x < 3; ++x)
	{
		// ���¸���Ʈ�� ������
		aStarTile* node = new aStarTile;

//		if (!node->getIsOpen()) continue;
//		if (node->getAttribute() == TR_START) continue;
//		if (node->getAttribute() == TR_WALL) continue;

//		node->setIso(_currentMap[startX + k][startY + j][startZ + i]);
//		(startY * TILEX) + startX + j + (i * TILEX)
		node->setIso(_currentMap[(startZ * TILEY * TILEX) + (startY * TILEX) + startX + x + (y * TILEX) + (z * TILEY * TILEX)]);

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
		_vOpenList.clear();
		_vCloseList.clear();
		return;
	}

	//����Ÿ���� �Ӽ��� ���� -> ����������!
	if (tempTile->getIso().ter == TER_WALL)
	{
		_vMoveList.insert(_vMoveList.begin(), tempTile->getIso());
		//�̶����� ������ Ÿ���� ��ĥ�ض�
		while (_startTile->getParentNode() != NULL)
		{
			_vMoveList.insert(_vMoveList.begin(), _startTile->getIso());
			_startTile = _startTile->getParentNode();
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

	_startTile = tempTile;

	pathFinder(_startTile);
}

void aStar::release()
{

}


void aStar::update() 
{
	
}

void aStar::render() 
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (-CAMERAMANAGER->getX() + _currentMap[i].x + TILESIZEX / 2 < 22) continue;
		if (-CAMERAMANAGER->getX() + _currentMap[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		if (-CAMERAMANAGER->getY() + _currentMap[i].y + TILESIZEY / 2 < 22) continue;
		if (-CAMERAMANAGER->getY() + _currentMap[i].y - TILESIZEY / 2 > 22 + 624) continue;
		if (_currentMap[i].ter == TER_NONE) continue;

		IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_currentMap[i].x - TILESIZEX / 2,
			_currentMap[i].y - _currentMap[i].z,
			_currentMap[i].terFrame.x, _currentMap[i].terFrame.y, true, 1.0f);

	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (-CAMERAMANAGER->getX() + _currentMap[i].x + TILESIZEX / 2 < 22) continue;
		if (-CAMERAMANAGER->getX() + _currentMap[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		if (-CAMERAMANAGER->getY() + _currentMap[i].y + TILESIZEY / 2 < 22) continue;
		if (-CAMERAMANAGER->getY() + _currentMap[i].y - TILESIZEY / 2 > 22 + 624) continue;
		if (_currentMap[i].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_currentMap[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
			_currentMap[i].y - _currentMap[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
			_currentMap[i].objFrame.x, _currentMap[i].objFrame.y, true, 1.0f);
	}
}