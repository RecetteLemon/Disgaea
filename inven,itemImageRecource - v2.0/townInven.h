#pragma once
#include "gameNode.h"
#include <vector>

enum TAGCURSORNUM
{
	CURSOR_1,
	CURSOR_2,
	CURSOR_3,
	CURSOR_4,
	CURSOR_5,
	CURSOR_6,
	CURSOR_7
};


enum TAGITEMSTAT
{
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_POTION,
	ITEM_NULL
};

class townInven : public gameNode
{
private:
	TAGCURSORNUM _cursorNum;
	TAGITEMSTAT _tagItemStat;

	RECT _itemInfo;
	RECT _itemNum1;
	RECT _itemNum10;
	RECT _wareHouseNum1;
	RECT _wareHouseNum10;
	RECT _wareHouseNum100;

	RECT _itemBag;
	RECT _itemBagBlock;
	RECT _wareHouse;
	RECT _wareHouseBlock;
	RECT _itemMove;
	RECT _itemCursor;

	RECT r_itemSlot[24];

	image* i_itemSlot[24];

	int _itemSlot;
	int _wareHouseSlot;

	bool _itemSlotUpMove;
	int _itemSlotMoveUpCount;

	int num;

	bool _wareHouseCheck;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void itemNumDraw();
	void slotMove();

	townInven();
	~townInven();
};

