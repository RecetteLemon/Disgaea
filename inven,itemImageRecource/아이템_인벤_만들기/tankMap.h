#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//鸥老
	DWORD _attribute[TILEX * TILEY];	//瘤屈 加己
	int _pos[2];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load();

	tagTile* getTile() { return _tiles; }
	DWORD* getAttribute() {return _attribute;}

	//加己 立辟磊

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

	tankMap();
	~tankMap();
};

