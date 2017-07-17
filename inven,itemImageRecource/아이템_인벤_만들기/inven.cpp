#include "stdafx.h"
#include "inven.h"


inven::inven()
{
}


inven::~inven()
{
}

HRESULT inven::init()
{	
	IMAGEMANAGER->addImage("인벤","itemBag1.bmp", 332, 254,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("커서", "cursor.bmp", 31, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("바", "itembagButton.bmp", 24, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("논", "none.bmp", 284, 31, true, RGB(255, 0, 255));

	i_cursor = IMAGEMANAGER->findImage("커서");
	i_bar = IMAGEMANAGER->findImage("바");
	i_slot = IMAGEMANAGER->findImage("논");
	_itemBag = RectMake(50, WINSIZEY / 2 - 100, 332, 254);
	_cursor = RectMake(40, WINSIZEY / 2 - 50, 31, 24);
	_bar = RectMake(_itemBag.left + 304, _itemBag.top + 40, 24, 56);
	_slotChoice = SLOT_1;
	_slotNum = _slotCount = 0;

	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_itemBag.left + 8,_itemBag.top + 47 + (34*i) ,284, 31);
	}

	a = 0;

	return S_OK;
}

void inven::release()
{

}
void inven::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_slotNum--;
		if (_slotNum < 0) _slotNum = 0;
		_slotCount--;
		if (_slotCount < 0)
		{
			_slotNum = 5;
			_slotCount = 23;
		}
		//스크롤바 관련
		if (_slotNum == 5)
		{
			if (_slotCount == 23) _bar = RectMake(_itemBag.left + 304, _itemBag.top + 40 + 156, 24, 56);
		}
		if (_slotNum == 0)
		{
			if (_bar.top >= _itemBag.top + 40)
			{
				_bar.top -= 8.0f;
				_bar.bottom -= 8.0f;
				if (_bar.top < _itemBag.top + 40)_bar = RectMake(_itemBag.left + 304, _itemBag.top + 40, 24, 56);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_slotNum++;
		if (_slotNum > 5) _slotNum = 5;
		_slotCount++;
		if (_slotCount > 23)
		{
			_slotCount = 0;
			_slotNum = 0;
		}
		//스크롤바 관련
		if (_slotNum == 0)
		{
			if (_slotCount == 0) _bar = RectMake(_itemBag.left + 304, _itemBag.top + 40, 24, 56);
		}
		if (_slotNum == 5)
		{
			if (_bar.bottom <= _itemBag.top + 40 + 156 + 56)
			{
				_bar.top += 8.0f;
				_bar.bottom += 8.0f;
				if (_bar.top > _itemBag.top + 40 + 156 + 56)_bar = RectMake(_itemBag.left + 304, _itemBag.top + 40 + 156, 24, 56);
			}
		}
	}
	slot();
}
void inven::render()
{
	char str[256];
	sprintf(str, "슬롯넘버 : %d ", _slotNum+1);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
	sprintf(str, "슬롯카운트 : %d ", _slotCount+1);
	TextOut(getMemDC(), 0, 15, str, strlen(str));

	IMAGEMANAGER->render("인벤", getMemDC(), _itemBag.left, _itemBag.top);
	i_bar->render(getMemDC(), _bar.left, _bar.top);
	for (int i = 0; i < 6; i++)
	{
		Rectangle(getMemDC(), _slot[i].left, _slot[i].top, _slot[i].right, _slot[i].bottom);
		i_slot->render(getMemDC(), _slot[i].left, _slot[i].top);

	}
	i_cursor->render(getMemDC(), _cursor.left, _cursor.top);
}

void inven::slot()
{
	switch (_slotNum)
	{
	case 0:
		_slotChoice = SLOT_1;
		_cursor = RectMake(40, WINSIZEY / 2 - 50, 31, 24);
		break;
	case 1:
		_slotChoice = SLOT_2;
		_cursor = RectMake(40, WINSIZEY / 2 - 15, 31, 24);
		break;
	case 2:
		_slotChoice = SLOT_3;
		_cursor = RectMake(40, WINSIZEY / 2 + 20, 31, 24);
		break;
	case 3:
		_slotChoice = SLOT_4;
		_cursor = RectMake(40, WINSIZEY / 2 + 55, 31, 24);
		break;
	case 4:
		_slotChoice = SLOT_5;
		_cursor = RectMake(40, WINSIZEY / 2 + 90, 31, 24);
		break;
	case 5:
		_slotChoice = SLOT_6;
		_cursor = RectMake(40, WINSIZEY / 2 + 125, 31, 24);
		break;
	}

}