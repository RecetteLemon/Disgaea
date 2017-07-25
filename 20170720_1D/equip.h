#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

enum EQUIP_SLOT
{
	ESLOT_1,
	ESLOT_2,
	ESLOT_3,
	ESLOT_4
};

enum INVEN_SLOT
{
	ISLOT_1,
	ISLOT_2,
	ISLOT_3,
	ISLOT_4,
	ISLOT_5,
	ISLOT_6
};

enum EQUIPSTATE
{
	INVEN,
	EQUIP
};

class equip : public gameNode
{
private:
	vector<Item> _vTemp;
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
	INVEN_SLOT _slotNum;
	EQUIP_SLOT _EslotNum;
	EQUIPSTATE _state;
	RECT _equipSlot[4];
	//커서
	RECT _cursor;
	RECT _tempCursor;
	bool _isTemp;
	//바
	RECT _bar;
	int _slotCount;
	int _num;
	int _tempNum;
	image* face;
	bool _infoOn;

	bool _isEquip;


	int _charNum;
	int _currentFrameX;
	int _currentFrameY;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void cursorMove();
	void slotMove();
	void itemInfo();
	void equipItem();
	void statUP_weapon();
	void statUP_armor();
	void takeOff_weapon();
	void takeOff_armor(int i);

	void setCharNum(int charNum) { _charNum = charNum; }

	equip();
	~equip();
};


