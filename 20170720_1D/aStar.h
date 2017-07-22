#pragma once
#include "singletonBase.h"
#include "tile.h"
#include <vector>

//aStar 알고리즘 계산을 위한 타일들
class aStarTile
{
private:
	tagIso _iso;				

	//f = g + h
	float _totalCost;			//f
	float _costFromStart;		//g == 시작점부터 현재 노드(타일)까지 비용
	float _costToGoal;			//h == 현재 노드(타일)부터 끝점까지 비용

	bool _isOpen;				//갈 수 있는 타일인가 

	aStarTile* _parentNode;		//이 타일의 상위노드(계속 갱신 되는)

public:
	//이 타일의 인덱스 
	int getIdX(void) { return _iso.x / TILESIZEX; }		
	int getIdY(void) { return _iso.y / TILESIZEY; }

	//POINT getCenter(void) { return _center; }
	//TERRAIN_TYPE getAttribute() { return _iso.ter; }

	// === getter, setter === //

	//iso 타일
	void setIso(tagIso iso) { _iso = iso; }
	tagIso &getIso() { return _iso; }

	//최종 코스트(f)
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	//시작지점부터의 코스트(g)
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	//도착지점부터의 코스트(h)
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	//부모 노드
	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }

	//갈 수 있는 길?
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }

};

class aStar
{
private:
	// 맵 전체
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	//지금 타일 기준으로 탐색한 갈 수 있는 길
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	//탐색한 갈 수 있는 길(OpenList) 중 비용이 제일 적은 길
	vector<aStarTile *> _vCloseList;
	vector<aStarTile *>::iterator _viCloseList;

	//캐릭터에게 넘길 가까운 길
	vector<tagIso> _vMoveList;
	vector<tagIso>::iterator _viMoveList;

	//현재 맵
//	tagIso* _currentMap;

	aStarTile* _startTile;		//시작 타일
	aStarTile* _goalTile;		//목표 타일
	aStarTile* _currentTile;	//지금 타일

public:
	aStar();
	~aStar();

	HRESULT init(tagIso* currentMap, int startX, int startY);
	void release();
 
	vector<aStarTile*> addOpenList(aStarTile* currentTile);	//갈 수 있는 길 색출
	void pathFinder(aStarTile* currentTile);				//타일 검사

	void renderGoalList();									//목표 타일이 될 수 있는 것들을 보여준다

	void vectorClear();

	// === gettter, setter === // 

	//시작 타일
	inline void setStartTile(tagIso tile) { _startTile->setIso(tile); }
//	inline void setStartTile(int x, int y) { x / TILESIZEX + y / TILESIZEY; } 좌표 기준으로 셋팅...
	inline tagIso getStartTile() { return _startTile->getIso(); }

	//목표 타일
	inline void setGoalTile(tagIso tile) { _goalTile->setIso(tile); }
//	inline void setStartTile(int x, int y) { x / TILESIZEX + y / TILESIZEY; } 좌표 기준으로 셋팅...
	inline tagIso getGoalTile() { return _goalTile->getIso(); }

	//이동가능한 타일
	inline void setMoveTile();
	inline vector<tagIso> &getMoveTile() { return _vMoveList; }	//캐릭터에게 이동할 길을 넘겨준다
};