#pragma once
#include "gameNode.h"

enum EQUIP_SLOT
{
	ESLOT_1,
	ESLOT_2,
	ESLOT_3,
	ESLOT_4,
	ESLOT_5,
	ESLOT_6
};

enum EQUIPSTATE
{
	INVEN,
	EQUIP
};

class equip : public gameNode
{
private:
	//기본 틀 렉트
	RECT _statBox;
	RECT _invenBox;
	RECT _itemBox;
	RECT _itemInfo;
	RECT _sort;
	//슬롯 생성
	RECT _slot[24];
	image* i_slot[24];
	EQUIP_SLOT _slotNum;
	EQUIPSTATE _state;
	RECT _equipSlot[4];
	//커서
	RECT _cursor;

	int _slotCount;
	int _num;
	int _tempNum;

	bool _infoOn;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
	void slotMove();
	void itemInfo();

	equip();
	~equip();
};

