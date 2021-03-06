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

	_itemSlot = 0;
	_wareHouseSlot = 0;

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
	for (int i = 0; i < 512; i++)
	{
		r_wareSlot[i] = RectMake(_wareHouse.left + 13, 103 + (i * 57), 474, 56);
	}


	_itemSlotUpMove = false;
	_itemSlotMoveUpCount = 0;

	_cursorNum = (TAGCURSORNUM)0;

	num = 0;
	_test = 0;
	_wareHouseCheck = false;

	_tagItemStat = ITEM_WEAPON;

	_swap = false;

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
			if (_itemSlot != 0)
			{
				_itemSlot--;
			}

			else if (_itemSlot == 0)
			{
				_itemSlot = 23;
				_cursorNum = (TAGCURSORNUM)6;
				num = 6;
			}
		}

		//창고 조작
		if (_wareHouseCheck)
		{
			if (_wareHouseSlot != 0)
			{
				_wareHouseSlot--;
			}

			else if (_wareHouseSlot == 0)
			{
				_wareHouseSlot = 512;
				_cursorNum = (TAGCURSORNUM)6;
				num = 6;
			}
		}

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
			if (_itemSlot != 23)
			{
				_itemSlot++;
			}

			else if (_itemSlot == 23)
			{
				_itemSlot = 0;
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
				_wareHouseSlot = 0;
				_cursorNum = (TAGCURSORNUM)0;
				num = 0;
			}
		}


	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_wareHouseCheck = false;
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_wareHouseCheck = true;
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SCENEMANAGER->changeScene(L"MenuScene");
	}
	//아이템 스왑용
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		sortItem();
		switch (_tagItemStat)
		{
		case 0:
			_tagItemStat = ITEM_ARMOR;
			break;
		case 1:
			_tagItemStat = ITEM_POTION;
			break;
		case 2:
			_tagItemStat = ITEM_WEAPON;
			break;
		}
	}
	//아이템 보내기
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		//스왑온
		for (int i = _test; i < _test + 7; i++)
		{
			if (i_itemSlot[i] != IMAGEMANAGER->findImage(L"none") || i_wareSlot[i] != IMAGEMANAGER->findImage(L"none"))
			{
				if (!_swap) _swap = true;
			}
		}
		//스왑온이면 스왑 진행
		if (_swap) SendItem();
	}

	slotMove();
}

void townInven::render()
{
	IMAGEMANAGER->findImage(L"backBlack")->render(_itemInfo.left, _itemInfo.top, false, 0.4f);
	IMAGEMANAGER->findImage(L"아이템정보")->render(_itemInfo.left, _itemInfo.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"마을인벤")->render(_itemBag.left, _itemBag.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"마을인벤3")->render(_itemBagBlock.left, _itemBagBlock.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"마을창고")->render(_wareHouse.left, _wareHouse.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"마을창고3")->render(_wareHouseBlock.left, _wareHouseBlock.top, false, 1.0f);

	if (_wareHouseCheck)
	{
		IMAGEMANAGER->findImage(L"마을창고2")->render(_itemMove.left, _itemMove.top, false, 1.0f);
	}
	else if (!_wareHouseCheck)
	{
		IMAGEMANAGER->findImage(L"마을인벤2")->render(_itemMove.left, _itemMove.top, false, 1.0f);
	}

	//인벤
	for (int i = _test; i < _test + 7; i++)
	{
		if (INVENMANAGER->getVItem().size() == 0)
		{
			i_itemSlot[i] = IMAGEMANAGER->findImage(L"none");
		}
		else
		{
			if (INVENMANAGER->getVItem().size() > i)
			{
				i_itemSlot[i] = INVENMANAGER->getVItem()[i].Image;
			}
			else if (INVENMANAGER->getVItem().size() <= i)
			{
				i_itemSlot[i] = IMAGEMANAGER->findImage(L"none");
			}
		}
		i_itemSlot[i]->render(r_itemSlot[i].left, r_itemSlot[i].top, false, 1.0f);
	}
	//창고 관련
	for (int i = _test; i < _test + 7; i++)
	{
		if (INVENMANAGER->getVWareHouse().size() == 0)
		{
			i_wareSlot[i] = IMAGEMANAGER->findImage(L"none");
		}
		else
		{
			if (INVENMANAGER->getVWareHouse().size() > i)
			{
				i_wareSlot[i] = INVENMANAGER->getVWareHouse()[i].Image;
			}
			else if (INVENMANAGER->getVWareHouse().size() <= i)
			{
				i_wareSlot[i] = IMAGEMANAGER->findImage(L"none");
			}
		}
		i_wareSlot[i]->render(r_wareSlot[i].left, r_wareSlot[i].top, false, 1.0f);
	}

	IMAGEMANAGER->findImage(L"커서")->render(_itemCursor.left, _itemCursor.top, false, 1.0f);

	WCHAR str[100];
	//swprintf_s(str, L"커서넘버: %d", _cursorNum);
	//DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 100, 300, 300);
	//swprintf_s(str, L"슬롯넘버: %d", _itemSlot);
	//DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 150, 300, 300);
	//swprintf_s(str, L"창고넘버: %d", _wareHouseSlot);
	//DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 200, 300, 300);
	//swprintf_s(str, L"넘버: %d", num);
	//DIRECT2D->DrawTextD2D(DIRECT2D->_defaultBrush, str, 100, 250, 300, 300);

	itemNumDraw();
}

