#include "stdafx.h"
#include "aStarManager.h"
#include "aStar.h"

aStar::aStar()
{}

aStar::~aStar()
{}


HRESULT aStar::init(tagIso* currentMap, int startX, int startY)
{
	_currentMap = new tagIso[TILEX * TILEY];
	_currentMap = currentMap;

	//���� ������ ���� Ÿ�Ϸ�
	_startTile->setIso(_currentMap[(startX / TILESIZEX) * (startY / TILESIZEY)]);

	return S_OK;
}

void aStar::release()
{
	//������ �� ������ 
	SAFE_DELETE(_currentMap);

	//���ʹ� ����ϰ� ����
	_vOpenList.clear();
	_vCloseList.clear();
	_vMoveList.clear();

	//Ÿ�ϵ� ������
	SAFE_DELETE(_startTile);
	SAFE_DELETE(_goalTile);
	SAFE_DELETE(_currentTile);
}

//�� �� �ִ� �� ����
vector<aStarTile*> aStar::addOpenList(tagIso currentTile)
{
	int startX = currentTile.indexX - 1;			//�˻� ������ ��ǥ X
	int startY = currentTile.indexY - 1;			//�˻� ������ ��ǥ Y
	int floor = currentTile.floorZ;					//����

	//int startZ = currentTile.z / TILESIZEZ - 1;	// �˻� ������ ��ǥ Z
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
		//		node->setIso(_currentMap[(startZ * TILEY * TILEX) + (startY * TILEX) + startX + x + (y * TILEX) + (z * TILEY * TILEX)]);
		node->setIso(_currentMap[(startY * TILEX) + startX + x + (y * TILEX)]);

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

//Ÿ�� �˻�
void aStar::pathFinder(tagIso currentTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_goalTile->getIdX() - _vOpenList[i]->getIdX())
			+ abs(_goalTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

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

	pathFinder(_startTile->getIso());
}

//�÷��̾��� ���; ��ǥ Ÿ���� �� �� �ִ� �͵��� �����ش�
void aStar::renderGoalList()
{
	WCHAR str[64];

	for (int i = 0; i < _vMoveList.size(); ++i)
	{
		wsprintf(str, L"%d %d", _vMoveList[i].indexX, _vMoveList[i].indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, WINSIZEX - 200, i * 50 + 50, WINSIZEX - 100, i * 50 + 100);
	}
}

//�̵������� Ÿ���� �����Ѵ� 
void aStar::setMoveTile()
{
	int startX = _startTile->getIdX() - 5;//-5ĭ -5ĭ���� �ָ��� �˻��ϴ� ��...
	int startY = _startTile->getIdY() - 5;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//�ϴ� �������� ���� ����
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			tagIso node = _currentMap[(startY * TILEX) + startX + j + (i * TILEX)];

			if (node.ter == 1) continue;//���̶�� ���� ����

			if (abs(node.indexX - _startTile->getIso().indexX) + abs(node.indexY - _startTile->getIso().indexY) <= 5)
			{
				//Ÿ�� �̹����� ���� 
				_vMoveList.push_back(node);//�ϰ� ������ �� �ִ� ���� �丸ŭ�� ���� 
			}
		}
	}
}
