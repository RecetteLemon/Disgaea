#include "stdafx.h"
#include "tankScene.h"


tankScene::tankScene()
{
}


tankScene::~tankScene()
{
}

HRESULT tankScene::init()
{
	_tankMap = new tankMap;
	_tankMap->init();

	_tank = new tank;
	_tank->init();
	_tank->setTankMapMemoryAddressLink(_tankMap);
	_tank->setTankPosition();

	_itemBag = new inven;
	_itemBag->init();

	_invenOn = false;

	return S_OK;
}

void tankScene::release()
{

}

void tankScene::update()
{
	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_invenOn) _invenOn = true;
		else _invenOn = false;
	}
	_tankMap->update();
	if (!_invenOn) _tank->update();
	else if  (_invenOn)_itemBag->update();
}

void tankScene::render()
{
	_tankMap->render();
	_tank->render();
	if(_invenOn)_itemBag->render();
}