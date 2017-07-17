#include "stdafx.h"
#include "starcraftScene.h"
#include "battle.h"


starcraftScene::starcraftScene()
{
}


starcraftScene::~starcraftScene()
{
}

HRESULT starcraftScene::init()
{
	_sm = new shipManager;
	_sm->init();


	return S_OK;
}

void starcraftScene::release()
{

}

void starcraftScene::update()
{
	_sm->update();
}

void starcraftScene::render()
{
	_sm->render();
}