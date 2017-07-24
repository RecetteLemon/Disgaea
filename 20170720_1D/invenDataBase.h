#pragma once
#include "gameNode.h"
#include "item.h"

class invenDataBase : public singletonBase<invenDataBase>
{
private:
	//������ ����
	vector<Item> _vInvenItem;
	vector<Item>::iterator _viInvenItem;
	//â�� ����
	vector<Item> _vWareHouse;
public:
	//�κ� ���Ͱ� ��������
	vector<Item> getVItem(void) { return _vInvenItem; }
	vector<Item>::iterator getVIItem(void) { return _viInvenItem; }
	//Ǫ�ù�
	void pushBackVItem(int i, vector<Item> Item) { _vInvenItem.push_back(Item[i]); }
	//�����Ѱ����� ���� ������ �����
	void eraseVItem(int i) { _vInvenItem.erase(_vInvenItem.begin() + i, _vInvenItem.end()); }
	//�ϳ��� ����� 
	void erase2VItem(int i) { _vInvenItem.erase(_vInvenItem.begin() + i); }
	//Ŭ����
	void clearVItem() { _vInvenItem.clear(); }
	//����
	void swapVItem(vector<Item> Item) { _vInvenItem.swap(Item); }
	//=========================================================================================
	//â�� ���� ��������
	vector<Item> getVWareHouse(void) { return _vWareHouse; }
	//â�� Ǫ�ù�
	void pushBackWareHouse(int i, vector<Item> Item) { _vWareHouse.push_back(Item[i]); }
	//â�� �ϳ� �����
	void eraseWareHouse(int i) { _vWareHouse.erase(_vWareHouse.begin() + i); }
	//â�� �����Ѱ� ���� ������ �����
	void eraseWareHouse2(int i) { _vWareHouse.erase(_vWareHouse.begin() + i, _vWareHouse.end()); }
	invenDataBase();
	~invenDataBase();
};
