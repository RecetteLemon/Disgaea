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
	if (_ld->loadingDone())
	{
		EFFECTMANAGER->addEffect(L"칼질", L"PrinnyEffect", L"image/Effect/prinny_effect.png", 1704, 202,
			213, 202, 15, 1.0f / 90.0f, 1);

		SCENEMANAGER->changeScene(L"TestScene");
	}
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
	//_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile96.png", 960, 480, 10, 5);
	_ld->loadFrameImage(L"IsoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);
	_ld->loadImage(L"IsoEraser", L"Image/MapTool/isoEraser.png", 128, 128);
	_ld->loadImage(L"IsoEdge", L"Image/MapTool/Edge.png", 96, 48);
	_ld->loadImage(L"IsoEdgeFrame", L"Image/MapTool/EdgeFrame.png", 1600, 900);
	_ld->loadImage(L"IsoBackground", L"Image/MapTool/Background.png", 1600, 900);

	// 캐릭터 관련 이미지
	_ld->loadFrameImage(L"Valvatorez", L"image/player/Valvatorez.png", 2964, 2873, 12, 13);
	_ld->loadFrameImage(L"Rozalin", L"image/player/rozalin.png", 1536, 2380, 12, 14);
	_ld->loadFrameImage(L"Cleric", L"image/player/Cleric.png", 1476, 1630, 12, 10);
	_ld->loadFrameImage(L"Adell", L"image/player/Adell.png", 1320, 1920, 12, 12);
	_ld->loadFrameImage(L"Pram", L"image/player/Pram.png", 2136, 2340, 12, 12);
	_ld->loadFrameImage(L"Prinny", L"image/player/prinny.png", 3744, 854, 32, 7);

	// 이펙트 이미지
	_ld->loadFrameImage(L"PrinnyEffect", L"image/Effect/prinny_effect.png", 1704, 202, 8, 1);




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

