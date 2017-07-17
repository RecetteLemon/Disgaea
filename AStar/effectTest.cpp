#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("Æø¹ß", "explosion.bmp", 0, 0, 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("Æø¹ß"), 32, 62, 1, 1.0f);

	//					ÀÌÆåÆ® Å°°ª   ÆÄÀÏÀÌ¸§     ÀÌ¹ÌÁö°¡·Î, ¼¼·Î, ÇÁ·¹ÀÓ °¡·Î, ¼¼·Î, FPS, ÀÌÆåÆ® ¾Ö´Ï¸ŞÀÌ¼Ç ¼Óµµ, ¹öÆÛ·®
	EFFECTMANAGER->addEffect("Æø¹ß", "explosion.bmp", 832, 62, 32, 62, 1, 1.0f, 300);

	_count = 0;

	return S_OK;
}

void effectTest::release()
{

}

void effectTest::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("Æø¹ß", _ptMouse.x, _ptMouse.y);
	}


	//_count++;
	//
	//if (_count % 10 == 0)
	//{
	//	EFFECTMANAGER->play("Æø¹ß", RND->getFromIntTo(100, 300),RND->getFromIntTo(100, 300));
	//}

	EFFECTMANAGER->update();
	_effect->update();
}

void effectTest::render()
{
	EFFECTMANAGER->render();
	_effect->render();
}
