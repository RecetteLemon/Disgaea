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
	_ld = new loading;
	_ld->init();
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}
void loadingScene::release()
{
	SAFE_DELETE(_ld);
}
void loadingScene::update()
{
	_ld->update();
	if (_ld->loadingDone()) SCENEMANAGER->changeScene(L"TestScene");
}
void loadingScene::render()
{
	_ld->render();
}
void loadingScene::loadingImage()
{
	
	// 메뉴씬 이미지
	_ld->loadImage(L"Menu", L"Image/Menu/M01.png", 1600, 900);
	_ld->loadImage(L"MenuMouse", L"Image/Menu/MMouse.png", 50, 39);
	_ld->loadFrameImage(L"StartButton", L"Image/MapTool/buttonStart.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"SaveButton", L"Image/MapTool/buttonSave.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"LoadButton", L"Image/MapTool/buttonLoad.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"TerrainButton", L"Image/MapTool/BtnTerrain.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"ObjectButton", L"Image/MapTool/BtnObject.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"EraseButton", L"Image/MapTool/BtnEraser.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile96.png", 960, 480, 10, 5);
	_ld->loadFrameImage(L"IsoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);
	_ld->loadImage(L"IsoEraser", L"Image/MapTool/isoEraser.png", 128, 128);

	// 캐릭터 관련 이미지

	_ld->loadFrameImage(L"Valvatorez", L"image/player/Valvatorez.png", 2964, 2873, 12, 13);




	// ?? 이미지


	// ?? 이미지


	// ?? 이미지


}
void loadingScene::loadingSound()
{
	// 메뉴 쏴운드


	// ?? Sound


	// ?? Sound


	// ?? Sound

	
	// ?? Sound

	
	// ?? Sound
}