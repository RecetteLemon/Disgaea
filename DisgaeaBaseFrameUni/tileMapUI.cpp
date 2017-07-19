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

	_selectRect[GROUNDTILE] = RectMake(_uiImage.x, _uiImage.y, 56, 51);	// 높이는 이미지 크기에 따라 설정
	_selectRect[OBJTILE] = RectMake(_uiImage.x + 53, _uiImage.y, 56, 51);
	// 까는 타일 이미지
	_tileImage[GROUNDTILE].img = IMAGEMANAGER->findImage(L"groundImage");
	_tileImage[OBJTILE].img = IMAGEMANAGER->findImage(L"objImage");

	// 블럭에 마우스를 갖다 대면 보여줄 타일이미지들
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

	// 타일의 정보가 오브젝트면
	if (_tileInfo == OBJTILE)
	{
		IMAGEMANAGER->frameRender(L"objImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}
	// 땅이면
	if (_tileInfo == GROUNDTILE)
	{
		IMAGEMANAGER->frameRender(L"groundImage", _tileRect.left, _tileRect.top, _listImage[_tileInfo].img->getFrameX(), _listImage[_tileInfo].img->getFrameY(), 1);
	}

	// 타일 렉트에 다았으면
	if (_tileCollision)
	{
		_listImage[_tileInfo].img->render(_saveX, _saveY);
	}

}

void tileMapUI::tileSetting()
{
	// 블럭에 마우스가 다으면
	if (PtInRect(&_tileRect, _ptMouse))
	{
		if (!_tileCollision)
		{
			// 좌표 저장
			_saveX = _ptMouse.x;
			_saveY = _ptMouse.y;
			_rectSetting = false;
			// 좌표에서 이미지크기가 창의 가로크기보다 커지면 그만큼 빼준다
			if (_saveX + _listImage[_tileInfo].img->getWidth() > WINSIZEX)
			{
				_saveX = WINSIZEX - _listImage[_tileInfo].img->getWidth() - 10;
			}
			_tileCollision = true;
		}
	}
	// 없으면
	else
	{	//
		if (!_listCollision) _tileCollision = false;
	}

	// 타일 리스트이미지에 마우스가 다으면
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