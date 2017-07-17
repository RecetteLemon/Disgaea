#include "stdafx.h"
#include "pixelCollisionTest.h"


pixelCollisionTest::pixelCollisionTest()
{
}


pixelCollisionTest::~pixelCollisionTest()
{
}

HRESULT pixelCollisionTest::init(void)
{
	IMAGEMANAGER->addImage("언덕", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage("공", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 100;
	_y = WINSIZEY / 2 + 110;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//탐사축은 OO에 셋팅
	//-> 다음 OO으로 알맞은 말은 : 
	_probeY = _y + _ball->getHeight() / 2;

	return S_OK;
}

void pixelCollisionTest::release(void)
{

}

void pixelCollisionTest::update(void)
{
	//제일 중요한건 연산 아니겠습니꽈ㅏㅏㅏㅏㅏㅏㅏㅏ

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}

	//탐사축은 실시간으로 보정해준다
	_probeY = (int)_y + _ball->getHeight() / 2;


	//범위는 
	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		//픽셀 정보값을 가져와서 컬러레퍼런스에 담아둔다
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("언덕")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

}

void pixelCollisionTest::render(void)
{
	IMAGEMANAGER->findImage("언덕")->render(getMemDC(), 0, 0);

	_ball->render(getMemDC(), _rc.left, _rc.top);


}