void townInven::itemNumDraw()
{
	if (_wareHouseCheck)
	{

		//100단위
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 100) IMAGEMANAGER->findImage(L"1")->render(_wareHouseNum100.left, _wareHouseNum100.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 200) IMAGEMANAGER->findImage(L"2")->render(_wareHouseNum100.left, _wareHouseNum100.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 300) IMAGEMANAGER->findImage(L"3")->render(_wareHouseNum100.left, _wareHouseNum100.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 400) IMAGEMANAGER->findImage(L"4")->render(_wareHouseNum100.left, _wareHouseNum100.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 100) == 500) IMAGEMANAGER->findImage(L"5")->render(_wareHouseNum100.left, _wareHouseNum100.top, false, 1.0f);

		//10단위 (수정하즈아)
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 0) IMAGEMANAGER->findImage(L"0")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 10) IMAGEMANAGER->findImage(L"1")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 20) IMAGEMANAGER->findImage(L"2")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 30) IMAGEMANAGER->findImage(L"3")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 40) IMAGEMANAGER->findImage(L"4")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 50) IMAGEMANAGER->findImage(L"5")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 60) IMAGEMANAGER->findImage(L"6")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 70) IMAGEMANAGER->findImage(L"7")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 80) IMAGEMANAGER->findImage(L"8")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);
		if (_wareHouseSlot - (_wareHouseSlot % 10 + 1) == 90) IMAGEMANAGER->findImage(L"9")->render(_wareHouseNum10.left, _wareHouseNum10.top, false, 1.0f);

		//1단위
		if (_wareHouseSlot % 10 == 0) IMAGEMANAGER->findImage(L"1")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 1) IMAGEMANAGER->findImage(L"2")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 2) IMAGEMANAGER->findImage(L"3")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 3) IMAGEMANAGER->findImage(L"4")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 4) IMAGEMANAGER->findImage(L"5")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 5) IMAGEMANAGER->findImage(L"6")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 6) IMAGEMANAGER->findImage(L"7")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 7) IMAGEMANAGER->findImage(L"8")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 8) IMAGEMANAGER->findImage(L"9")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);
		if (_wareHouseSlot % 10 == 9) IMAGEMANAGER->findImage(L"0")->render(_wareHouseNum1.left, _wareHouseNum1.top, false, 1.0f);



	}

	if (!_wareHouseCheck)
	{
		if (_itemSlot > 8 && _itemSlot < 19) IMAGEMANAGER->findImage(L"1")->render(_itemNum10.left, _itemNum10.top, false, 1.0f);
		if (_itemSlot > 18 && _itemSlot < 24) IMAGEMANAGER->findImage(L"2")->render(_itemNum10.left, _itemNum10.top, false, 1.0f);
		if (_itemSlot % 10 == 0) IMAGEMANAGER->findImage(L"1")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 1) IMAGEMANAGER->findImage(L"2")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 2) IMAGEMANAGER->findImage(L"3")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 3) IMAGEMANAGER->findImage(L"4")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 4) IMAGEMANAGER->findImage(L"5")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 5) IMAGEMANAGER->findImage(L"6")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 6) IMAGEMANAGER->findImage(L"7")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 7) IMAGEMANAGER->findImage(L"8")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 8) IMAGEMANAGER->findImage(L"9")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
		if (_itemSlot % 10 == 9) IMAGEMANAGER->findImage(L"0")->render(_itemNum1.left, _itemNum1.top, false, 1.0f);
	}
}

