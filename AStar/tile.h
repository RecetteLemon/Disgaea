#pragma once
#include "gameNode.h"
#include <string>

#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_POISON		0x00000004


enum TERRAIN
{
	TR_START, TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_WALL, TR_ROAD, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//f = g + h
	//f == totalCost
	//g == 시작점부터 현재 노드(타일)까지 비용
	//h == 현재 노드(타일)부터 끝점까지 비용

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	int _terrainFrameX;
	int _terrainFrameY;
	int _objFrameX;
	int _objFrameY;

	bool _isOpen;	//갈수있나?!

	tile* _parentNode;	//상위노드(갱신이 되는)

	TERRAIN _attribute;
	OBJECT _obj;

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release(void);
	void update(void);
	void render(void);

	int getIdX(void) { return _idX; }
	int getIdY(void) { return _idY; }

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter(void) { return _center; }

	void setAttribute(TERRAIN str) { _attribute = str; }
	TERRAIN getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }

	void setTerrainFrameX(int frameX) { _terrainFrameX = frameX; }
	int getTerrainFrameX() { return _terrainFrameX; }

	void setTerrainFrameY(int frameY) { _terrainFrameY = frameY; }
	int getTerrainFrameY() { return _terrainFrameY; }
};

