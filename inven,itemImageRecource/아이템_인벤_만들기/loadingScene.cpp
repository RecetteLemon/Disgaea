#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("캐릭선택씬");
	}
}

void loadingScene::render()	
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	//이미지가 여러장이 아니니까 포문 돌려서
	//이미지 1장을 300개 올리겠다는 뜻임
	for (int i = 0; i < 1000; i++)
	{
		_loading->loadImage("캐릭선택", WINSIZEX, WINSIZEY);
	}
}

void loadingScene::loadingSound()
{

}
