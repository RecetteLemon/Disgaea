#pragma once
#include "gameNode.h"

enum BAGSLOT
{
	SLOT_1,
	SLOT_2,
	SLOT_3,
	SLOT_4,
	SLOT_5,
	SLOT_6
};

class inven : public gameNode
{
private:
	RECT _itemBag;
	RECT _cursor;
	RECT _bar;
	RECT _slot[24];
	image* i_bar;
	image* i_cursor;
	image* i_slot;
	BAGSLOT _slotChoice;
	int _slotNum; // ½½·Ô¹øÈ£
	int _slotCount; // ½½·ÔÄ«¿îÆ®
	float a;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void slot();

	inven();
	~inven();
};

