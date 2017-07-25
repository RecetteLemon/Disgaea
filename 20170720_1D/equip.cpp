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
	_sort = RectMake(_itemBox.right - 100, 315, 374, 203);
	//
	_slotNum = ISLOT_1;
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_invenBox.left + 12, _invenBox.top + 76 + (67 * i), 474, 56);
	}
	for (int i = 0; i < 4; i++)
	{
		_equipSlot[i] = RectMake(WINSIZEX - 619, 30 + (59 * i), 564, 54);
	}
	_bar = RectMake(_invenBox.right - 47, _invenBox.top + 67, 40, 123);
	//_cursor = RectMakeCenter(_slot[0].left - 4, (_slot[0].bottom - _slot[0].top) / 2 + _slot[0].top, 52, 39);
	_cursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 0), 52, 39);
	_slotCount = _num = _tempNum = 0;
	_infoOn = false;
	_isEquip = false;
	_isTemp = false;
	_state = EQUIP;
	_charNum = 0;
	_currentFrameX = _currentFrameY = 0;

	return S_OK;
}

void equip::release()
{
}

void equip::update()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_charNum--;
		if (_charNum < 0) _charNum = 4;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_charNum++;
		if (_charNum > 4) _charNum = 0;
	}


	switch (_charNum)
	{
	case 0:
		face = IMAGEMANAGER->findImage(L"AdellFace");
		break;
	case 1:
		face = IMAGEMANAGER->findImage(L"RozalinFace");
		break;
	case 2:
		face = IMAGEMANAGER->findImage(L"PramFace");
		break;
	case 3:
		face = IMAGEMANAGER->findImage(L"ValvatorezFace");
		break;
	case 4:
		face = IMAGEMANAGER->findImage(L"ClericFace");
		break;
	}
	for (int i = 0; i < 24; i++)
	{
		//있는 배열 범위까지만 아이템의 이미지를 넣어준다
		if (INVENMANAGER->getVItem().size() > i)
		{
			i_slot[i] = INVENMANAGER->getVItem()[i].Image;
		}
		//없는 배열에는 논 이미지를 넣어준다
		else if (INVENMANAGER->getVItem().size() <= i)
		{
			i_slot[i] = IMAGEMANAGER->findImage(L"none");
		}
	}
	cursorMove();
	slotMove();
	itemInfo();

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (!_isEquip) _isEquip = true;
		else _isEquip = false;
		if (_isEquip && i_slot[_slotCount + (int)_slotNum] != IMAGEMANAGER->findImage(L"none")) equipItem();
	}
	_bar = RectMake(_invenBox.right - 47, _invenBox.top + 67 + (16 * _slotCount), 40, 123);
}

