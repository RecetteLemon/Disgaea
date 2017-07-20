#include "stdafx.h"
#include "townInven.h"


townInven::townInven()
{
}


townInven::~townInven()
{
}

HRESULT townInven::init()
{
	_itemSlot = 1;
	_wareHouseSlot = 1;

	_itemNum1 = RectMake(500, 65, 20, 25);
	_itemNum10 = RectMake(480, 65, 20, 25);
	_wareHouseNum1 = RectMake(1100, 65, 20, 25);
	_wareHouseNum10 = RectMake(1080, 65, 20, 25);
	_wareHouseNum100 = RectMake(1060, 65, 20, 25);

	_itemCursor = RectMake(35, 120, 52, 39);

	_itemInfo = RectMake(50, 525, 1474, 340);

	_itemBag = RectMake(50, 35, 553, 480);
	_itemBagBlock = RectMake(556, 103, 40, 123);

	_wareHouse = RectMake(650, 35, 553, 480);
	_wareHouseBlock = RectMake(1157, 103, 40, 33);

	_itemMove = RectMake(1245, 320, 277, 190);

	for (int i = 0; i < 24; i++)
	{
		r_itemSlot[i] = RectMake(62, 103 + (i * 57), 474, 56);
	}



	_itemSlotUpMove = false;
	_itemSlotMoveUpCount = 0;

	_cursorNum = (TAGCURSORNUM)0;

	num = 0;

	_wareHouseCheck = false;



	return S_OK;
}

void townInven::release()
{

}

void townInven::update()
{
	if (!_wareHouseCheck && _cursorNum == 0) _itemCursor = RectMake(35, 120, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 1) _itemCursor = RectMake(35, 177, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 2) _itemCursor = RectMake(35, 234, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 3) _itemCursor = RectMake(35, 291, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 4) _itemCursor = RectMake(35, 348, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 5) _itemCursor = RectMake(35, 405, 52, 39);
	if (!_wareHouseCheck && _cursorNum == 6) _itemCursor = RectMake(35, 462, 52, 39);

	if (_wareHouseCheck && _cursorNum == 0) _itemCursor = RectMake(635, 120, 52, 39);
	if (_wareHouseCheck && _cursorNum == 1) _itemCursor = RectMake(635, 177, 52, 39);
	if (_wareHouseCheck && _cursorNum == 2) _itemCursor = RectMake(635, 234, 52, 39);
	if (_wareHouseCheck && _cursorNum == 3) _itemCursor = RectMake(635, 291, 52, 39);
	if (_wareHouseCheck && _cursorNum == 4) _itemCursor = RectMake(635, 348, 52, 39);
	if (_wareHouseCheck && _cursorNum == 5) _itemCursor = RectMake(635, 405, 52, 39);
	if (_wareHouseCheck && _cursorNum == 6) _itemCursor = RectMake(635, 462, 52, 39);

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (num > 0) num--;

		if (_cursorNum != 0)
		{
			_cursorNum = (TAGCURSORNUM)num;
		}

		//인벤토리 조작
		if (!_wareHouseCheck)
		{
			if (_itemSlot != 1)
			{
				_itemSlot--;
			}

			else if (_itemSlot == 1)
			{
				_itemSlot = 24;
				_cursorNum = (TAGCURSORNUM)6;
				num = 6;
			}
		}

		//창고 조작
		if (_wareHouseCheck)
		{
			if (_wareHouseSlot != 1)
			{
				_wareHouseSlot--;
			}

			else if (_wareHouseSlot == 1)
			{
				_wareHouseSlot = 512;
				_cursorNum = (TAGCURSORNUM)6;
				num = 6;
			}
		}

	}

	if (KEYMANAGER->isOnceKeyUp('W'))
	{

	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (num < 6) num++;
		if (_cursorNum != 6)
		{
			_cursorNum = (TAGCURSORNUM)num;
		}

		//인벤토리 조작
		if (!_wareHouseCheck)
		{
			if (_itemSlot != 24)
			{
				_itemSlot++;
			}

			else if (_itemSlot == 24)
			{
				_itemSlot = 1;
				_cursorNum = (TAGCURSORNUM)0;
				num = 0;
			}
		}

		//창고 조작
		if (_wareHouseCheck)
		{
			if (_wareHouseSlot != 512)
			{
				_wareHouseSlot++;
			}

			else if (_wareHouseSlot == 512)
			{
				_wareHouseSlot = 1;
				_cursorNum = (TAGCURSORNUM)0;
				num = 0;
			}
		}


	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_wareHouseCheck = false;
		//_itemSlot = _itemSlot + num;
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_wareHouseCheck = true;
	}




	slotMove();
}

