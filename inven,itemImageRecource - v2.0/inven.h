#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

//������ �ɷ�ġ
//struct invenItem
//{
//	wstring Name;			//�̸�
//	ITEMTYPE Type;			//Ÿ��
//	image* Image;			//�̹���
//	image* Explain;		//����
//	int HP, SP;			//hp sp
//	int Atk, Int;			//����, ����
//	int Def, Res;			//����, ����
//	int Price;				//����
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
	//������ ����
	vector<Item> _vItem;
	vector<Item>::iterator _viItem;

	//���� �κ�
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
	int _slotNum; // ���Թ�ȣ
	int _slotCount; // ����ī��Ʈ
	int _currentFrameY;
	int _listNum;

	float _alpha;
	//ȭ��ǥ
	bool _upDirectionOn;
	bool _downDirectionOn;
	//���
	bool _upTo;
	bool _downTo;
	//����â
	bool _isInfoOn;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���� �κ���
	void slot();
	void alpha();
	void directionFlash();
	void listSet();
	void moveBar();
	void infoBox();

	inven();
	~inven();
};

