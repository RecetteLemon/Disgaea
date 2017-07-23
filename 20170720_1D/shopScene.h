#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>
//샵 페이지
enum shopPage
{
	SHOP_MAIN,
	SHOP_BUY,
	SHOP_SELL
};
//샵 메인 메뉴
enum SHOPMAINMENU
{
	SELECT_BUY, SELECT_SELL
};
//구매 페이지 슬롯
enum BUYSLOT
{
	BUY_SLOT_1,
	BUY_SLOT_2,
	BUY_SLOT_3,
	BUY_SLOT_4,
	BUY_SLOT_5,
	BUY_SLOT_6,
	BUY_SLOT_7,
	BUY_SLOT_8
};
//판매 페이지 타입
enum SELLTYPE
{
	TYPE_INVEN,
	TYPE_WAREHOUSE
};
//판매 페이지 슬롯
enum SELLSLOT
{
	SELL_SLOT_1,
	SELL_SLOT_2,
	SELL_SLOT_3,
	SELL_SLOT_4,
	SELL_SLOT_5,
	SELL_SLOT_6,
	SELL_SLOT_7
};

class shopScene : public gameNode
{
private:
	//인벤
	vector<Item> _vInven;
	vector<Item>::iterator _viInven;
	vector<Item> _vTemp;
	vector<Item>::iterator _viTemp;
	//창고
	vector<Item> _vWareHouse;
private:
	shopPage _page;
	item* _item;
	//공용
	RECT _cursor;
	RECT _bar;
	//메인용
	RECT _buy;
	RECT _sell;
	SHOPMAINMENU _menu;
	image* _menuInfo;
	//구입용
	RECT _slot[11];
	image* i_slot[11];
	BUYSLOT _buySlot;
	SELLSLOT _sellSlot;

	int _buySlotNum;
	int _changeNum;
	//정보출력을 위한
	bool _isBuyInfo;
	//살껀지 물어보기 위한
	bool _isBuying;
	image* _infoImage;
	//판매용
	bool _isSelling;
	RECT _invenSlot[24];
	image* _invenSImage[24];
	int _slotIdx[24];
	RECT _wareHouseSlot[100];
	SELLTYPE _sellType;
	int _sellSlotNum;
	bool _togle;
	int _sortNum;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void pageChange();
	void mainPage();
	void buyPage();
	void sellPage();

	void buyingItem();
	void sellingItem();

	shopScene();
	~shopScene();
};