void equip::render()
{
	IMAGEMANAGER->findImage(L"StatUI")->render(_statBox.left, _statBox.top, false, 0.4f);
	IMAGEMANAGER->findImage(L"StatUI1")->render(_statBox.left, _statBox.top, false, 1.0f);
	face->render(_statBox.left + 5, _statBox.top + 70, 195, 195, false, 1.0f);
	//무기 끼우기
	if (STATMANAGER->getVWeapon(_charNum).size() == 0)	IMAGEMANAGER->findImage(L"weapon")->render(_equipSlot[0].left, _equipSlot[0].top, false, 1.0f);
	else STATMANAGER->getVWeapon(_charNum)[0].Image2->render(_equipSlot[0].left + 100, _equipSlot[0].top, false, 1.0f);
	// 방어구
	if (STATMANAGER->getVArmor(_charNum).size() == 0)
	{
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[1].left, _equipSlot[1].top, false, 1.0f);
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[2].left, _equipSlot[2].top, false, 1.0f);
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[3].left, _equipSlot[3].top, false, 1.0f);
	}
	if (STATMANAGER->getVArmor(_charNum).size() == 1)
	{
		STATMANAGER->getVArmor(_charNum)[0].Image2->render(_equipSlot[1].left + 100, _equipSlot[1].top, false, 1.0f);
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[2].left, _equipSlot[2].top, false, 1.0f);
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[3].left, _equipSlot[3].top, false, 1.0f);
	}
	if (STATMANAGER->getVArmor(_charNum).size() == 2)
	{
		STATMANAGER->getVArmor(_charNum)[0].Image2->render(_equipSlot[1].left + 100, _equipSlot[1].top, false, 1.0f);
		STATMANAGER->getVArmor(_charNum)[1].Image2->render(_equipSlot[2].left + 100, _equipSlot[2].top, false, 1.0f);
		IMAGEMANAGER->findImage(L"other")->render(_equipSlot[3].left, _equipSlot[3].top, false, 1.0f);
	}
	if (STATMANAGER->getVArmor(_charNum).size() == 3)
	{
		STATMANAGER->getVArmor(_charNum)[0].Image2->render(_equipSlot[1].left + 100, _equipSlot[1].top, false, 1.0f);
		STATMANAGER->getVArmor(_charNum)[1].Image2->render(_equipSlot[2].left + 100, _equipSlot[2].top, false, 1.0f);
		STATMANAGER->getVArmor(_charNum)[2].Image2->render(_equipSlot[3].left + 100, _equipSlot[3].top, false, 1.0f);
	}
	//if()
	IMAGEMANAGER->findImage(L"itemBag")->render(_invenBox.left, _invenBox.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"moveBar")->render(_bar.left, _bar.top, false, 1.0f);
	IMAGEMANAGER->findImage(L"equipSort")->frameRender(_sort.left, _sort.top, _currentFrameX, _currentFrameY, false, 1.0f);
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
				if (INVENMANAGER->getVItem()[i].Type == GENERAL) i_slot[i]->render(_slot[i].left, _slot[i].top, false, 0.4f);
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
		WCHAR str[100];
		IMAGEMANAGER->findImage(L"miniBlack")->render(_itemBox.left, _itemBox.top, false, 0.4f);
		IMAGEMANAGER->findImage(L"miniInfo")->render(_itemBox.left, _itemBox.top, false, 1.0f);
		IMAGEMANAGER->findImage(L"infoBox")->render(61, _invenBox.bottom + 20, false, 1.0f);
		if (INVENMANAGER->getVItem().size())
		{
			for (int i = 0; i < INVENMANAGER->getVItem().size(); i++)
			{
				if (i == _slotCount + (int)_slotNum)
				{
					INVENMANAGER->getVItem()[i].info->render(61 + 13, _invenBox.bottom + 20 + 7, false, 1.0f);
					INVENMANAGER->getVItem()[i].Image2->render(_itemBox.left + 7, _itemBox.top + 10, false, 1.0f);
					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].HP);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 330 - 60, 532 + 100 - 10, 600 + 330, 523 + 100 + 50);

					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].SP);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 330 - 60, 532 + 130 - 10, 600 + 330, 523 + 130 + 50);

					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].Atk);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 330 - 60, 532 + 165 - 5, 600 + 330, 523 + 165 + 50);

					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].Int);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 330 - 60, 532 + 195 - 5, 600 + 330, 523 + 195 + 50);

					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].Def);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 665 - 60, 532 + 165 - 5, 600 + 665, 523 + 165 + 50);

					swprintf_s(str, L"%d", INVENMANAGER->getVItem()[i].Res);
					DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0x7a, 0x7a, 0x7a), 1), L"고딕", 30, str, 600 + 665 - 60, 532 + 195 - 5, 600 + 665, 523 + 195 + 50);
				}
			}
		}
	}
	IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);
	if (_isTemp)IMAGEMANAGER->findImage(L"cursor")->render(_tempCursor.left, _tempCursor.top, false, 1.0f);

	WCHAR str[128];
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_charNum]._atk);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"고딕", 40, str, 400, WINSIZEY / 2 - 280, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_charNum]._int);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"고딕", 40, str, 400, WINSIZEY / 2 - 250, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_charNum]._def);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"고딕", 40, str, WINSIZEX / 2, WINSIZEY / 2 - 280, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_charNum]._res);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"고딕", 40, str, WINSIZEX / 2, WINSIZEY / 2 - 250, WINSIZEX, WINSIZEY);
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
	if (_state == EQUIP)
	{
		switch (_EslotNum)
		{
		case 0:
			_cursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 0), 52, 39);
			_tempCursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 0), 52, 39);
			break;
		case 1:
			_cursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 1), 52, 39);
			_tempCursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 1), 52, 39);
			break;
		case 2:
			_cursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 2), 52, 39);
			_tempCursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 2), 52, 39);
			break;
		case 3:
			_cursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 3), 52, 39);
			_tempCursor = RectMakeCenter(_equipSlot[0].left, 40 + (59 * 3), 52, 39);
			break;
		}

	}
}
void equip::slotMove()
{
	switch (_state)
	{
	case INVEN:
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
				_slotNum = (INVEN_SLOT)_num;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				_num--;
				_slotNum = (INVEN_SLOT)_num;
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
				_slotNum = (INVEN_SLOT)_num;
			}
		}
		else
		{
			if (KEYMANAGER->isOnceKeyDown('S'))
			{
				_num++;
				_slotNum = (INVEN_SLOT)_num;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('D'))	_state = EQUIP;
		break;
	case EQUIP:
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_num--;
			if (_num < 0) _num = 3;
			_EslotNum = (EQUIP_SLOT)_num;

		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_num++;
			if (_num > 3) _num = 0;
			_EslotNum = (EQUIP_SLOT)_num;
		}
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			if (STATMANAGER->getVWeapon(_charNum).size() == 0 && STATMANAGER->getVArmor(_charNum).size() == 0)
			{
				_isTemp = true;
				_state = INVEN;
			}
			else
			{
				if (_num == 0)
				{
					if (STATMANAGER->getVWeapon(_charNum).size() == 1)
					{
						takeOff_weapon();
						INVENMANAGER->pushBackVItem(0, STATMANAGER->getVWeapon(_charNum));
						STATMANAGER->eraseVWeapon(_charNum, 0);
					}
				}
				else
				{
					if (STATMANAGER->getVArmor(_charNum).size() == 1)
					{
						takeOff_armor(0);
						INVENMANAGER->pushBackVItem(0, STATMANAGER->getVArmor(_charNum));
						STATMANAGER->eraseVArmor(_charNum, 0);
					}
					else if (STATMANAGER->getVArmor(_charNum).size() == 2)
					{
						if (_num == 1)
						{
							takeOff_armor(0);
							INVENMANAGER->pushBackVItem(0, STATMANAGER->getVArmor(_charNum));
							_vTemp.push_back(STATMANAGER->getVArmor(_charNum)[1]);
							STATMANAGER->erase2VArmor(_charNum, 0);
							STATMANAGER->pushBackVArmor(_charNum, _vTemp[0]);
							_vTemp.clear();
						}
						if (_num == 2)
						{
							takeOff_armor(1);
							INVENMANAGER->pushBackVItem(1, STATMANAGER->getVArmor(_charNum));
							STATMANAGER->eraseVArmor(_charNum, 1);
						}
					}
					else if (STATMANAGER->getVArmor(_charNum).size() == 3)
					{
						if (_num == 1)
						{
							takeOff_armor(0);
							INVENMANAGER->pushBackVItem(0, STATMANAGER->getVArmor(_charNum));
							_vTemp.push_back(STATMANAGER->getVArmor(_charNum)[1]);
							_vTemp.push_back(STATMANAGER->getVArmor(_charNum)[2]);
							STATMANAGER->erase2VArmor(_charNum, 0);
							STATMANAGER->pushBackVArmor(_charNum, _vTemp[0]);
							STATMANAGER->pushBackVArmor(_charNum, _vTemp[1]);
							_vTemp.clear();
						}
						if (_num == 2)
						{
							takeOff_armor(1);
							INVENMANAGER->pushBackVItem(1, STATMANAGER->getVArmor(_charNum));
							_vTemp.push_back(STATMANAGER->getVArmor(_charNum)[2]);
							STATMANAGER->erase2VArmor(_charNum, 1);
							STATMANAGER->pushBackVArmor(_charNum, _vTemp[0]);
							_vTemp.clear();
						}
						if (_num == 3)
						{
							takeOff_armor(2);
							INVENMANAGER->pushBackVItem(2, STATMANAGER->getVArmor(_charNum));
							STATMANAGER->eraseVArmor(_charNum, 2);
						}
					}
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown('A')) _state = INVEN;
		break;
	}
	//인벤 슬롯
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_invenBox.left + 12, _invenBox.top + 76 + (67 * (i - _slotCount)), 474, 56);
	}
}

