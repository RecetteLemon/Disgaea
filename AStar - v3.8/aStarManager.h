#pragma once
#include "singletonBase.h"
#include "tile.h"
#include <vector>

class aStarTile
{
private:
	tagIso _iso;

	//f = g + h
	//f == totalCost
	//g == ���������� ���� ���(Ÿ��)���� ���
	//h == ���� ���(Ÿ��)���� �������� ���

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//�����ֳ�?!

	aStarTile* _parentNode;	//�������(������ �Ǵ�)
public:
	aStarTile();
	~aStarTile();

	// == getter, setter �Լ��� == //

	// ���̼� Ÿ��
	void setIso(tagIso iso) { _iso = iso; }
	tagIso getIso() { return _iso; }
	// ���� �ڽ�Ʈ
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }
	// �������������� �ڽ�Ʈ
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }
	// �������������� �ڽ�Ʈ
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }
	// �θ� ���
	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }
	// ���� ����?
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }
};

class aStarManager : public singletonBase<aStarManager>
{
private:
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	// ã�� ���� ����
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	// _vOpenList���� �� �ڽ�Ʈ�� ���� ������ ã�� ����
	vector<aStarTile*> _vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	// ĳ�������� �ѱ� ����
	vector<tagIso> _vMoveList;
	vector<tagIso>::iterator _viMoveList;

	// ���� ��
//	tagIso* _currentMap;

	aStarTile* _startTile;
	aStarTile* _currentTile;
	aStarTile* _endTile;

public:
	aStarManager();
	~aStarManager();

	HRESULT init();

	void loadCurrentMap(tagIso* tiles);							// ���� ���� �����´�
	vector<aStarTile*> addOpenList(aStarTile* currentTile);		// �˻��� Ÿ�� ����
	void pathFinder(aStarTile* currentTile);					// Ÿ�� �˻�

	void render();

	void vectorClear();
	void moveListUpdate();

	// getter setter ����

	inline void setStartTile(int arrayNum)											// ���� ��ǥ�� ����
	{
		vectorClear();
		_startTile = _vTotalList[arrayNum];
		_currentTile = _startTile;
	}
	inline aStarTile* getStartTile() { return _startTile; }							// ���� ��ǥ�� ������

	inline void setEndTile(int arrayNum) { _endTile = _vTotalList[arrayNum]; }		// ���� ��ǥ�� ����
	inline aStarTile* getEndTile() { return _endTile; }								// ���� ��ǥ�� ������

	inline vector<tagIso> &getMoveTile() { return _vMoveList; }						// ĳ�������� ������ ��ǥ �ٶ� �����
};

