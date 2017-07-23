#include "stdafx.h"
#include "aStarManager.h"
#include "aStar.h"

aStar::aStar()
	: _startTile(NULL), _currentTile(NULL),
	_goalTile(NULL)
{
}

aStar::~aStar()
{
}


HRESULT aStar::init(tagIso* currentMap, int startX, int startY)
{
//	_currentMap = new tagIso[TILEX * TILEY];
//	_currentMap = currentMap;

	//���� ������ ���� Ÿ�Ϸ�
//	_startTile->setIso(_currentMap[(startX / TILESIZEX) * (startY / TILESIZEY)]);

	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	_vMoveList.clear();

	_startTile = NULL;
	_currentTile = NULL;
	_goalTile = NULL;

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		aStarTile* node = new aStarTile;

		node->setIso(currentMap[i]);
		node->setTotalCost(0);
		node->setCostFromStart(0);
		node->setCostToGoal(0);
		node->setIsOpen(1);

		if (((startX / TILESIZEX) * (startY / TILESIZEY)) == i)
		{
			_startTile = node;
			continue;
		}

		_vTotalList.push_back(node);
	}

	return S_OK;
}

void aStar::release()
{
	//������ �� ������ 
//	SAFE_DELETE(_currentMap);

	//���ʹ� ����ϰ� ����
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	_vMoveList.clear();

	//Ÿ�ϵ� ������
	SAFE_DELETE(_startTile);
	SAFE_DELETE(_goalTile);
	SAFE_DELETE(_currentTile);
}

//�� �� �ִ� �� ����
vector<aStarTile*> aStar::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIso().indexX - 1;	// �˻� ������ ��ǥ X
	int startY = currentTile->getIso().indexY - 1;	// �˻� ������ ��ǥ Y

	// �ڽ��� �ֺ�Ÿ���� �˻��ؾߵǱ� ������ ���� �ΰ� �����ϴ�.
	for (int y = 0; y < 3; ++y) for (int x = 0; x < 3; ++x)
	{
		// �迭�� ������ �ǰų� �Ѿ�� ������.
		if (startX + x < 0 || startY + y < 0) continue;
		if (startX + x >= TILEX || startY + y >= TILEY) continue;

		// �밢�� �����ֱ� ���� ����ó���Դϴ�.
		if (y == 0 && x == 0) continue;
		if (y == 0 && x == 2) continue;
		if (y == 2 && x == 0) continue;
		if (y == 2 && x == 2) continue;

		// �˻��� �������Ϳ� �����̴ϴ�.
		aStarTile* node = _vTotalList[(startY * TILEX) + startX + x + (y * TILEX)];

		// �� �����ְų� ���������̸� ������ �Ѱ��ݽô�.
		// �Ʊ� �ϴٰ� �̰Ŷ����� �ָԾ����.. (�θ��忡 ��� �Ȱ����� ��ܼ� ���ѷ��� �ȴٴ��� �׷���..)
		if (!node->getIsOpen()) continue;
		if (node == _startTile) continue;

		// ���� �θ��忡 ����Ÿ�� �־��ݽô�.
		// (�� pathfinder �Լ����� _currentTile�� NULL �̸� While�� ���������ϱ� �� ó���� NULL�� �ʱ�ȭ ������մϴ�!)
		node->setParentNode(_currentTile);

		// �߰��Ұ��� ���Ұ��� �˻��� �ӽú���
		bool addObj = true;

		// ���࿡ �Ȱ��� ���� ���� �߰����ϰ� �����ݴϴ�. (����ó��)
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == node)
			{
				addObj = false;
				break;
			}
		}

		// ����ó����
		if (!addObj) continue;

		// �� �˻縦 ������ ���Ϳ� ����ݽô�.
		_vOpenList.push_back(node);
	}

	// �˻簡 �������� ���� �Ѱ��ݽô�.
	return _vOpenList;
}

//Ÿ�� �˻�
void aStar::pathFinder(aStarTile* currentTile)
{
	// �˻糪 �ӽ÷� ������� �ӽ� ������ �Դϴ�.
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	// �� for���� ������ addOpenList() �Լ����� ������ ��ŭ�� ���ϴ�.
	// �����Ѱ� ������ �翬�� �� for���� ���� �ʰ���? (���� ������ �ӽú��� tempTile�� �翬�� �����Ⱚ)
	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		// ������ ��ǥ�߿� �������������� ����� ���մϴ�.
		_vOpenList[i]->setCostToGoal((abs(_goalTile->getIso().indexX - _vOpenList[i]->getIso().indexX)
			+ abs(_goalTile->getIso().indexY - _vOpenList[i]->getIso().indexY)) * 10);

		// ���� ��ǥ���� ������ ��ǥ������ ����� ���մϴ�.
		_vOpenList[i]->setCostFromStart(10);

		// ���� ���ؼ� ���� ����� ���մϴ�.
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//���� ����� ���� ���� ã���ϴ�.
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		// ������ �����߿� tempTile�� ������ �߰����� �ʽ��ϴ�.
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				//addObj ����
				addObj = false;
				continue;
			}
		}

		// ���߿� �����Ҷ��� ���� ���°�(����ó��)
		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	if (addOpenList(currentTile).size() == NULL)
	{
		//vectorClear();
		return;
	}

	//����Ÿ���� �Ӽ��� ���� -> ����������!
	if (tempTile == _goalTile)
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

void aStar::render()
{
	if (_goalTile)
	{
		WCHAR str[126];
		swprintf(str, L"%d %d", _goalTile->getIso().indexX, _goalTile->getIso().indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, 500, 0, 550, 10);
	}
	if (_startTile)
	{
		WCHAR str[128];
		swprintf(str, L"%d %d", _startTile->getIso().indexX, _startTile->getIso().indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, 600, 0, 650, 10);
	}
	for (int i = 0; i < _vMoveList.size(); i++)
	{
		WCHAR str[128];
		swprintf(str, L"%d %d", _vMoveList[i].indexX, _vMoveList[i].indexY);
		DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, _vMoveList[i].centerX, _vMoveList[i].centerY, _vMoveList[i].centerX + 30, _vMoveList[i].centerY + 30);
	}
}

//�̵������� Ÿ���� �����Ѵ� 
void aStar::setMoveTile(tagIso tile)
{
	int startX = tile.indexX - 5;//-5ĭ -5ĭ���� �ָ��� �˻��ϴ� ��...
	int startY = tile.indexY - 5;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//�ϴ� �������� ���� ����
			if (startX + j < 0 || startY + i < 0) continue;
			if (startX + j > TILEX - 1 || startY + i > TILEY - 1) continue;

			tagIso node = _vTotalList[(startY * TILEX) + startX + j + (i * TILEX)]->getIso();

			if (node.ter == 1) continue;//���̶�� ���� ����

			if (abs(node.indexX - _startTile->getIso().indexX) + abs(node.indexY - _startTile->getIso().indexY) <= 5)
			{
				//Ÿ�� �̹����� ���� 
				_vMoveList.push_back(node);//�ϰ� ������ �� �ִ� ���� �丸ŭ�� ���� 
			}
		}
	}
}

void aStar::vectorClear()
{
	_vOpenList.clear();
	_vCloseList.clear();
}

void aStar::moveListUpdate()
{
	_vMoveList.clear();
}