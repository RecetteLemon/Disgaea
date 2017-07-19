#include "stdafx.h"
#include "tileMapUI.h"


tileMapUI::tileMapUI()
{
}


tileMapUI::~tileMapUI()
{
}

HRESULT tileMapUI::init()
{
	_uiImage.img = IMAGEMANAGER->addFrameImage("selectTile", L"image/MapTool/tileInterFace.png", 192 * 2, 104, 2, 1);
	_uiImage.x = WINSIZEX - 400;
	_uiImage.y = 100;


	_selectRect[GROUNDTILE] = RectMake(_uiImage.x, _uiImage.y, 56, 51);	// ���̴� �̹��� ũ�⿡ ���� ����
	_selectRect[OBJTILE] = RectMake(_uiImage.x + 53, _uiImage.y, 56, 51);
	// ��� Ÿ�� �̹���
	_tileImage[GROUNDTILE].img = IMAGEMANAGER->addFrameImage("groundImage", L"image/MapTool/terrainTile.png", 640, 320, 10, 5);
	_tileImage[OBJTILE].img = IMAGEMANAGER->addFrameImage("objImage", L"image/MapTool/objTile.png", 512, 448, 8, 7);

	// ���� ���콺�� ���� ��� ������ Ÿ���̹�����
	_listImage[GROUNDTILE].img = IMAGEMANAGER->addFrameImage("groundList", L"image/MapTool/terrainListTile.png", 640, 320, 10, 5);
	_listImage[OBJTILE].img = IMAGEMANAGER->addFrameImage("objList", L"image/MapTool/objListTile.png", 512, 448, 8, 7);


	_tileRect = RectMake(_uiImage.x + _uiImage.img->getFrameWidth() / 2 - 32, _uiImage.y + _uiImage.img->getFrameHeight() / 2 - 32 + 17, 64, 64);

	_tileInfo = GROUNDTILE;

	_tileCollision = _listCollision = false;

	return S_OK;
}

void tileMapUI::release()
{

}

void tileMapUI::update()
{
	tileSetting();
}

void tileMapUI::render()
{
	
	_uiImage.img->frameRender(_uiImage.x, _uiImage.y, _uiImage.img->getFrameX(), _uiImage.img->getFrameY());

	// Ÿ���� ������ ������Ʈ��
	if (_tileInfo == OBJTILE)
	{
		IMAGEMANAGER->frameRender("objImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}
	// ���̸�
	if (_tileInfo == GROUNDTILE)
	{
		IMAGEMANAGER->frameRender("groundImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}

	// Ÿ�� ��Ʈ�� �پ�����
	if (_tileCollision)
	{
		_listImage[_tileInfo].img->render(_saveX, _saveY);
	}

	for (int i = 0; i < ENDTILE; i++)
	{
		//Rectangle(getMemDC(), _selectRect[i].left, _selectRect[i].top, _selectRect[i].right, _selectRect[i].bottom);
	}


}

void tileMapUI::tileSetting()
{
	RECT temp;
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		for (int i = 0; i < ENDTILE; i++)
		{
			if (PtInRect(&_selectRect[i], _ptMouse))
			{
				if (i == OBJTILE)
				{
					_uiImage.img->setFrameX(1);
					_tileInfo = OBJTILE;
				}

				else if (i == GROUNDTILE)
				{
					_uiImage.img->setFrameX(0);
					_tileInfo = GROUNDTILE;
				}

			}
		}
	}
	
	// ���� ���콺�� ������
	if (PtInRect(&_tileRect, _ptMouse))
	{
		if (!_tileCollision)
		{
			// ��ǥ ����
			_saveX = _ptMouse.x;
			_saveY = _ptMouse.y;
			_rectSetting = false;
			// ��ǥ���� �̹���ũ�Ⱑ â�� ����ũ�⺸�� Ŀ���� �׸�ŭ ���ش�
			if (_saveX + _listImage[_tileInfo].img->getWidth() > WINSIZEX)
			{
				_saveX = WINSIZEX - _listImage[_tileInfo].img->getWidth() - 10;
			}
			_tileCollision = true;
		}
	}
	// ������
	else
	{	//
		if (!_listCollision) _tileCollision = false;
	}

	// Ÿ�� ����Ʈ�̹����� ���콺�� ������
	if (PtInRect(&_listRect[_tileInfo], _ptMouse))
	{
		if (_tileCollision)
		{
			_listCollision = true;
		}

		// �ѹ��� �����Ű��
		if (!_rectSetting)
		{
			// Ÿ�ϵ� ��Ʈ ����
			if (_tileInfo == OBJTILE)
			{
				for (int i = 0; i < OBJTILEY; i++)
				{
					for (int j = 0; j < OBJTILEX; j++)
					{
						SetRect(&_listImage->objRc[j + OBJTILEX * i],
							_saveX + TILESIZE * j,
							_saveY + TILESIZE * i,
							64, 64);
					}
				}
			}

			if (_tileInfo == GROUNDTILE)
			{
				for (int i = 0; i < GROUNDTILEY; i++)
				{
					for (int j = 0; j < GROUNDTILEX; j++)
					{
						SetRect(&_listImage->groundRc[j + OBJTILEX * i],
							_saveX + TILESIZE * j,
							_saveY + TILESIZE * i,
							64, 64);
					}
				}
			}
			_rectSetting = true;
		}

		if (_tileInfo == OBJTILE)
		{
			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				_listImage[_tileInfo].img->setFrameX(int((_ptMouse.x - _saveX) / 64));
				_listImage[_tileInfo].img->setFrameY(int((_ptMouse.y - _saveY) / 64));
			}
		}
		if (_tileInfo == GROUNDTILE)
		{
			if (KEYMANAGER->isOnceKeyDown('D'))
			{
				_listImage[_tileInfo].img->setFrameX(int((_ptMouse.x - _saveX) / 64));
				_listImage[_tileInfo].img->setFrameY(int((_ptMouse.y - _saveY) / 64));
			}
		}
	}
	else _listCollision = false;


	


	_listRect[_tileInfo] = RectMake(_saveX, _saveY, _listImage[_tileInfo].img->getWidth(), _listImage[_tileInfo].img->getHeight());
	////Ÿ�ϼ¿��� �����޾ƿ���
	//for (int i = 0; i < OBJTILEX * OBJTILEY; i++)
	//{
	//	if (PtInRect(&_objTile[i].rcTile, _ptMouse))
	//	{
	//		_currentTile.x = _objTile[i].FrameX;
	//		_currentTile.y = _objTile[i].FrameY;
	//		break;
	//	}
	//}

	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	if (PtInRect(&_tiles[i].rc, _ptMouse))
	//	{
	//		if (_tileInfo == GROUNDTILE)
	//		{
	//			_tiles[i].terrainFrameX = _currentTile.x;
	//			_tiles[i].terrainFrameY = _currentTile.y;

	//			_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
	//		}
	//		else if (_tileInfo == OBJTILE)
	//		{
	//			_tiles[i].objFrameX = _currentTile.x;
	//			_tiles[i].objFrameY = _currentTile.y;

	//			_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
	//		}
	//		else break;

	//		InvalidateRect(_hWnd, NULL, false);
	//		break;
	//	}
	//}

}