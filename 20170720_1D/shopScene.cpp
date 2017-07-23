#include "stdafx.h"
#include "shopScene.h"

shopScene::shopScene()
{
}

shopScene::~shopScene()
{
}

HRESULT shopScene::init()
{
	//�÷��̾� �ʱⰪ
	_playerMoney = STATMANAGER->getMoney();
	//������ �ʱⰪ
	_page = SHOP_MAIN;
	//������ ��������
	_item = new item;
	_item->init();

	_menu = SELECT_BUY;
	_sellType = TYPE_INVEN;
	_buySlot = BUY_SLOT_1;
	_sellSlot = SELL_SLOT_1;
	_buySlotNum = _sellSlotNum = 0;
	_changeNum = 0;
	_menuInfo = IMAGEMANAGER->findImage(L"buyInfo");
	//�κ��� �ʱ�ȭ
	for (int i = 0; i < 24; i++)
	{
		_invenSImage[i] = IMAGEMANAGER->findImage(L"noneShop");
	}
	_togle = false;
	_isBuyInfo = _isBuying = _isSelling = _isSellInfo = false;

	_sortNum = 0;

	return S_OK;
}
void shopScene::release()
{


}
void shopScene::update()
{
	//������ ��ȯ
	pageChange();
	if (KEYMANAGER->isOnceKeyDown('P')) SCENEMANAGER->changeScene(L"TownScene");

}
void shopScene::render()
{
	WCHAR str[128];

	switch (_page)
	{
		//����
	case 0:
		IMAGEMANAGER->findImage(L"shopMain")->render(0, 0, false, 1.0f);
		IMAGEMANAGER->findImage(L"buy")->render(_buy.left, _buy.top, false, 1.0f);
		IMAGEMANAGER->findImage(L"sell")->render(_sell.left, _sell.top, false, 1.0f);
		IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);
		_menuInfo->render(77, WINSIZEY - 109, false, 1.0f);

		swprintf_s(str, L"%d", _playerMoney);
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, WINSIZEX - 276, 701, WINSIZEX - 77, 761);

		break;
		//����
	case 1:
		IMAGEMANAGER->findImage(L"shopBuy")->render(0, 0, false, 1.0f);
		IMAGEMANAGER->findImage(L"moveBar")->render(_bar.left, _bar.top, false, 1.0f);
		//��ó���� ���̴� ������ 8�� �װ͸� ������
		for (int i = _changeNum; i < 8 + _changeNum; i++)
		{
			//���� �������� �� �̹����� ����
			if (_item->getVItem().size() == 0)
			{
				i_slot[i] = IMAGEMANAGER->findImage(L"noneShop");
			}
			//���Ͱ��� ������ 
			else
			{
				//�ִ� �迭 ���������� �������� �̹����� �־��ش�
				if (_item->getVItem().size() > i)
				{
					i_slot[i] = _item->getVItem()[i].priceImage;
				}
				//���� �迭���� �� �̹����� �־��ش�
				else if (_item->getVItem().size() <= i)
				{
					i_slot[i] = IMAGEMANAGER->findImage(L"noneShop");
				}

			}
			i_slot[i]->render(_slot[i].left, _slot[i].top, false, 1.0f);
			//Ŀ�� �̹���
			IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);
			//�����̹��� ���
			if (_isBuyInfo)
			{
				IMAGEMANAGER->findImage(L"infoBox")->render(63, WINSIZEY - 117, false, 1.0f);
				_infoImage->render(76, WINSIZEY - 110, false, 1.0f);
				IMAGEMANAGER->findImage(L"backBlack")->render(63, 523, false, 0.1f);
				IMAGEMANAGER->findImage(L"itemStat")->render(63, 523, false, 1.0f);
				_infoImage2->render(69, 532, false, 1.0f);
			}
			//����� ����� �� ���
			if (_isBuying)
			{
				IMAGEMANAGER->findImage(L"buyMessage")->render(WINSIZEX - 603, 233, false, 1.0f);
				_item->getVItem()[_changeNum + (int)_buySlot].Image->render(WINSIZEX - 590, 246, false, 1.0f);
			}
		}
		swprintf_s(str, L"%d", _playerMoney);
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, WINSIZEX - 280, 443, WINSIZEX - 77, 503);
		break;
		//�Ǹ�
	case 2:
		IMAGEMANAGER->findImage(L"shopSell")->frameRender(0, 0, 0, _togle, false, 1.0f);
		IMAGEMANAGER->findImage(L"sellSort")->frameRender(1257, 180, !_togle, _sortNum, false, 1.0f);
		IMAGEMANAGER->findImage(L"moveBar")->render(_bar.left, _bar.top, false, 1.0f);
		switch (_sellType)
		{
		case TYPE_INVEN:
			for (int i = _changeNum; i < 7 + _changeNum; i++)
			{
				_invenSImage[i]->render(_invenSlot[i].left, _invenSlot[i].top, false, 1.0f);
			}
			break;
		case TYPE_WAREHOUSE:
			for (int i = 0; i < 7; i++)
			{
				IMAGEMANAGER->findImage(L"noneShop")->render(_wareHouseSlot[i].left, _wareHouseSlot[i].top, false, 1.0f);
			}
			break;
		}
		//Ŀ�� �̹���
		IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);
		if (_isSelling)
		{
			IMAGEMANAGER->findImage(L"sellMessage")->render(WINSIZEX - 553, -3, false, 1.0f);
			_item->getVItem()[_changeNum + (int)_sellSlot].Image->render(WINSIZEX - 541, 253, false, 1.0f);
		}
		//�����̹��� ���
		if (_isSellInfo)
		{
			IMAGEMANAGER->findImage(L"infoBox")->render(63, WINSIZEY - 117, false, 1.0f);
			_infoImage->render(76, WINSIZEY - 110, false, 1.0f);
		}
		swprintf_s(str, L"%d", _playerMoney);
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, WINSIZEX - 280, 450, WINSIZEX - 77, 510);
		break;
	}
}
//������ ��ȯ
void shopScene::pageChange()
{
	switch (_page)
	{
	case 0:
		mainPage();
		break;
	case 1:
		buyPage();
		break;
	case 2:
		sellPage();
		break;
	}
}
//���� ���� ������
void shopScene::mainPage()
{
	_buy = RectMake(613, 278 + 29, 374, 44);
	_sell = RectMake(613, _buy.bottom + 29, 374, 44);
	//���� �����̱�
	if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('S'))
	{
		if (_menu == SELECT_BUY) _menu = SELECT_SELL;
		else if (_menu == SELECT_SELL) _menu = SELECT_BUY;
	}
	switch (_menu)
	{
	case SELECT_BUY:
		_cursor = RectMake(613 - 35, (_buy.bottom - _buy.top) / 2 + _buy.top - 20, 52, 39);
		_menuInfo = IMAGEMANAGER->findImage(L"buyInfo");
		if (KEYMANAGER->isOnceKeyDown('K'))_page = SHOP_BUY;
		break;
	case SELECT_SELL:
		_cursor = RectMake(613 - 35, (_buy.bottom - _buy.top) / 2 + _buy.top - 20 + 29 + 44, 52, 39);
		_menuInfo = IMAGEMANAGER->findImage(L"sellInfo");
		if (KEYMANAGER->isOnceKeyDown('K'))_page = SHOP_SELL;
		break;
	}
}
//���� ���� ������
void shopScene::buyPage()
{
	if (!_isBuying)
	{
		//�ڷΰ��� ��ư
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			_page = SHOP_MAIN;
			_changeNum = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('K')) if (i_slot[_changeNum + (int)_buySlot] != IMAGEMANAGER->findImage(L"noneShop")) _isBuying = true;
	}
	else if (_isBuying)
	{
		if (KEYMANAGER->isOnceKeyDown('L')) _isBuying = false;
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			//���� �Ǹ�
			if (_item->getVItem()[_changeNum + (int)_buySlot].Price <= _playerMoney)
			{
				buyingItem();
				STATMANAGER->setMoney(_playerMoney - _item->getVItem()[_changeNum + (int)_buySlot].Price);
				_playerMoney = STATMANAGER->getMoney();
			}
			//�ȵǸ� ����¡
			if (_item->getVItem()[_changeNum + (int)_buySlot].Price > _playerMoney) _isBuying = false;
		}
	}
	//���� �����
	for (int i = 0; i < 11; i++)
	{
		switch (_changeNum)
		{
		case 0:
			_slot[i] = RectMake(76, 47 + (56 * i), 833, 56);
			_bar = RectMake(917, 40, 40, 123);
			if (i > 8) continue;
			break;
		case 1:
			_slot[i] = RectMake(76, 47 + (56 * (i - 1)), 833, 56);
			_bar = RectMake(917, 155, 40, 123);
			if (i > 9) continue;
			break;
		case 2:
			_slot[i] = RectMake(76, 47 + (56 * (i - 2)), 833, 56);
			_bar = RectMake(917, 270, 40, 123);
			if (i > 10) continue;
			break;
		case 3:
			_slot[i] = RectMake(76, 47 + (56 * (i - 3)), 833, 56);
			_bar = RectMake(917, 385, 40, 123);
			break;
		}

	}
	//��, �Ʒ� ��ư
	if (_buySlot == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_changeNum--;
			if (_changeNum < 0)
			{
				_buySlotNum = 7;
				_changeNum = 3;
			}
			else _buySlotNum = 0;
			_buySlot = (BUYSLOT)_buySlotNum;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_buySlotNum--;
			_buySlot = (BUYSLOT)_buySlotNum;
		}
	}
	if (_buySlot == 7)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_changeNum++;
			if (_changeNum > 3)
			{
				_buySlotNum = 0;
				_changeNum = 0;
			}
			else _buySlotNum = 7;
			_buySlot = (BUYSLOT)_buySlotNum;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_buySlotNum++;
			_buySlot = (BUYSLOT)_buySlotNum;
		}
	}

	//���� �̹��� �������ϴ� ����
	RECT tempRC;
	if (IntersectRect(&tempRC, &RectMake(_cursor.left - 20, _cursor.top + 10, _cursor.right + 10, _cursor.bottom - 20), &_slot[_changeNum + (int)_buySlot]))
	{
		if (i_slot[_changeNum + (int)_buySlot] != IMAGEMANAGER->findImage(L"noneShop"))
		{
			_isBuyInfo = true;
			_infoImage = _item->getVItem()[_changeNum + (int)_buySlot].info;
			_infoImage2 = _item->getVItem()[_changeNum + (int)_buySlot].Image2;
		}
		else _isBuyInfo = false;
	}

	//���� ���� Ŀ�� ��ġ
	switch (_buySlot)
	{
	case 0:
		_cursor = RectMake(_slot[0].left - 27, 47, 52, 39);
		break;
	case 1:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56, 52, 39);
		break;
	case 2:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 2, 52, 39);
		break;
	case 3:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 3, 52, 39);
		break;
	case 4:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 4, 52, 39);
		break;
	case 5:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 5, 52, 39);
		break;
	case 6:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 6, 52, 39);
		break;
	case 7:
		_cursor = RectMake(_slot[0].left - 27, 47 + 56 * 7, 52, 39);
		break;
	}
}
//���� �Ǹ� ������
void shopScene::sellPage()
{
	//�Ȱ����� ����
	if (!_isSelling)
	{
		//�ڷΰ��� ��ư
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			_page = SHOP_MAIN;
			_changeNum = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (_invenSImage[_changeNum + (int)_sellSlot] != IMAGEMANAGER->findImage(L"noneShop")) _isSelling = true;
			else _isSelling = false;
		}
	}
	if (_isSelling)
	{
		if (KEYMANAGER->isOnceKeyDown('L')) _isSelling = false;
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			sellingItem();
			_isSelling = false;
		}
	}
	//â��� �κ� ����
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_togle)
		{
			_togle = false;
			_sellType = TYPE_INVEN;
		}
		else if (!_togle)
		{
			_togle = true;
			_sellType = TYPE_WAREHOUSE;
		}
	}

	//���º� ������ ��ġ ����
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_sortNum++;
		if (_sortNum > 2) _sortNum = 0;

		switch (_sortNum)
		{
		case 0:
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
		case 1:
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
		case 2:
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
		}
		//�̹��� �ֽ�ȭ
		for (int i = 0; i < 24; i++)
		{
			//�ִ� �迭 ���������� �������� �̹����� �־��ش�
			if (INVENMANAGER->getVItem().size() > i)
			{
				_invenSImage[i] = INVENMANAGER->getVItem()[i].priceImage;
			}
			//���� �迭���� �� �̹����� �־��ش�
			else if (INVENMANAGER->getVItem().size() <= i)
			{
				_invenSImage[i] = IMAGEMANAGER->findImage(L"noneShop");
			}
		}
	}
	//�κ� ����
	for (int i = 0; i < 24; i++)
	{
		//â�� ������ �������� ����
		switch (_changeNum)
		{
		case 0:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * i), 834, 56);

			if (i > 7) continue;
			break;
		case 1:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 1)), 834, 56);
			if (i > 8) continue;
			break;
		case 2:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 2)), 834, 56);
			if (i > 9) continue;
			break;
		case 3:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 3)), 834, 56);
			break;
		case 4:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 4)), 834, 56);
			break;
		case 5:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 5)), 834, 56);
			break;
		case 6:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 6)), 834, 56);
			break;
		case 7:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 7)), 834, 56);
			break;
		case 8:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 8)), 834, 56);
			break;
		case 9:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 9)), 834, 56);
			break;
		case 10:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 10)), 834, 56);
			break;
		case 11:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 11)), 834, 56);
			break;
		case 12:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 12)), 834, 56);
			break;
		case 13:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 13)), 834, 56);
			break;
		case 14:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 14)), 834, 56);
			break;
		case 15:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 15)), 834, 56);
			break;
		case 16:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 16)), 834, 56);
			break;
		case 17:
			_invenSlot[i] = RectMake(76, 104 + 2 + (58 * (i - 17)), 834, 56);
			break;
		}

	}
	_bar = RectMake(927, 104 + (17 * _changeNum), 40, 123);
	//â�� ����
	for (int i = 0; i < 100; i++)
	{
		_wareHouseSlot[i] = RectMake(76, 104 + 2 + (58 * i), 834, 56);
	}

	//��, �Ʒ� ��ư
	if (_sellSlot == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_changeNum--;
			if (_changeNum < 0)
			{
				_sellSlotNum = 6;
				_changeNum = 17;
			}
			else _sellSlotNum = 0;
			_sellSlot = (SELLSLOT)_sellSlotNum;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_sellSlotNum--;
			_sellSlot = (SELLSLOT)_sellSlotNum;
		}
	}

	if (_sellSlot == 6)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_changeNum++;
			if (_changeNum > 17)
			{
				_sellSlotNum = 0;
				_changeNum = 0;
			}
			else _sellSlotNum = 6;
			_sellSlot = (SELLSLOT)_sellSlotNum;
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_sellSlotNum++;
			_sellSlot = (SELLSLOT)_sellSlotNum;
		}
	}

	//���� �̹��� �������ϴ� ����
	RECT tempRC;
	if (IntersectRect(&tempRC, &RectMake(_cursor.left - 20, _cursor.top + 10, _cursor.right + 10, _cursor.bottom - 20), &_invenSlot[_changeNum + (int)_sellSlot]))
	{
		if (_invenSImage[_changeNum + (int)_sellSlot] != IMAGEMANAGER->findImage(L"noneShop"))
		{
			_isSellInfo = true;
			_infoImage = INVENMANAGER->getVItem()[_changeNum + (int)_sellSlot].info;
		}
		else _isSellInfo = false;
	}

	//���Դ� Ŀ��
	switch (_sellSlot)
	{
	case 0:
		_cursor = RectMake(_invenSlot[0].left - 27, 104, 52, 39);
		break;
	case 1:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60, 52, 39);
		break;
	case 2:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60 * 2, 52, 39);
		break;
	case 3:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60 * 3, 52, 39);
		break;
	case 4:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60 * 4, 52, 39);
		break;
	case 5:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60 * 5, 52, 39);
		break;
	case 6:
		_cursor = RectMake(_invenSlot[0].left - 27, 104 + 60 * 6, 52, 39);
		break;
	}
}

