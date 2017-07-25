#pragma once
#include "gameNode.h"
#include "characterSelet.h"
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

enum TAGSLOT
{
	SLOT_01,
	SLOT_02,
	SLOT_03,
	SLOT_04,
	SLOT_05,
	SLOT_06,
	SLOT_07
};

enum TAGITEMSTAT
{
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_POTION
	//ITEM_NULL
};

class townInven : public gameNode
{
private:
	vector<Item> _vItem;
	vector<Item>::iterator _viItem;

	//인벤
	vector<Item> _vInven;
	vector<Item>::iterator _viInven;
	vector<Item> _vTemp;
	vector<Item>::iterator _viTemp;
	//창고
	vector<Item> _vWareHouse;

	TAGCURSORNUM _cursorNum;
	TAGITEMSTAT _tagItemStat;
	TAGSLOT _tagSlot;

	RECT _itemBottom;
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
	RECT r_wareSlot[512];
	image* i_itemSlot[24];
	image* i_wareSlot[512];
	RECT _moveCursor;

	RECT _itemName2;
	RECT _itemInfo2;

	bool _moveCheck;
	int _itemSlot;
	int _wareHouseSlot;

	bool _itemSlotUpMove;
	int _itemSlotMoveUpCount;

	int num;
	int _test;
	int _test1;

	int _wareNum;
	int _slotNum;
	bool _wareHouseCheck;
	bool _swap;
	float _blockMove;
	float _wareBlockMove;

	int firstNum, secNum;
	//사용할지에 관한 불값
	bool _isItem;
	characterSelet* _charSel;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void itemNumDraw();
	void swapItem(int x, int y);

	void sortItem();
	void SendItem();
	void eatItem();

	townInven();
	~townInven();
};