#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}

testScene::~testScene()
{
}

HRESULT testScene::init()
{
	_itemBag_battle = new inven;
	_itemBag_battle->init();

	_townInven = new townInven;
	_townInven->init();

	_invenOn_battle = false;
	_invenOn_town = false;

	return S_OK;
}
void testScene::release()
{

}

void testScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_invenOn_battle) _invenOn_battle = true;
		else _invenOn_battle = false;
	}
	else if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (!_invenOn_town) _invenOn_town = true;
		else _invenOn_town = false;
	}

	if (_invenOn_battle)_itemBag_battle->update();
	if (_invenOn_town) _townInven->update();
}

void testScene::render()
{
	if (_invenOn_battle)_itemBag_battle->render();
	if (_invenOn_town) _townInven->render();
}