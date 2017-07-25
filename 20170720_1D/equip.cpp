#include "stdafx.h"
#include "equip.h"


equip::equip()
{
	_charNum = 0;
}


equip::~equip()
{
}

HRESULT equip::init()
{
	//�⺻Ʋ
	_statBox = RectMake(0, 10, 1600, 300);
	_invenBox = RectMake(61, 315, 553, 480);
	_itemBox = RectMake(_invenBox.right + 20, 535, 677, 253);
	_sort = RectMake(_itemBox.right - 100, 315, 374, 203);
	//
	_slotNum = ESLOT_1;
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_invenBox.left + 12, _invenBox.top + 76 + (67 * i), 474, 56);
	}
	for (int i = 0; i < 4; i++)
	{
		_equipSlot[i] = RectMake(WINSIZEX - 619, 30 + (59 * i), 564, 54);
	}
	_bar = RectMake(_invenBox.right - 47, _invenBox.top + 67, 40, 123);
	_cursor = RectMakeCenter(_slot[0].left - 4, (_slot[0].bottom - _slot[0].top) / 2 + _slot[0].top, 52, 39);
	_slotCount = _num = _tempNum = 0;
	_infoOn = false;
	_isEquip = false;
	_state = INVEN;

	return S_OK;
}

void equip::release()
{
}

void equip::update()
{
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
		//�ִ� �迭 ���������� �������� �̹����� �־��ش�
		if (INVENMANAGER->getVItem().size() > i)
		{
			i_slot[i] = INVENMANAGER->getVItem()[i].Image;
		}
		//���� �迭���� �� �̹����� �־��ش�
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
	//���� �����
	if (STATMANAGER->getVWeapon(_charNum).size() == 0)	IMAGEMANAGER->findImage(L"weapon")->render(_equipSlot[0].left, _equipSlot[0].top, false, 1.0f);
	else STATMANAGER->getVWeapon(_charNum)[0].Image2->render(_equipSlot[0].left + 100, _equipSlot[0].top, false, 1.0f);
	// ��
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
		IMAGEMANAGER->findImage(L"miniBlack")->render(_itemBox.left, _itemBox.top, false, 0.4f);
		IMAGEMANAGER->findImage(L"miniInfo")->render(_itemBox.left, _itemBox.top, false, 1.0f);
		IMAGEMANAGER->findImage(L"infoBox")->render(61, _invenBox.bottom + 20, false, 1.0f);
		if (INVENMANAGER->getVItem().size())
		{
			INVENMANAGER->getVItem()[_slotCount + (int)_slotNum].info->render(61 + 13, _invenBox.bottom + 20 + 7, false, 1.0f);
			INVENMANAGER->getVItem()[_slotCount + (int)_slotNum].Image2->render(_itemBox.left + 7, _itemBox.top + 10, false, 1.0f);
		}
	}
	IMAGEMANAGER->findImage(L"cursor")->render(_cursor.left, _cursor.top, false, 1.0f);


	WCHAR str[128];
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()->_atk);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, 400, WINSIZEY / 2 - 280, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()->_int);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, 400, WINSIZEY / 2 - 250, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()->_def);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, WINSIZEX / 2, WINSIZEY / 2 - 280, WINSIZEX, WINSIZEY);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()->_res);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"���", 40, str, WINSIZEX / 2, WINSIZEY / 2 - 250, WINSIZEX, WINSIZEY);
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
	//�κ� ����
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
			//�κ�â�� ��� �� �ϳ� ������
			if (INVENMANAGER->getVItem().size() == 1)
			{
				_isEquip = false;
				STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[0]);
				INVENMANAGER->erase2VItem(0);
			}
			//���� ������ ������
			else if (INVENMANAGER->getVItem().size() > 1)
			{
				//��������
				if (_slotCount + (int)_slotNum == INVENMANAGER->getVItem().size() - 1)
				{
					_isEquip = false;
					STATMANAGER->pushBackVWeapon(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					INVENMANAGER->erase2VItem(_slotCount + (int)_slotNum);

				}
				//�������� ����
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
		else if (STATMANAGER->getVWeapon(_charNum).size() > 0)
		{
			_isEquip = false;
			_vTemp.push_back(STATMANAGER->getVWeapon(_charNum)[0]);
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
			//�κ�â�� ��� �� �ϳ� ������
			if (INVENMANAGER->getVItem().size() == 1)
			{
				_isEquip = false;
				STATMANAGER->pushBackVArmor(_charNum, INVENMANAGER->getVItem()[0]);
				INVENMANAGER->erase2VItem(0);
			}
			else if (INVENMANAGER->getVItem().size() > 1)
			{
				//��������
				if (_slotCount + (int)_slotNum == INVENMANAGER->getVItem().size() - 1)
				{
					_isEquip = false;
					STATMANAGER->pushBackVArmor(_charNum, INVENMANAGER->getVItem()[_slotCount + (int)_slotNum]);
					INVENMANAGER->erase2VItem(_slotCount + (int)_slotNum);

				}
				//�������� ����
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
		STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()->_atk + STATMANAGER->getVWeapon(_charNum)[0].Atk);
		STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()->_int + STATMANAGER->getVWeapon(_charNum)[0].Int);
		STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()->_def + STATMANAGER->getVWeapon(_charNum)[0].Def);
		STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()->_res + STATMANAGER->getVWeapon(_charNum)[0].Res);
	}
}

void equip::statUP_armor()
{
	if (STATMANAGER->getVArmor(_charNum).size() > 0)
	{
		if (STATMANAGER->getVArmor(_charNum).size() == 1)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()->_atk + STATMANAGER->getVArmor(_charNum)[0].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()->_int + STATMANAGER->getVArmor(_charNum)[0].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()->_def + STATMANAGER->getVArmor(_charNum)[0].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()->_res + STATMANAGER->getVArmor(_charNum)[0].Res);
		}
		else if (STATMANAGER->getVArmor(_charNum).size() == 2)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()->_atk + STATMANAGER->getVArmor(_charNum)[1].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()->_int + STATMANAGER->getVArmor(_charNum)[1].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()->_def + STATMANAGER->getVArmor(_charNum)[1].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()->_res + STATMANAGER->getVArmor(_charNum)[1].Res);
		}
		else if (STATMANAGER->getVArmor(_charNum).size() == 3)
		{
			STATMANAGER->setAtk(_charNum, STATMANAGER->getPlayerStat()->_atk + STATMANAGER->getVArmor(_charNum)[2].Atk);
			STATMANAGER->setInt(_charNum, STATMANAGER->getPlayerStat()->_int + STATMANAGER->getVArmor(_charNum)[2].Int);
			STATMANAGER->setDef(_charNum, STATMANAGER->getPlayerStat()->_def + STATMANAGER->getVArmor(_charNum)[2].Def);
			STATMANAGER->setRes(_charNum, STATMANAGER->getPlayerStat()->_res + STATMANAGER->getVArmor(_charNum)[2].Res);
		}

	}
}