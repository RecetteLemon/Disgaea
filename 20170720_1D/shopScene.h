#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>
//�� ������
enum shopPage
{
	SHOP_MAIN,
	SHOP_BUY,
	SHOP_SELL
};
//�� ���� �޴�
enum SHOPMAINMENU
{
	SELECT_BUY, SELECT_SELL
};
//���� ������ ����
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
//�Ǹ� ������ Ÿ��
enum SELLTYPE
{
	TYPE_INVEN,
	TYPE_WAREHOUSE
};
//�Ǹ� ������ ����
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
	//�κ�
	vector<Item> _vInven;
	vector<Item>::iterator _viInven;
	vector<Item> _vTemp;
	vector<Item>::iterator _viTemp;
	//â��
	vector<Item> _vWareHouse;
private:
	shopPage _page;
	item* _item;
	//����
	RECT _cursor;
	RECT _bar;
	//���ο�
	RECT _buy;
	RECT _sell;
	SHOPMAINMENU _menu;
	image* _menuInfo;
	//���Կ�
	RECT _slot[11];
	image* i_slot[11];
	BUYSLOT _buySlot;
	SELLSLOT _sellSlot;

	int _buySlotNum;
	int _changeNum;
	//��������� ����
	bool _isBuyInfo;
	//�첫�� ����� ����
	bool _isBuying;
	image* _infoImage;
	//�Ǹſ�
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

