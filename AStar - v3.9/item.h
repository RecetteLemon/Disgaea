#pragma once
#include "gameNode.h"
#include <vector>

//아이템 타입
enum ITEMTYPE
{
	WEAPON,
	ARMOR,
	GENERAL
};
//아이템 능력치
struct Item
{
	wstring Name;			//이름
	ITEMTYPE Type;			//타입
	image* Image;			//이미지
	image* Image2;			//이미지2
	image* priceImage;			//가격
	image* info;		//설명
	int HP, SP;			//hp sp
	int Atk, Int;			//물공, 마공
	int Def, Res;			//물방, 마방
	int Price;				//가격
};

class item : public gameNode
{
private:
	vector<Item> _vItem;
	vector<Item>::iterator _viItem;

public:
	HRESULT init();
	void release();
	void sellItem(int a);
	void buyItem(int a);

	vector<Item> getVItem(void) { return _vItem; }
	vector<Item>::iterator getVIItem(void) { return _viItem; }

	item();
	~item();
};

