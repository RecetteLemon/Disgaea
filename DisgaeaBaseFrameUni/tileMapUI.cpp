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
	_uiImage.img = IMAGEMANAGER->findImage(L"selectTile");
	_uiImage.x = WINSIZEX - 400;
	_uiImage.y = 100;

	_selectRect[GROUNDTILE] = RectMake(_uiImage.x, _uiImage.y, 56, 51);	// ���̴� �̹��� ũ�⿡ ���� ����
	_selectRect[OBJTILE] = RectMake(_uiImage.x + 53, _uiImage.y, 56, 51);
	// ��� Ÿ�� �̹���
	_tileImage[GROUNDTILE].img = IMAGEMANAGER->findImage(L"groundImage");
	_tileImage[OBJTILE].img = IMAGEMANAGER->findImage(L"objImage");

	// ���� ���콺�� ���� ��� ������ Ÿ���̹�����
	_listImage[GROUNDTILE].img = IMAGEMANAGER->findImage(L"groundList");
	_listImage[OBJTILE].img = IMAGEMANAGER->findImage(L"objList");


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
		IMAGEMANAGER->frameRender(L"objImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}
	// ���̸�
	if (_tileInfo == GROUNDTILE)
	{
		IMAGEMANAGER->frameRender(L"groundImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}

	// Ÿ�� ��Ʈ�� �پ�����
	if (_tileCollision)
	{
		_listImage[_tileInfo].img->render(_saveX, _saveY);
	}

}

void tileMapUI::tileSetting()
{
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
	}
	else _listCollision = false;


	_listRect[_tileInfo] = RectMake(_saveX, _saveY, _listImage[_tileInfo].img->getWidth(), _listImage[_tileInfo].img->getHeight());

}

void tileMapUI::lButtonClick()
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

	if (_listCollision)
	{
		if (_tileInfo == OBJTILE)
		{
			_listImage[_tileInfo].img->setFrameX(int((_ptMouse.x - _saveX) / 64));
			_listImage[_tileInfo].img->setFrameY(int((_ptMouse.y - _saveY) / 64));
		}
		if (_tileInfo == GROUNDTILE)
		{
			_listImage[_tileInfo].img->setFrameX(int((_ptMouse.x - _saveX) / 64));
			_listImage[_tileInfo].img->setFrameY(int((_ptMouse.y - _saveY) / 64));
		}
	}

}