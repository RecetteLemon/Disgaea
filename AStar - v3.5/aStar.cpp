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