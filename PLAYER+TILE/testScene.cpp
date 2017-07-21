#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{

}


HRESULT testScene::init(void)
{

	_cm = new characterManager;
	_cm->init(WINSIZEX / 2, WINSIZEY / 2);
	//_cm->selectPlayer(2);
	

	
	return S_OK;
}
void testScene::release(void)
{

}
void testScene::update(void) 
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_cm->selectPlayer(0);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_cm->selectPlayer(1);
	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_cm->selectPlayer(2);
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		_cm->selectPlayer(3);
	}
	if (KEYMANAGER->isOnceKeyDown('5'))
	{
		_cm->selectPlayer(4);
	}
	if (KEYMANAGER->isOnceKeyDown('6'))
	{
		_cm->selectEnemy(0);
	}
	if (KEYMANAGER->isOnceKeyDown('7'))
	{
		STATMANAGER->setExp(0, STATMANAGER->getPlayerStat()[0]._exp + 10);
		//STATMANAGER->setAtk(0, 100);
	}
	STATMANAGER->update();
	_cm->update();
}
void testScene::render(void) 
{
	WCHAR str[128];
	swprintf_s(str, L"%d ,%d, %d", STATMANAGER->getPlayerStat()[0]._atk, STATMANAGER->getPlayerStat()[0]._maxExp, STATMANAGER->getPlayerStat()[0]._exp);
	DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2 + 100, WINSIZEY / 2 + 30);

	_cm->render();
}