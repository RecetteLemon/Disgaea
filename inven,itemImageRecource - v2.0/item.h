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
	image* Explain;		//����
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
	void itemSet();

	vector<Item> getVItem(void) { return _vItem; }
	vector<Item>::iterator getVIItem(void) { return _viItem; }

	item();
	~item();
};

