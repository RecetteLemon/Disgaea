#pragma once
#include "gameNode.h"
#include "mapToolScene.h"

class aStarTile
{
private:
	tagIso _iso;

	//f = g + h
	//f == totalCost
	//g == 시작점부터 현재 노드(타일)까지 비용
	//h == 현재 노드(타일)부터 끝점까지 비용

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//갈수있나?!

	aStarTile* _parentNode;	//상위노드(갱신이 되는)
public:
	int getIdX(void) { return _iso.x / TILESIZEX; }
	int getIdY(void) { return _iso.y / TILESIZEY; }

//	POINT getCenter(void) { return _center; }

//	TERRAIN_TYPE getAttribute() { return _iso.ter; }

	// == getter, setter 함수들 == //

	// 아이소 타일
	void setIso(tagIso iso) { _iso = iso; }
	tagIso getIso() { return _iso; }
	// 최종 코스트
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }
	// 시작지점부터의 코스트
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }
	// 도착지점부터의 코스트
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }
	// 부모 노드
	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }
	// 길이 열림?
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }
};

class aStar : public gameNode
{
private:
	// 전체 타일
	vector<aStarTile*> _vTotalList;
	vector<aStarTile*>::iterator _viTotalList;

	// 찾을 범위 벡터
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	// _vOpenList벡터 중 코스트가 제일 낮은걸 찾은 벡터
	vector<aStarTile*> _vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	// 캐릭터한테 넘길 벡터
	vector<tagIso> _vMoveList;
	vector<tagIso>::iterator _viMoveList;

	// 현재 맵
//	tagIso _currentMap;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;
public:
	HRESULT init();

	//	inline void setStartPosition() { ; }
	void loadCurrentMap(tagIso (*tiles)[TILEY][TILEZ]);
	vector<aStarTile*> addOpenList(aStarTile* currentTile);					// 검사할 타일 색출
	void pathFinder(aStarTile* currentTile);								// 타일 검사

	void release();
	void update();
	void render();

	aStar();
	~aStar();
};

