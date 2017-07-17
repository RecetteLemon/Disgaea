#include "stdafx.h"
#include "tankk.h"
#include "aStarTest.h"

tankk::tankk()
{
}


tankk::~tankk()
{
}

HRESULT tankk::init()
{
	_img = IMAGEMANAGER->addFrameImage("ÅÊÅ©", "tank.bmp", 256, 128, 8, 4, true, RGB(255, 0, 255));

	_dir = DIR_RIGHT;

	_isStart = false;

	_indexX = _indexY = 0;

	_x = ((float)(TILEWIDTH * 3)) + (TILEWIDTH / 2);
	_y = ((float)(TILEHEIGHT * 3)) + (TILEHEIGHT / 2);

	_rc = RectMakeCenter(_x, _y, 28, 28);
	_frame = 0;

	return S_OK;
}

void tankk::release()
{

}

void tankk::update() 
{
	_rc = RectMakeCenter(_x, _y, 28, 28);
	_frame++;
	key();
}

void tankk::render() 
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top);
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void tankk::key()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_dir = DIR_LEFT;
		move();
		imgFrame();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_dir = DIR_RIGHT;
		move();
		imgFrame();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_dir = DIR_UP;
		move();
		imgFrame();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_dir = DIR_DOWN;
		move();
		imgFrame();
	}
}

void tankk::move()
{
	switch (_dir)
	{
		case DIR_LEFT:
			_img->setFrameY(3);
			_x -= 2.0f;
		break;
		case DIR_RIGHT:
			_img->setFrameY(2);
			_x += 2.0f;
		break;
		case DIR_UP:
			_img->setFrameY(0);
			_y -= 2.0f;
		break;
		case DIR_DOWN:
			_img->setFrameY(1);
			_y += 2.0f;
		break;
	}
	_rc = RectMakeCenter(_x, _y, 28, 28);
}

void tankk::imgFrame()
{
	if (_frame % 10 == 0)
	{
		_img->setFrameX(_img->getFrameX() + 1);
		if (_img->getFrameX() >= _img->getMaxFrameX())
		{
			_img->setFrameX(0);
			_frame = 0;
		}
	}
}