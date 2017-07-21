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
	if (_ld->loadingDone()) SCENEMANAGER->changeScene("MenuScene");
}
void loadingScene::render()
{
	_ld->render();
}
void loadingScene::loadingImage()
{
	
	// 메뉴씬 이미지
	_ld->loadImage("Menu", L"Image/Menu/M01.png", 1600, 900);
	_ld->loadImage("MenuMouse", L"Image/Menu/MMouse.png", 50, 39);
	_ld->loadFrameImage("startButton", L"Image/MapTool/buttonStart.png", 243, 258, 1, 2);
	_ld->loadFrameImage("saveButton", L"Image/MapTool/buttonSave.png", 243, 258, 1, 2);
	_ld->loadFrameImage("loadButton", L"Image/MapTool/buttonLoad.png", 243, 258, 1, 2);
	_ld->loadFrameImage("terrainButton", L"Image/MapTool/BtnTerrain.png", 125, 64, 1, 2);
	_ld->loadFrameImage("objectButton", L"Image/MapTool/BtnObject.png", 125, 64, 1, 2);
	_ld->loadFrameImage("eraseButton", L"Image/MapTool/BtnEraser.png", 125, 64, 1, 2);
	_ld->loadFrameImage("isoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	_ld->loadFrameImage("isoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);
	_ld->loadImage("isoEraser", L"Image/MapTool/isoEraser.png", 128, 128);

	//마을 인벤 관련
	_ld->loadImage("아이템정보", L"Image/inven/itemInfo.png", 1474, 340);
	_ld->loadImage("마을인벤", L"Image/inven/itemBag.png", 553, 480);
	_ld->loadImage("마을인벤2", L"Image/inven/itemBagMove.png", 277, 190);
	_ld->loadImage("마을인벤3", L"Image/inven/itemBagBlock.png", 40, 123);
	_ld->loadImage("마을창고", L"Image/inven/wareHouse.png", 553, 480);
	_ld->loadImage("마을창고2", L"Image/inven/wareHouseMove.png", 277, 190);
	_ld->loadImage("마을창고3", L"Image/inven/wareHouseBlock.png", 40, 33);

	//상점 관련
	_ld->loadImage("shopMain", L"Image/inven/main.png", 1600, 900);
	_ld->loadImage("buy", L"Image/inven/buy.png", 1446, 63);
	_ld->loadImage("sell", L"Image/inven/sell.png", 1446, 63);
	_ld->loadImage("explanation", L"Image/inven/explanation.png", 1446, 63);
	_ld->loadImage("none", L"image/inven/none.png", 474, 56);

	//전투 인벤 이미지
	_ld->loadImage("itemBag",L"Image/Inven/itemBag.png",553,480);
	_ld->loadImage("moveBar", L"Image/Inven/itemBagBlock.png",40,123);
	_ld->loadImage("upDirection", L"Image/Inven/upDirection.png", 51, 11);
	_ld->loadImage("downDirection", L"Image/Inven/downDirection.png", 51, 11);
	_ld->loadImage("cursor", L"Image/Inven/cursor.png", 52, 39);
	_ld->loadFrameImage("sort", L"Image/Inven/sortwarehouse.png", 277, 399, 1, 3);
	_ld->loadImage("infoBox", L"Image/Inven/infoBox.png", 1474, 77);

	// 아이템 이미지
	_ld->loadImage("none", L"Image/Item/none.png", 475, 50);
	_ld->loadImage("mintGum", L"Image/Item/mintGum.png", 475, 50);
	_ld->loadImage("miniGumInfo", L"Image/Item/mintGumInfo.png", 1448, 64);
	_ld->loadImage("water", L"Image/Item/water.png", 475, 50);
	_ld->loadImage("waterInfo", L"Image/Item/waterInfo.png", 1448, 64);
	_ld->loadImage("soda", L"Image/Item/soda.png", 475, 50);
	_ld->loadImage("sodaInfo", L"Image/Item/sodaInfo.png", 1448, 64);
	_ld->loadImage("candy", L"Image/Item/candy.png", 475, 50);

	//_ld->loadImage("candyInfo", L"Image/Item/hardCandyInfo.png", 1448, 64);
	// 숫자 이미지
	_ld->loadImage("1", L"image/inven/1.png", 20, 25);
	_ld->loadImage("2", L"image/inven/2.png", 20, 25);
	_ld->loadImage("3", L"image/inven/3.png", 20, 25);
	_ld->loadImage("4", L"image/inven/4.png", 20, 25);
	_ld->loadImage("5", L"image/inven/5.png", 20, 25);
	_ld->loadImage("6", L"image/inven/6.png", 20, 25);
	_ld->loadImage("7", L"image/inven/7.png", 20, 25);
	_ld->loadImage("8", L"image/inven/8.png", 20, 25);
	_ld->loadImage("9", L"image/inven/9.png", 20, 25);
	_ld->loadImage("0", L"image/inven/0.png", 20, 25);
	_ld->loadImage("커서", L"image/inven/itemCursor.png", 52, 39);
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