#pragma once
#include "gameNode.h"
#include "item.h"

class invenDataBase : public singletonBase<invenDataBase>
{
private:
	//아이템 벡터
	vector<Item> _vInvenItem;
	vector<Item>::iterator _viInvenItem;
	//창고 벡터
	vector<Item> _vWareHouse;
public:
	//인벤 벡터값 가져오기
	vector<Item> getVItem(void) { return _vInvenItem; }
	vector<Item>::iterator getVIItem(void) { return _viInvenItem; }
	//푸시백
	void pushBackVItem(int i, vector<Item> Item) { _vInvenItem.push_back(Item[i]); }
	//지정한곳에서 부터 끝까지 지우기
	void eraseVItem(int i) { _vInvenItem.erase(_vInvenItem.begin() + i, _vInvenItem.end()); }
	//하나만 지우기 
	void erase2VItem(int i) { _vInvenItem.erase(_vInvenItem.begin() + i); }
	//클리어
	void clearVItem() { _vInvenItem.clear(); }
	//스왑
	void swapVItem(vector<Item> Item) { _vInvenItem.swap(Item); }
	//=========================================================================================
	//창고 벡터 가져오기
	vector<Item> getVWareHouse(void) { return _vWareHouse; }
	//창고 푸시백
	void pushBackWareHouse(int i, vector<Item> Item) { _vWareHouse.push_back(Item[i]); }
	//창고 하나 지우기
	void eraseWareHouse(int i) { _vWareHouse.erase(_vWareHouse.begin() + i); }
	//창고 지정한것 부터 끝까지 지우기
	void eraseWareHouse2(int i) { _vWareHouse.erase(_vWareHouse.begin() + i, _vWareHouse.end()); }
	invenDataBase();
	~invenDataBase();
};
