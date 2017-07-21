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
	_item = new item;
	_item->init();

	_invenPage = TOWN_PAGE;
	i_cursor = IMAGEMANAGER->findImage("cursor");
	i_bar = IMAGEMANAGER->findImage("moveBar");
	
	_itemBag = RectMake(50, WINSIZEY / 2 - 140, 553, 480);
	_cursor = RectMake(40, WINSIZEY / 2 - 50, 52, 39);
	_bar = RectMake(_itemBag.right - 47, _itemBag.top + 67, 40, 123);
	_sort = RectMake(WINSIZEX - 350, WINSIZEY / 2 - 80, 277, 133);
	_upDirection = RectMakeCenter((_itemBag.right - _itemBag.left) / 2 + _itemBag.left - 54, _itemBag.top + 70, 51, 11);
	_downDirection = RectMakeCenter((_itemBag.right - _itemBag.left) / 2 + _itemBag.left - 54, _itemBag.bottom - 10, 51, 11);
	_infoBox = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 50, 1474, 77);
	_slotChoice = SLOT_1;
	_slotNum = _slotCount = 0;


	//전체 슬롯
	for (int i = 0; i < 24; i++)
	{
		_slot[i] = RectMake(_itemBag.left + 12, _itemBag.top + 79 + (66 * i), 475, 50);
	}
	
	_currentFrameY = 2;
	_upDirectionOn = false;
	_downDirectionOn = true;

	_alpha = 1.0f;
	_listNum = 0;

	//위아래 버튼 토글
	_upTo = _downTo = false;
	_isInfoOn = false;

	return S_OK;
}

void inven::release()
{

}

void inven::update()
{
	//커서 움직임
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_upTo = true;
		_slotNum--;
		if (_slotNum < 0) _slotNum = 0;
		_slotCount--;
		if (_slotCount < 0)
		{
			_slotNum = 5;
			_slotCount = 23;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('W')) _upTo = false;
	
	//커서 움직임
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_downTo = true;
		_slotNum++;
		if (_slotNum > 5) _slotNum = 5;
		_slotCount++;
		if (_slotCount > 23)
		{
			_slotCount = 0;
			_slotNum = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyUp('S')) _downTo = false;

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_currentFrameY++;
		if (_currentFrameY == 3) _currentFrameY = 0;
	}

	

	slot();
	alpha();
	directionFlash();
	listSet();
	moveBar();
	infoBox();

}

