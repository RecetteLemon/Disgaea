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
	//g == 시작점부터 현재 노드(타일)까지 비용
	//h == 현재 노드(타일)부터 끝점까지 비용

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//갈수있나?!

	aStarTile* _parentNode;	//상위노드(갱신이 되는)
public:
	aStarTile();
	~aStarTile();

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

class aStarManager : public singletonBase<aStarManager>
{
private:
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
//	tagIso* _currentMap;

	aStarTile* _startTile;
	aStarTile* _currentTile;
	aStarTile* _endTile;

public:
	aStarManager();
	~aStarManager();

	HRESULT init();

	void loadCurrentMap(tagIso* tiles);							// 현재 맵을 가져온다
	vector<aStarTile*> addOpenList(aStarTile* currentTile);		// 검사할 타일 색출
	void pathFinder(aStarTile* currentTile);					// 타일 검사

	void render();

	void vectorClear();

	// getter setter 설정

	inline void setStartTile(int arrayNum)											// 시작 좌표를 설정
	{
		vectorClear();
		_startTile = _vTotalList[arrayNum];
		_currentTile = _startTile;
	}
	inline aStarTile* getStartTile() { return _startTile; }							// 시작 좌표를 가져옴

	inline void setEndTile(int arrayNum) { _endTile = _vTotalList[arrayNum]; }		// 도착 좌표를 설정
	inline aStarTile* getEndTile() { return _endTile; }								// 도착 좌표를 가져옴

	inline vector<tagIso> &getMoveTile() { return _vMoveList; }						// 캐릭터한테 움직일 좌표 줄때 사용함
};