void townInven::render()
{
	IMAGEMANAGER->findImage("아이템정보")->render(_itemInfo.left, _itemInfo.top);
	IMAGEMANAGER->findImage("마을인벤")->render(_itemBag.left, _itemBag.top);
	IMAGEMANAGER->findImage("마을인벤3")->render(_itemBagBlock.left, _itemBagBlock.top);
	IMAGEMANAGER->findImage("마을창고")->render(_wareHouse.left, _wareHouse.top);
	IMAGEMANAGER->findImage("마을창고3")->render(_wareHouseBlock.left, _wareHouseBlock.top);
	IMAGEMANAGER->findImage("마을인벤2")->render(_itemMove.left, _itemMove.top);


	//for (int i = 0; i < 7; i++)
	//{
	//	IMAGEMANAGER->findImage("none")->render(r_itemSlot[i].left, r_itemSlot[i].top);
	//}

	for (int i = 0; i < 7; i++)
	{
	}

	IMAGEMANAGER->findImage("커서")->render(_itemCursor.left, _itemCursor.top);

	WCHAR str[100];
	swprintf_s(str, L"커서넘버: %d", _cursorNum);
	DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 100, 300, 300);
	swprintf_s(str, L"슬롯넘버: %d", _itemSlot);
	DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 150, 300, 300);
	swprintf_s(str, L"창고넘버: %d", _wareHouseSlot);
	DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 200, 300, 300);
	swprintf_s(str, L"넘버: %d", num);
	DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 250, 300, 300);

	itemNumDraw();
}

void townInven::itemNumDraw()
{
	if (_wareHouseCheck)
	{

		//100단위
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 100) IMAGEMANAGER->findImage("1")->render(_wareHouseNum100.left, _wareHouseNum100.top);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 200) IMAGEMANAGER->findImage("2")->render(_wareHouseNum100.left, _wareHouseNum100.top);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 300) IMAGEMANAGER->findImage("3")->render(_wareHouseNum100.left, _wareHouseNum100.top);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 400) IMAGEMANAGER->findImage("4")->render(_wareHouseNum100.left, _wareHouseNum100.top);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 500) IMAGEMANAGER->findImage("5")->render(_wareHouseNum100.left, _wareHouseNum100.top);

		//10단위
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 0) IMAGEMANAGER->findImage("0")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 10) IMAGEMANAGER->findImage("1")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 20) IMAGEMANAGER->findImage("2")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 30) IMAGEMANAGER->findImage("3")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 40) IMAGEMANAGER->findImage("4")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 50) IMAGEMANAGER->findImage("5")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 60) IMAGEMANAGER->findImage("6")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 70) IMAGEMANAGER->findImage("7")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 80) IMAGEMANAGER->findImage("8")->render(_wareHouseNum10.left, _wareHouseNum10.top);
		if (_wareHouseSlot - (_wareHouseSlot % 10) == 90) IMAGEMANAGER->findImage("9")->render(_wareHouseNum10.left, _wareHouseNum10.top);

		//1단위
		if (_wareHouseSlot % 10 == 0) IMAGEMANAGER->findImage("0")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 1) IMAGEMANAGER->findImage("1")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 2) IMAGEMANAGER->findImage("2")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 3) IMAGEMANAGER->findImage("3")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 4) IMAGEMANAGER->findImage("4")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 5) IMAGEMANAGER->findImage("5")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 6) IMAGEMANAGER->findImage("6")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 7) IMAGEMANAGER->findImage("7")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 8) IMAGEMANAGER->findImage("8")->render(_wareHouseNum1.left, _wareHouseNum1.top);
		if (_wareHouseSlot % 10 == 9) IMAGEMANAGER->findImage("9")->render(_wareHouseNum1.left, _wareHouseNum1.top);



	}

	if (!_wareHouseCheck)
	{
		if (_itemSlot > 9 && _itemSlot < 20) IMAGEMANAGER->findImage("1")->render(_itemNum10.left, _itemNum10.top);
		if (_itemSlot > 19 && _itemSlot < 25) IMAGEMANAGER->findImage("2")->render(_itemNum10.left, _itemNum10.top);
		if (_itemSlot % 10 == 0) IMAGEMANAGER->findImage("0")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 1) IMAGEMANAGER->findImage("1")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 2) IMAGEMANAGER->findImage("2")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 3) IMAGEMANAGER->findImage("3")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 4) IMAGEMANAGER->findImage("4")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 5) IMAGEMANAGER->findImage("5")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 6) IMAGEMANAGER->findImage("6")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 7) IMAGEMANAGER->findImage("7")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 8) IMAGEMANAGER->findImage("8")->render(_itemNum1.left, _itemNum1.top);
		if (_itemSlot % 10 == 9) IMAGEMANAGER->findImage("9")->render(_itemNum1.left, _itemNum1.top);
	}

	//Rectangle(getMemDC(), _itemNum1.left, _itemNum1.top, _itemNum1.right, _itemNum1.bottom);
	//Rectangle(getMemDC(), _itemNum10.left, _itemNum10.top, _itemNum10.right, _itemNum10.bottom);
}

void townInven::slotMove()
{

}