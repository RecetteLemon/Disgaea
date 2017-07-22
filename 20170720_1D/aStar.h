#pragma once
#include "singletonBase.h"
#include "tile.h"
#include <vector>

//aStar �˰��� ����� ���� Ÿ�ϵ�
class aStarTile
{
private:
	tagIso _iso;				

	//f = g + h
	float _totalCost;			//f
	float _costFromStart;		//g == ���������� ���� ���(Ÿ��)���� ���
	float _costToGoal;			//h == ���� ���(Ÿ��)���� �������� ���

	bool _isOpen;				//�� �� �ִ� Ÿ���ΰ� 

	aStarTile* _parentNode;		//�� Ÿ���� �������(��� ���� �Ǵ�)

public:
	//�� Ÿ���� �ε��� 
	int getIdX(void) { return _iso.x / TILESIZEX; }		
	int getIdY(void) { return _iso.y / TILESIZEY; }

	//POINT getCenter(void) { return _center; }
	//TERRAIN_TYPE getAttribute() { return _iso.ter; }

	// === getter, setter === //

	//iso Ÿ��
	void setIso(tagIso iso) { _iso = iso; }
	tagIso &getIso() { return _iso; }

	//���� �ڽ�Ʈ(f)
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	//�������������� �ڽ�Ʈ(g)
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	//�������������� �ڽ�Ʈ(h)
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	//�θ� ���
	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }

	//�� �� �ִ� ��?
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }

};

class aStar
{
private:
	// �� ��ü
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//���� Ÿ�� �������� Ž���� �� �� �ִ� ��
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//Ž���� �� �� �ִ� ��(OpenList) �� ����� ���� ���� ��
	vector<aStarTile *> _vCloseList;
	vector<aStarTile *>::iterator _viCloseList;

	//ĳ���Ϳ��� �ѱ� ����� ��
	vector<tagIso> _vMoveList;
	vector<tagIso>::iterator _viMoveList;

	//���� ��
//	tagIso* _currentMap;

	aStarTile* _startTile;		//���� Ÿ��
	aStarTile* _goalTile;		//��ǥ Ÿ��
	aStarTile* _currentTile;	//���� Ÿ��

public:
	aStar();
	~aStar();

	HRESULT init(tagIso* currentMap, int startX, int startY);
	void release();
 
	vector<aStarTile*> addOpenList(aStarTile* currentTile);	//�� �� �ִ� �� ����
	void pathFinder(aStarTile* currentTile);				//Ÿ�� �˻�

	void renderGoalList();									//��ǥ Ÿ���� �� �� �ִ� �͵��� �����ش�

	void vectorClear();

	// === gettter, setter === // 

	//���� Ÿ��
	inline void setStartTile(tagIso tile) { _startTile->setIso(tile); }
//	inline void setStartTile(int x, int y) { x / TILESIZEX + y / TILESIZEY; } ��ǥ �������� ����...
	inline tagIso getStartTile() { return _startTile->getIso(); }

	//��ǥ Ÿ��
	inline void setGoalTile(tagIso tile) { _goalTile->setIso(tile); }
//	inline void setStartTile(int x, int y) { x / TILESIZEX + y / TILESIZEY; } ��ǥ �������� ����...
	inline tagIso getGoalTile() { return _goalTile->getIso(); }

	//�̵������� Ÿ��
	inline void setMoveTile();
	inline vector<tagIso> &getMoveTile() { return _vMoveList; }	//ĳ���Ϳ��� �̵��� ���� �Ѱ��ش�
};