void townInven::slotMove()
{
	if (_itemSlot == 0)
	{
		_test = 0;

		for (int i = _test; i < _test + 7; i++)
		{
			r_itemSlot[i] = RectMake(62, 103 + (57 * i), 474, 56);
		}
	}

	if (_itemSlot >= 6)
	{
		_test = _itemSlot - 6;

		for (int i = _test; i < _test + 7; i++)
		{
			r_itemSlot[i] = RectMake(62, 103 + (57 * (i - _test)), 474, 56);
		}
	}

}
//아이템 정렬
void townInven::sortItem()
{
	switch (_tagItemStat)
	{
	case 0:
		_vTemp.swap(INVENMANAGER->getVItem());
		INVENMANAGER->clearVItem();
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == WEAPON) INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == ARMOR)INVENMANAGER->pushBackVItem(i, _vTemp);
			else if (_vTemp[i].Type == GENERAL)INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		_vTemp.clear();
		break;
	case 1:
		_vTemp.swap(INVENMANAGER->getVItem());
		INVENMANAGER->clearVItem();
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == ARMOR) INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == GENERAL)INVENMANAGER->pushBackVItem(i, _vTemp);
			else if (_vTemp[i].Type == WEAPON)INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		_vTemp.clear();
		break;
	case 2:
		_vTemp.swap(INVENMANAGER->getVItem());
		INVENMANAGER->clearVItem();
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == GENERAL) INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		for (int i = 0; i < _vTemp.size(); i++)
		{
			if (_vTemp[i].Type == ARMOR)INVENMANAGER->pushBackVItem(i, _vTemp);
			else if (_vTemp[i].Type == WEAPON)INVENMANAGER->pushBackVItem(i, _vTemp);
		}
		_vTemp.clear();
		break;
	}
}
//아이템 인벤에서 창고로 또는 창고에서 인벤으로
void townInven::SendItem()
{
	switch (_wareHouseCheck)
	{
		//인벤창 일 때
	case 0:
		//인벤 안에 템이 한개 있을때
		if (INVENMANAGER->getVItem().size() == 1)
		{
			INVENMANAGER->pushBackWareHouse(0, INVENMANAGER->getVItem());
			INVENMANAGER->erase2VItem(0);
			_swap = false;
		}
		//여러개 있을때
		else if (INVENMANAGER->getVItem().size() > 1)
		{
			if (_itemSlot == INVENMANAGER->getVItem().size() - 1)
			{
				INVENMANAGER->pushBackWareHouse(_itemSlot, INVENMANAGER->getVItem());
				INVENMANAGER->erase2VItem(_itemSlot);
				_swap = false;
			}
			else if (_itemSlot < INVENMANAGER->getVItem().size() - 1)
			{
				INVENMANAGER->pushBackWareHouse(_itemSlot, INVENMANAGER->getVItem());
				for (int i = _itemSlot + 1; i < INVENMANAGER->getVItem().size(); i++)
				{
					_vTemp.push_back(INVENMANAGER->getVItem()[i]);
				}
				INVENMANAGER->eraseVItem(_itemSlot);
				for (int i = 0; i < _vTemp.size(); i++)
				{
					INVENMANAGER->pushBackVItem(i, _vTemp);
				}
				_vTemp.clear();
				_swap = false;
			}
		}
		break;
		//창고창 일 때
	case 1:
		//창고 안에 템이 한개 있을때
		if (INVENMANAGER->getVWareHouse().size() == 1)
		{
			INVENMANAGER->pushBackVItem(0, INVENMANAGER->getVWareHouse());
			INVENMANAGER->eraseWareHouse(0);
			_swap = false;
		}
		//여러개 있을때
		else if (INVENMANAGER->getVWareHouse().size() > 1)
		{
			if (_itemSlot == INVENMANAGER->getVWareHouse().size() - 1)
			{
				INVENMANAGER->pushBackVItem(_itemSlot, INVENMANAGER->getVWareHouse());
				INVENMANAGER->eraseWareHouse(_itemSlot);
				_swap = false;
			}
			else if (_itemSlot < INVENMANAGER->getVWareHouse().size() - 1)
			{
				INVENMANAGER->pushBackVItem(_itemSlot, INVENMANAGER->getVWareHouse());
				for (int i = _itemSlot + 1; i < INVENMANAGER->getVWareHouse().size(); i++)
				{
					_vTemp.push_back(INVENMANAGER->getVWareHouse()[i]);
				}
				INVENMANAGER->eraseWareHouse2(_itemSlot);
				for (int i = 0; i < _vTemp.size(); i++)
				{
					INVENMANAGER->pushBackWareHouse(i, _vTemp);
				}
				_vTemp.clear();
				_swap = false;
			}
		}
		break;
	}
}