void equip::itemInfo()
{
	RECT tempRC;
	if (IntersectRect(&tempRC, &RectMake(_cursor.left - 20, _cursor.top + 10, _cursor.right + 20, _cursor.bottom - 10), &_slot[_slotCount + (int)_slotNum]))
	{
		if (i_slot[_slotCount + (int)_slotNum] != IMAGEMANAGER->findImage(L"none"))  _infoOn = true;
		else _infoOn = false;
	}
	if (INVENMANAGER->getVItem().size() == 0) _infoOn = false;
}

void equip::equipItem()
{
	switch (INVENMANAGER->getVItem()[_slotCount + (int)_slotNum].Type)
	{
	case WEAPON:
		if (STATMANAGER->getVWeapon(_charNum).size() == 0)
		{
			//인벤창에 장비 템 하나 있을때
			if (INVENMANAGER->getVItem().size() == 1)
			{
				_isEquip = false;
				STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[0]);
				INVENMANAGER->erase2VItem(0);
			}
			//템이 여러개 있을때
			else if (INVENMANAGER->getVItem().size() > 1)
			{
				//마지막꺼
				if (_slotCount + (int)_slotNum == INVENMANAGER->getVItem().size() - 1)
				{
					_isEquip = false;
					STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					INVENMANAGER->erase2VItem(_slotCount + (int)_slotNum);

				}
				//마지막거 말고
				else if (_slotCount + (int)_slotNum < INVENMANAGER->getVItem().size())
				{
					_isEquip = false;
					STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					for (int i = _slotCount + (int)_slotNum + 1; i < INVENMANAGER->getVItem().size(); i++)
					{
						_vTemp.push_back(INVENMANAGER->getVItem()[i]);
					}
					INVENMANAGER->eraseVItem(_slotCount + (int)_slotNum);
					for (int i = 0; i < _vTemp.size(); i++)
					{
						INVENMANAGER->pushBackVItem(i, _vTemp);
					}
					_vTemp.clear();
				}
			}
		}
		//아이템을 끼고 있어서 스왑할때
		else if (STATMANAGER->getVWeapon(_charNum).size() > 0)
		{
			_isEquip = false;
			_vTemp.push_back(STATMANAGER->getVWeapon(_charNum)[0]);
			//함수 실행
			takeOff_weapon();
			STATMANAGER->eraseVWeapon(_charNum, 0);
			STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
			INVENMANAGER->erase2VItem(_slotCount + (int)_slotNum);
			INVENMANAGER->pushBackVItem(0, _vTemp);
			_vTemp.clear();
		}
		statUP_weapon();
		break;

	case ARMOR:

		if (STATMANAGER->getVArmor(_charNum).size() < 4)
		{
			_isEquip = false;
			//인벤창에 장비 템 하나 있을때
			if (INVENMANAGER->getVItem().size() == 1)
			{
				_isEquip = false;
				STATMANAGER->pushBackVArmor(_charNum, INVENMANAGER->getVItem()[0]);
				INVENMANAGER->erase2VItem(0);
			}
			else if (INVENMANAGER->getVItem().size() > 1)
			{
				//마지막꺼
				if (_slotCount + (int)_slotNum == INVENMANAGER->getVItem().size() - 1)
				{
					_isEquip = false;
					STATMANAGER->pushBackVArmor(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					INVENMANAGER->erase2VItem(_slotCount + (int)_slotNum);

				}
				//마지막거 말고
				else if (_slotCount + (int)_slotNum < INVENMANAGER->getVItem().size())
				{
					_isEquip = false;
					STATMANAGER->pushBackVArmor(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					for (int i = _slotCount + (int)_slotNum + 1; i < INVENMANAGER->getVItem().size(); i++)
					{
						_vTemp.push_back(INVENMANAGER->getVItem()[i]);
					}
					INVENMANAGER->eraseVItem(_slotCount + (int)_slotNum);
					for (int i = 0; i < _vTemp.size(); i++)
					{
						INVENMANAGER->pushBackVItem(i, _vTemp);
					}
					_vTemp.clear();
				}
			}

		}
		//else if (STATMANAGER->getVArmor().size() == 3)
		//{
		//
		//}
		statUP_armor();
		break;
	}

}
void equip::statUP_weapon()
{
	if (STATMANAGER->getVWeapon(_charNum).size() > 0)
	{
		STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk + STATMANAGER->getVWeapon(_charNum)[0].Atk);
		STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int + STATMANAGER->getVWeapon(_charNum)[0].Int);
		STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def + STATMANAGER->getVWeapon(_charNum)[0].Def);
		STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res + STATMANAGER->getVWeapon(_charNum)[0].Res);
	}
}