void inven::render()
{
	IMAGEMANAGER->findImage("itemBag")->render(_itemBag.left, _itemBag.top);
	IMAGEMANAGER->findImage("sort")->frameRender(_sort.left, _sort.top, 0, _currentFrameY, 1.0f);
	for (int i = _listNum; i < _listNum + 6; i++)
	{
		//값이 없을때는 논 이미지만 나옴
		if (_item->getVItem().size() == 0)
		{
			i_slot[i] = IMAGEMANAGER->findImage("none");
		}
		//벡터값이 있으면 
		else
		{
			//있는 배열 범위까지만 아이템의 이미지를 넣어준다
			if (_item->getVItem().size() > i)
			{
				i_slot[i] = _item->getVItem()[i].Image;
			}
			//없는 배열에는 논 이미지를 넣어준다
			else if (_item->getVItem().size() <= i)
			{
				i_slot[i] = IMAGEMANAGER->findImage("none");
			}
			
		}
		i_slot[i]->render(_slot[i].left, _slot[i].top);
	}

	i_bar->render(_bar.left, _bar.top);
	i_cursor->render(_cursor.left, _cursor.top);
	if(_upDirectionOn) IMAGEMANAGER->frameRender("upDirection", _upDirection.left, _upDirection.top, 0, 0, _alpha);
	if(_downDirectionOn) IMAGEMANAGER->frameRender("downDirection", _downDirection.left, _downDirection.top, 0, 0, _alpha);
	if (_isInfoOn) IMAGEMANAGER->findImage("infoBox")->render(_infoBox.left, _infoBox.top);
}
//눈에 보이는 6개의 슬롯을 세팅해주장
void inven::slot()
{
	switch (_slotNum)
	{
	case 0:
		_slotChoice = SLOT_1;
		_cursor = RectMake(40, WINSIZEY / 2 - 50, 52, 39);
		break;
	case 1:
		_slotChoice = SLOT_2;
		_cursor = RectMake(40, WINSIZEY / 2 + 16, 52, 39);
		break;
	case 2:
		_slotChoice = SLOT_3;
		_cursor = RectMake(40, WINSIZEY / 2 + 82, 52, 39);
		break;
	case 3:
		_slotChoice = SLOT_4;
		_cursor = RectMake(40, WINSIZEY / 2 + 148, 52, 39);
		break;
	case 4:
		_slotChoice = SLOT_5;
		_cursor = RectMake(40, WINSIZEY / 2 + 214, 52, 39);
		break;
	case 5:
		_slotChoice = SLOT_6;
		_cursor = RectMake(40, WINSIZEY / 2 + 280, 52, 39);
		break;
	}
}
//화살표 알파값
void inven::alpha()
{
	_alpha-= 0.01f;
	if (_alpha <= 0.0f) _alpha = 1.0f;
}
//어떠한 상황에서 위 아래 화살표가 반짝이는가?
void inven::directionFlash()
{
	if (_bar.bottom >= _itemBag.bottom - 6) _downDirectionOn = false;
	else  _downDirectionOn = true;
	if (_bar.top > _itemBag.top + 67) _upDirectionOn = true;
	else _upDirectionOn = false;
}
//밑으로 내려가든 위로 가든 리스트는 움직여야지?
void inven::listSet()
{
	if (_slotCount >= 5)
	{
		_listNum = _slotCount - 4;
		for (int i = _listNum; i < _listNum + 6; i++)
		{
			_slot[i] = RectMake(_itemBag.left + 12, _itemBag.top + 79 + (66 * (i - _listNum)), 475, 50);
		}
	}
	if (_slotCount == 0)
	{
		_listNum = 0;
		for (int i =0; i < 6; i++)
		{
			_slot[i] = RectMake(_itemBag.left + 12, _itemBag.top + 79 + (66 * i), 475, 50);
		}
	}
}
//스크롤바 움직임
void inven::moveBar()
{
	//위버튼 누르고 보여지는 첫번째 슬롯일 경우
	if (_upTo && _slotChoice == SLOT_1)
	{
		if (_slotCount < 18)
		{
			_upTo = false;
			_bar.top -= 16.0f;
			_bar.bottom -= 16.0f;
			//넘어가는거 방지
			if(_bar.top < _itemBag.top + 67)_bar = RectMake(_itemBag.right - 47, _itemBag.top + 67, 40, 123);
		}
	}
	if (_upTo && _slotChoice == SLOT_6)
	{
		_upTo = false;
		_bar = RectMake(_itemBag.right - 47, _itemBag.bottom - 4 - 123, 40, 123);
	}
	//밑버튼 누르고 보여지는 여섯번째 슬롯일 경우
	if (_downTo && _slotChoice == SLOT_6)
	{
		if (_slotCount > 5)
		{
			_downTo = false;
			_bar.top += 16.0f;
			_bar.bottom += 16.0f;
			//넘어가는거 방지
			if (_bar.bottom > _itemBag.bottom - 4)_bar = RectMake(_itemBag.right - 47, _itemBag.bottom - 4 - 123, 40, 123);
		}
	}
	if (_downTo && _slotChoice == SLOT_1)
	{
		_downTo = false;
		_bar = RectMake(_itemBag.right - 47, _itemBag.top + 67, 40, 123);
	}

}
//정보
void inven::infoBox()
{
	RECT tempRC;
	for (int i = 0; i < 24; i++)
	{
		if (IntersectRect(&tempRC, &_cursor, &_slot[i]))
		{
			if (i_slot[i] != IMAGEMANAGER->findImage("none")) _isInfoOn = true;
			else if (i_slot[i] == IMAGEMANAGER->findImage("none")) _isInfoOn = false;
		}
	}
}
