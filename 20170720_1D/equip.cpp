#include "stdafx.h"
#include "equip.h"


equip::equip()
{
}


equip::~equip()
{
}

HRESULT equip::init()
{
	//기본틀
	_statBox = RectMake(0, 10, 1600, 300);
	_invenBox = RectMake(61, 315, 553, 480);
	_itemBox = RectMake(_invenBox.right + 20, 535, 677, 253);
	_sort = RectMake(_itemBox.right - 100, 315,374, 203);
	//
	_slotNum = ESLOT_1;
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_invenBox.left + 12, _invenBox.top + 76 +(67 * i) , 474,56);
	}
	for (int i = 0; i < 4; i++)
	{
		_equipSlot[i] = RectMake(WINSIZEX - 619, 30 + (59 * i), 564, 54);
	}
	_cursor = RectMakeCenter(_slot[0].left - 4, (_slot[0].bottom - _slot[0].top) / 2 + _slot[0].top, 52, 39);
	_slotCount = _num = _tempNum = 0;
	_infoOn = false;

	_state = INVEN;

	return S_OK;
}

void equip::release()
{
}

void equip::update()
{
	cursorMove();
	slotMove();
	itemInfo();
}

void equip::render()
{
	IMAGEMANAGER->findImage(L"StatUI")->render(_statBox.left, _statBox.top, false, 0.4f);
	IMAGEMANAGER->findImage(L"StatUI1")->render(_statBox.left, _statBox.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"weapon")->render(_equipSlot[0].left, _equipSlot[0].top, false, 1.0f);
	IMAGEMANAGER->findImage(L"other")->render(_equipSlot[1].left, _equipSlot[1].top, false, 1.0f);
	IMAGEMANAGER->findImage(L"other")->render(_equipSlot[2].left, _equipSlot[2].top, false, 1.0f);
	IMAGEMANAGER->findImage(L"other")->render(_equipSlot[3].left, _equipSlot[3].top, false, 1.0f);
	//if()
	IMAGEMANAGER->findImage(L"itemBag")->render(_invenBox.left, _invenBox.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"equipSort")->frameRender(_sort.left, _sort.top, 0, 0, false, 1.0f);
	for (int i = _slotCount; i < _slotCount + 6; i++)
	{
		if (INVENMANAGER->getVItem().size() == 0)
		{
			i_slot[i] = IMAGEMANAGER->findImage(L"none");
			i_slot[i]->render(_slot[i].left, _slot[i].top, false, 1.0f);
		}
		else
		{
			if (INVENMANAGER->getVItem().size() > i)
			{
				i_slot[i] = INVENMANAGER->getVItem()[i].Image;
				if(INVENMANAGER->getVItem()[i].Type == GENERAL) i_slot[i]->render(_slot[i].left, _slot[i].top, false, 0.4f);
				else i_slot[i]->render(_slot[i].left, _slot[i].top, false, 1.0f);
			}
			else if (INVENMANAGER->getVItem().size() <= i)
			{
				i_slot[i] = IMAGEMANAGER->findImage(L"none");
				i_slot[i]->render(_slot[i].left, _slot[i].top, false, 1.0f);
			}
		}
	}
	if (_infoOn)
	{
		IMAGEMANAGER->findImage(L"miniBlack")->render(_itemBox.left, _itemBox.top, false, 0.4f);
		IMAGEMANAGER->findImage(L"miniInfo")->render(_itemBox.left, _itemBox.top, false, 1.0f);
		IMAGEMANAGER->findImage(L"infoBox")->render(61, _invenBox.bottom + 20, false, 1.0f);
		INVENMANAGER->getVItem()[_tempNum + _num].info->render(61 + 13, _invenBox.bottom + 20 + 7, false, 1.0f);
		INVENMANAGER->getVItem()[_tempNum + _num].Image2->render(_itemBox.left + 7, _itemBox.top + 10, false, 1.0f);
	}
	IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);
}

void equip::cursorMove()
{
	if (_state == INVEN)
	{
		switch (_slotNum)
		{
		case 0:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2, 52, 39);
			break;
		case 1:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2 + (67 * 1), 52, 39);
			break;
		case 2:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2 + (67 * 2), 52, 39);
			break;
		case 3:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2 + (67 * 3), 52, 39);
			break;
		case 4:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2 + (67 * 4), 52, 39);
			break;
		case 5:
			_cursor = RectMakeCenter(_slot[0].left - 4, _invenBox.top + 76 + 56 / 2 + (67 * 5), 52, 39);
			break;
		}
	}
	else
	{

	}
}
void equip::slotMove()
{
	if (_slotNum == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_slotCount--;
			if (_slotCount < 0)
			{
				_num = 5;
				_slotCount = 18;
			}
			else _num = 0;
			_slotNum = (EQUIP_SLOT)_num;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_num--;
			_slotNum = (EQUIP_SLOT)_num;
		}
	}

	if (_slotNum == 5)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_slotCount++;
			if (_slotCount > 18)
			{
				_num = 0;
				_slotCount = 0;
			}
			else _num = 5;
			_slotNum = (EQUIP_SLOT)_num;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_num++;
			_slotNum = (EQUIP_SLOT)_num;
		}
	}
	//인벤 슬롯
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_invenBox.left + 12, _invenBox.top + 76 + (67 * (i- _slotCount)), 474, 56);
	}
}

void equip::itemInfo()
{
	RECT tempRC;
	if (IntersectRect(&tempRC, &RectMake(_cursor.left - 20, _cursor.top + 10, _cursor.right + 20, _cursor.bottom - 10), &_slot[_slotCount + (int)_slotNum]))
	{
		if (i_slot[_tempNum + _num] != IMAGEMANAGER->findImage(L"none"))  _infoOn = true;
		else _infoOn = false;
	}
	if(INVENMANAGER->getVItem().size() == 0) _infoOn = false;
}