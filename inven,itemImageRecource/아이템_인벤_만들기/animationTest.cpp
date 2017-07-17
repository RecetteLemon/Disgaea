#include "stdafx.h"
#include "animationTest.h"


animationTest::animationTest()
{
}


animationTest::~animationTest()
{

}

HRESULT animationTest::init()
{
	//낙타 이미지
	_camel = IMAGEMANAGER->addFrameImage("camel", "camel.bmp", 300, 267, 4, 3, true, RGB(255, 0, 255));

	//디폴트
	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani1->setDefPlayFrame(true, false);
	_ani1->setFPS(1);

	//배열
	int arrAni[] = { 1, 1, 2, 6, 5, 4 };
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani2->setPlayFrame(arrAni, 6, true);
	_ani2->setFPS(1);
	//구간
	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani3->setPlayFrame(2, 7, true, true);
	_ani3->setFPS(1);

	return S_OK;
}

void animationTest::release()
{

}

void animationTest::update() 
{
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_ani1->start();
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_ani2->start();
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_ani3->start();
	}

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime());

}

void animationTest::render() 
{
	_camel->aniRender(getMemDC(), 100, 200, _ani1);
	_camel->aniRender(getMemDC(), 250, 200, _ani2);
	_camel->aniRender(getMemDC(), 400, 200, _ani3);
}
