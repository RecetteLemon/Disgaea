#pragma once
#include "gameNode.h"
#include <vector>

//������ Ÿ��
enum ITEMTYPE
{
	WEAPON,
	ARMOR,
	GENERAL
};
//������ �ɷ�ġ
struct Item
{
	wstring Name;			//�̸�
	ITEMTYPE Type;			//Ÿ��
	image* Image;			//�̹���
	image* Image2;			//�̹���2
	image* priceImage;			//����
	image* info;		//����
	int HP, SP;			//hp sp
	int Atk, Int;			//����, ����
	int Def, Res;			//����, ����
	int Price;				//����
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

