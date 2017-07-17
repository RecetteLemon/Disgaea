#include "stdafx.h"
#include "characterSelectScene.h"


characterSelectScene::characterSelectScene()
{
}


characterSelectScene::~characterSelectScene()
{
}

HRESULT characterSelectScene::init()
{

	return S_OK;
}

void characterSelectScene::release()
{

}

void characterSelectScene::update()
{

}

void characterSelectScene::render()
{
	IMAGEMANAGER->render("캐릭선택", getMemDC(), 0, 0);
}