void equip::statUP_armor()
{
	if (STATMANAGER->getVArmor(_charNum).size() > 0)
	{
		if (STATMANAGER->getVArmor(_charNum).size() == 1)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk + STATMANAGER->getVArmor(_charNum)[0].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int + STATMANAGER->getVArmor(_charNum)[0].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def + STATMANAGER->getVArmor(_charNum)[0].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res + STATMANAGER->getVArmor(_charNum)[0].Res);
		}
		else if (STATMANAGER->getVArmor(_charNum).size() == 2)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk + STATMANAGER->getVArmor(_charNum)[1].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int + STATMANAGER->getVArmor(_charNum)[1].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def + STATMANAGER->getVArmor(_charNum)[1].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res + STATMANAGER->getVArmor(_charNum)[1].Res);
		}
		else if (STATMANAGER->getVArmor(_charNum).size() == 3)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk + STATMANAGER->getVArmor(_charNum)[2].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int + STATMANAGER->getVArmor(_charNum)[2].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def + STATMANAGER->getVArmor(_charNum)[2].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res + STATMANAGER->getVArmor(_charNum)[2].Res);
		}

	}
}
//아이템을 벗을때 능력치 돌려주는
void equip::takeOff_weapon()
{
	STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk - STATMANAGER->getVWeapon(_charNum)[0].Atk);
	STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int - STATMANAGER->getVWeapon(_charNum)[0].Int);
	STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def - STATMANAGER->getVWeapon(_charNum)[0].Def);
	STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res - STATMANAGER->getVWeapon(_charNum)[0].Res);
}
void equip::takeOff_armor(int i)
{
	STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()[_charNum]._atk - STATMANAGER->getVArmor(_charNum)[i].Atk);
	STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()[_charNum]._int - STATMANAGER->getVArmor(_charNum)[i].Int);
	STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()[_charNum]._def - STATMANAGER->getVArmor(_charNum)[i].Def);
	STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()[_charNum]._res - STATMANAGER->getVArmor(_charNum)[i].Res);
}