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
	if (_ld->loadingDone()) SCENEMANAGER->changeScene(L"MapToolScene");
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
	_ld->loadFrameImage(L"terrainButton", L"Image/MapTool/BtnTerrain.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"objectButton", L"Image/MapTool/BtnObject.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"eraseButton", L"Image/MapTool/BtnEraser.png", 125, 64, 1, 2);
	//_ld->loadFrameImage(L"isoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	_ld->loadFrameImage(L"isoTerrain", L"Image/MapTool/isoTile96.png", 960, 480, 10, 5);
	_ld->loadFrameImage(L"isoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);
	_ld->loadImage(L"isoEraser", L"Image/MapTool/isoEraser.png", 128, 128);
	_ld->loadImage(L"isoEdge", L"Image/MapTool/Edge.png", 96, 48);

	_ld->loadFrameImage(L"selectTile", L"image/MapTool/tileInterFace.png", 192 * 2, 104, 2, 1);
	_ld->loadFrameImage(L"groundImage", L"image/MapTool/terrainTile.png", 640, 320, 10, 5);
	_ld->loadFrameImage(L"objImage", L"image/MapTool/objTile.png", 512, 448, 8, 7);
	_ld->loadFrameImage(L"groundList", L"image/MapTool/terrainListTile.png", 640, 320, 10, 5);
	_ld->loadFrameImage(L"objList", L"image/MapTool/objListTile.png", 512, 448, 8, 7);
	_ld->loadImage(L"saveButton", L"Image/MapTool/saveButton.png", 100, 50);
	_ld->loadImage(L"loadButton", L"Image/MapTool/loadButton.png", 100, 50);
	// ?? 이미지


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