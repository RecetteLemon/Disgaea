#include "stdafx.h"
#include "menuUI.h"


menuUI::menuUI()
{
}


menuUI::~menuUI()
{
}

HRESULT menuUI::init()
{
	//스탯UI 소환
	_sUI = new statUi;
	_sUI->init();
	//인벤소환
	_townInven = new townInven;
	_townInven->init();
	//장비창 소환
	_equip = new equip;
	_equip->init();

	_turnMenu = false;
	_invenOn = false;
	_showui = false;
	_equipOn = false;

	_cursor = SLOT_ITEM;
	_selectNum = 0;
	for (int i = 0; i < SLOT_EXIT; i++)
	{
		_selectRc[i] = RectMake(WINSIZEX / 2 + 250, 100 + (i * 80), 250, 80);
	}

	return S_OK;
}

void menuUI::release()
{
}

void menuUI::update() 
{
	control();
	if(_showui)_sUI->update();
	if (_invenOn) _townInven->update();
	if (_equipOn) _equip->update();
}

void menuUI::render() 
{
	if (_turnMenu)
	{
		IMAGEMANAGER->findImage(L"MenuMain")->render(WINSIZEX / 2 + 250, 100, false, 1);
		cursorDraw();
	}
	if (_showui)_sUI->render();
	if (_invenOn) _townInven->render();
	if (_equipOn) _equip->render();
}

void menuUI::control()
{
	if (KEYMANAGER->isOnceKeyDown('I') && (!_showui && !_invenOn && !_turnMenu && !_equipOn)) _turnMenu = true;

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		if (_turnMenu)_turnMenu = false;
		else if (_showui && !_turnMenu)
		{
			_turnMenu = true;
			_showui = false;
		}
		else if (_invenOn && !_turnMenu)
		{
			_turnMenu = true;
			_invenOn = false;
		}
		else if (_equipOn && !_turnMenu)
		{
			_turnMenu = true;
			_equipOn = false;
		}
	}

	if (_turnMenu)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_selectNum--;
			if (_selectNum < 0)_selectNum = 2;
			_cursor = (cursor)_selectNum;
		}
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_selectNum++;
			if (_selectNum > 2)_selectNum = 0;
			_cursor = (cursor)_selectNum;
		}

		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			switch (_cursor)
			{
			case SLOT_ITEM:
				_turnMenu = false;
				_invenOn = true;
				break;
			case SLOT_EQUIP:
				_turnMenu = false;
				_equipOn = true;
				break;
			case SLOT_STATUS:
				_turnMenu = false;
				_showui = true;
				break;
			}
		}
	}
}

void menuUI::cursorDraw()
{
	switch (_cursor)
	{
	case SLOT_ITEM:
		IMAGEMANAGER->findImage(L"cursor")->render(_selectRc[SLOT_ITEM].left - IMAGEMANAGER->findImage(L"cursor")->getWidth(), 
			_selectRc[SLOT_ITEM].top + IMAGEMANAGER->findImage(L"cursor")->getHeight() / 2, false, 1);
		break;
	case SLOT_EQUIP:
		IMAGEMANAGER->findImage(L"cursor")->render(_selectRc[SLOT_EQUIP].left - IMAGEMANAGER->findImage(L"cursor")->getWidth(),
			_selectRc[SLOT_EQUIP].top + IMAGEMANAGER->findImage(L"cursor")->getHeight() / 2, false, 1);
		break;
	case SLOT_STATUS:
		IMAGEMANAGER->findImage(L"cursor")->render(_selectRc[SLOT_STATUS].left - IMAGEMANAGER->findImage(L"cursor")->getWidth(),
			_selectRc[SLOT_STATUS].top + IMAGEMANAGER->findImage(L"cursor")->getHeight() / 2, false, 1);
		break;
	}
}
