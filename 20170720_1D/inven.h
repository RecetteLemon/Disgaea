#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

//아이템 능력치
//struct invenItem
//{
//	wstring Name;			//이름
//	ITEMTYPE Type;			//타입
//	image* Image;			//이미지
//	image* Explain;		//설명
//	int HP, SP;			//hp sp
//	int Atk, Int;			//물공, 마공
//	int Def, Res;			//물방, 마방
//	int Price;				//가격
//};

enum INVENPAGE
{
	TOWN_PAGE,
	BATTLE_PAGE
};

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
	//아이템 벡터
	vector<Item> _vItem;
	vector<Item>::iterator _viItem;

	//전투 인벤
	INVENPAGE _invenPage;
	RECT _itemBag;
	RECT _cursor;
	RECT _bar;
	RECT _sort;
	RECT _upDirection;
	RECT _downDirection;
	RECT _slot[24];
	RECT _showingSlot[6];
	RECT _infoBox;
	image* i_bar;
	image* i_cursor;
	image* i_slot[24];
	BAGSLOT _slotChoice;
	item* _item;
	int _slotNum; // 슬롯번호
	int _slotCount; // 슬롯카운트
	int _currentFrameY;
	int _listNum;

	float _alpha;
	//화살표
	bool _upDirectionOn;
	bool _downDirectionOn;
	//토글
	bool _upTo;
	bool _downTo;
	//정보창
	bool _isInfoOn;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//전투 인벤용
	void slot();
	void alpha();
	void directionFlash();
	void listSet();
	void moveBar();
	void infoBox();

	inven();
	~inven();
};