void shopScene::buyingItem()
{
	//�κ� ĭ�� ������ â��� �������� ��
	if (INVENMANAGER->getVItem().size() > 24)
	{
		_vWareHouse.push_back(_item->getVItem()[_changeNum + (int)_buySlot]);
	}
	//�κ�ĭ ������ ���������� �κ����� �������� �־��ش�
	else
	{
		INVENMANAGER->pushBackVItem(_changeNum + (int)_buySlot, _item->getVItem());//.push_back(_item->getVItem()[_changeNum + (int)_buySlot]);
	}
	for (int i = 0; i < 24; i++)
	{
		//�ִ� �迭 ���������� �������� �̹����� �־��ش�
		if (INVENMANAGER->getVItem().size() > i)
		{
			_invenSImage[i] = INVENMANAGER->getVItem()[i].priceImage;
		}
		//���� �迭���� �� �̹����� �־��ش�
		else if (INVENMANAGER->getVItem().size() <= i)
		{
			_invenSImage[i] = IMAGEMANAGER->findImage(L"noneShop");
		}
	}
	_item->sellItem(_changeNum + (int)_buySlot);
	_isBuying = false;
}

void shopScene::sellingItem()
{
	STATMANAGER->setMoney(_playerMoney + INVENMANAGER->getVItem()[_changeNum + (int)_sellSlot].Price);
	_playerMoney = STATMANAGER->getMoney();
	//�������� �Ѱ��� ������
	if (INVENMANAGER->getVItem().size() == 1)
	{
		INVENMANAGER->eraseVItem(_changeNum + (int)_sellSlot);
	}
	//�������� �Ѱ��� �ʰ�������
	else
	{
		//�� �������� ���ﶧ
		if (_changeNum + (int)_sellSlot == INVENMANAGER->getVItem().size() - 1)
		{
			INVENMANAGER->erase2VItem(_changeNum + (int)_sellSlot);
		}
		//�������� �ƴ� �ٸ��� ���ﶧ
		else
		{
			//�ӽ� ���Ϳ� �κ� ���͸� �־��ְ�
			for (int i = _changeNum + (int)_sellSlot + 1; i < INVENMANAGER->getVItem().size(); i++)
			{
				_vTemp.push_back(INVENMANAGER->getVItem()[i]);
			}
			//�ȷ��� ������ ���� ���� ������ �� �����ش�.
			INVENMANAGER->eraseVItem(_changeNum + (int)_sellSlot);
			//�ӽú��Ϳ��� �ٽ� �κ� ���Ϳ� �ȸ� ������ ������ ���� �ٽ� �־��ش�
			for (int i = 0; i < _vTemp.size(); i++)
			{
				INVENMANAGER->pushBackVItem(i, _vTemp);
			}
			//�ӽú��ʹ� Ŭ�������ش�
			_vTemp.clear();
		}

	}
	//�̹��� �ֽ�ȭ
	for (int i = 0; i < 24; i++)
	{
		//�ִ� �迭 ���������� �������� �̹����� �־��ش�
		if (INVENMANAGER->getVItem().size() > i)
		{
			_invenSImage[i] = INVENMANAGER->getVItem()[i].priceImage;
		}
		//���� �迭���� �� �̹����� �־��ش�
		else if (INVENMANAGER->getVItem().size() <= i)
		{
			_invenSImage[i] = IMAGEMANAGER->findImage(L"noneShop");
		}
	}
	//_item->buyItem(_changeNum + (int)_sellSlot);
}