#include "stdafx.h"
#include "aStarScene.h"


aStarScene::aStarScene()
{
}


aStarScene::~aStarScene()
{

}

HRESULT aStarScene::init()
{
	_ast = new aStarTest;
	_ast->init();
	_ast->setTiles();

	_tank = new tankk;
	_tank->init();
	_tank->setAstarMemoryAddressLink(_ast);
	_ast->setTankAddressMemoryLink(_tank);

	return S_OK;
}

void aStarScene::release()
{

}

void aStarScene::update() 
{
	if (KEYMANAGER->isOnceKeyDown('H')) this->init();
	_ast->update();
	_tank->update();
}

void aStarScene::render() 
{
	_ast->render();
	_tank->render();
}

