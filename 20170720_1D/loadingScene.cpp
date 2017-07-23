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
	if (_ld->loadingDone()) SCENEMANAGER->changeScene(L"MenuScene");
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
	
	// 맵툴 이미지
	_ld->loadFrameImage(L"StartButton", L"Image/MapTool/BtnBack.png", 100, 200, 1, 2);
	_ld->loadFrameImage(L"SaveButton", L"Image/MapTool/BtnSave.png", 100, 200, 1, 2);
	_ld->loadFrameImage(L"LoadButton", L"Image/MapTool/BtnLoad.png", 100, 200, 1, 2);
	_ld->loadFrameImage(L"TerrainButton", L"Image/MapTool/BtnTerrain.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"ObjectButton", L"Image/MapTool/BtnObject.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"EraseButton", L"Image/MapTool/BtnEraser.png", 125, 64, 1, 2);
	//_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	//_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/isoTile96.png", 1920, 960, 10, 5);
	//_ld->loadFrameImage(L"IsoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);

	_ld->loadImage(L"IsoEraser", L"Image/MapTool/isoEraser.png", 128, 128);
	_ld->loadImage(L"IsoEdge", L"Image/MapTool/Edge.png", 192, 96);
	_ld->loadImage(L"IsoEdgeFrame", L"Image/MapTool/EdgeFrame.png", 1600, 900);
	_ld->loadImage(L"IsoBackground", L"Image/MapTool/Background.png", 1600, 900);

	_ld->loadFrameImage(L"objTile", L"Image/MapTool/objTile.png", 768, 672, 8, 7);
	_ld->loadFrameImage(L"IsoObject", L"Image/MapTool/objTile2.png", 1536, 1344, 8, 7);
	_ld->loadFrameImage(L"objSelectTile", L"Image/MapTool/objSelectTile.png", 576 / 2, 504 / 2, 8, 7);
	_ld->loadFrameImage(L"objSelectTile2", L"Image/MapTool/objSelectTile2.png", 384 / 2, 336 / 2, 8, 7);

	_ld->loadFrameImage(L"terrainTile", L"Image/MapTool/terrainTile.png", 768, 192, 8, 2);
	_ld->loadFrameImage(L"IsoTerrain", L"Image/MapTool/terrainTile2.png", 1536, 384, 8, 2);
	_ld->loadFrameImage(L"terrainSelectTile", L"Image/MapTool/terrainSelectTile.png", 576 / 2, 144 / 2, 8, 2);
	_ld->loadFrameImage(L"terrainSelectTile2", L"Image/MapTool/terrainSelectTile2.png", 384 / 2, 96 / 2, 8, 2);


	_ld->loadFrameImage(L"settingIcon", L"Image/MapTool/settingIcon.png", 150, 50, 3, 1);


	// 캐릭터 관련 이미지
	_ld->loadFrameImage(L"Valvatorez", L"Image/player/Valvatorez.png", 2964, 2873, 12, 13);
	_ld->loadFrameImage(L"Rozalin", L"Image/player/rozalin.png", 1536, 2380, 12, 14);
	_ld->loadFrameImage(L"Cleric", L"Image/player/Cleric.png", 1476, 1630, 12, 10);
	_ld->loadFrameImage(L"Adell", L"Image/player/Adell.png", 1320, 1920, 12, 12);
	_ld->loadFrameImage(L"Pram", L"Image/player/Pram.png", 2136, 2340, 12, 12);
	_ld->loadFrameImage(L"Prinny", L"Image/player/prinny.png", 3744, 854, 32, 7);
	_ld->loadImage(L"shadow", L"Image/player/shadow.png", 100, 40);


	// 이펙트 이미지
	_ld->loadFrameImage(L"PrinnyEffect", L"image/Effect/prinny_effect.png", 1704, 202, 8, 1);

	//마을 인벤 관련
	_ld->loadImage(L"아이템정보", L"Image/inven/itemInfo.png", 1474, 340);
	_ld->loadImage(L"마을인벤", L"Image/inven/itemBag.png", 553, 480);
	_ld->loadImage(L"마을인벤2", L"Image/inven/itemBagMove.png", 277, 190);
	_ld->loadImage(L"마을인벤3", L"Image/inven/itemBagBlock.png", 40, 123);
	_ld->loadImage(L"마을창고", L"Image/inven/wareHouse.png", 553, 480);
	_ld->loadImage(L"마을창고2", L"Image/inven/wareHouseMove.png", 277, 190);
	_ld->loadImage(L"마을창고3", L"Image/inven/wareHouseBlock.png", 40, 33);

	//상점 관련
	_ld->loadImage(L"shopMain", L"Image/shop/shopMain.png", 1600, 900);
	_ld->loadImage(L"shopBuy", L"Image/shop/shopBuy.png", 1600, 900);
	_ld->loadFrameImage(L"shopSell", L"Image/shop/shopSell.png", 1600, 1800, 1, 2);
	_ld->loadImage(L"buy", L"Image/shop/buy.png", 374, 44);
	_ld->loadImage(L"sell", L"Image/shop/sell.png", 374, 44);
	_ld->loadImage(L"buyInfo", L"Image/inven/buy.png", 1446, 63);
	_ld->loadImage(L"sellInfo", L"Image/inven/sell.png", 1446, 63);
	_ld->loadImage(L"explanation", L"Image/inven/explanation.png", 1446, 63);
	_ld->loadFrameImage(L"sellSort", L"Image/shop/sellSort.png", 560, 741, 2, 3);
	_ld->loadImage(L"buyMessage", L"Image/shop/buyMessage.png", 540, 190);
	_ld->loadImage(L"sellMessage", L"Image/shop/sellMessage.png", 490, 430);
	//전투 인벤 이미지
	_ld->loadImage(L"itemBag", L"Image/Inven/itemBag.png", 553, 480);
	_ld->loadImage(L"moveBar", L"Image/Inven/itemBagBlock.png", 40, 123);
	_ld->loadImage(L"upDirection", L"Image/Inven/upDirection.png", 51, 11);
	_ld->loadImage(L"downDirection", L"Image/Inven/downDirection.png", 51, 11);
	_ld->loadImage(L"cursor", L"Image/Inven/cursor.png", 52, 39);
	_ld->loadFrameImage(L"sort", L"Image/Inven/sortwarehouse.png", 277, 399, 1, 3);
	_ld->loadImage(L"infoBox", L"Image/Inven/infoBox.png", 1474, 77);
	// 아이템 이미지
	_ld->loadImage(L"none", L"Image/Item/none.png", 475, 50);
	// 무기
	_ld->loadImage(L"staff", L"Image/Item/weapon/BoneStaff/boneStaff.png", 463, 56);
	_ld->loadImage(L"staff2", L"Image/Item/weapon/BoneStaff/boneStaff2.png", 664, 53);
	_ld->loadImage(L"staffPrice", L"Image/Item/weapon/BoneStaff/boneStaff-shop.png", 834, 56);
	_ld->loadImage(L"staffInfo", L"Image/Item/weapon/BoneStaff/boneStaffInfo.png", 1448, 64);
	_ld->loadImage(L"glove", L"Image/Item/weapon/DoubleSlap/doubleSlap.png", 463, 56);
	_ld->loadImage(L"glove2", L"Image/Item/weapon/DoubleSlap/doubleSlap2.png", 664, 53);
	_ld->loadImage(L"glovePrice", L"Image/Item/weapon/DoubleSlap/doubleSlap-shop.png", 834, 56);
	_ld->loadImage(L"gloveInfo", L"Image/Item/weapon/DoubleSlap/doubleSlapInfo.png", 1448, 64);
	_ld->loadImage(L"rapier", L"Image/Item/weapon/Rapier/rapier.png", 463, 56);
	_ld->loadImage(L"rapier2", L"Image/Item/weapon/Rapier/rapier2.png", 664, 53);
	_ld->loadImage(L"rapierPrice", L"Image/Item/weapon/Rapier/rapier-shop.png", 834, 56);
	_ld->loadImage(L"rapierInfo", L"Image/Item/weapon/Rapier/rapierInfo.png", 1448, 64);
	_ld->loadImage(L"trumpet", L"Image/Item/weapon/Trumpet/trumpet.png", 463, 56);
	_ld->loadImage(L"trumpet2", L"Image/Item/weapon/Trumpet/trumpet2.png", 664, 53);
	_ld->loadImage(L"trumpetPrice", L"Image/Item/weapon/Trumpet/trumpet-shop.png", 834, 56);
	_ld->loadImage(L"trumpetInfo", L"Image/Item/weapon/Trumpet/trumpetInfo.png", 1448, 64);
	// 방어구
	_ld->loadImage(L"buckler", L"Image/Item/armor/Buckler/Buckler.png", 463, 56);
	_ld->loadImage(L"buckler2", L"Image/Item/armor/Buckler/Buckler2.png", 664, 53);
	_ld->loadImage(L"bucklerPrice", L"Image/Item/armor/Buckler/Buckler-shop.png", 834, 56);
	_ld->loadImage(L"bucklerInfo", L"Image/Item/armor/Buckler/BucklerInfo.png", 1448, 64);
	_ld->loadImage(L"cloth", L"Image/Item/armor/Old Cloth/OldCloth.png", 463, 56);
	_ld->loadImage(L"cloth2", L"Image/Item/armor/Old Cloth/OldCloth2.png", 664, 53);
	_ld->loadImage(L"clothPrice", L"Image/Item/armor/Old Cloth/OldCloth-shop.png", 834, 56);
	_ld->loadImage(L"clothInfo", L"Image/Item/armor/Old Cloth/OldClothInfo.png", 1448, 64);
	_ld->loadImage(L"tunic", L"Image/Item/armor/Tunic/Tunic.png", 463, 56);
	_ld->loadImage(L"tunic2", L"Image/Item/armor/Tunic/Tunic2.png", 664, 53);
	_ld->loadImage(L"tunicPrice", L"Image/Item/armor/Tunic/Tunic-shop.png", 834, 56);
	_ld->loadImage(L"tunicInfo", L"Image/Item/armor/Tunic/TunicInfo.png", 1448, 64);
	// 그외 것들
	_ld->loadImage(L"mintGum", L"Image/Item/general/mintGum/mintGum.png", 463, 56);
	_ld->loadImage(L"mintGum2", L"Image/Item/general/mintGum/mintGum2.png", 664, 53);
	_ld->loadImage(L"mintGumPrice", L"Image/Item/general/mintGum/mintGum-shop.png", 834, 56);
	_ld->loadImage(L"mintGumInfo", L"Image/Item/general/mintGum/mintGumInfo.png", 1448, 64);
	_ld->loadImage(L"water", L"Image/Item/general/water/water.png", 463, 56);
	_ld->loadImage(L"water2", L"Image/Item/general/water/water2.png", 664, 53);
	_ld->loadImage(L"waterPrice", L"Image/Item/general/water/water-shop.png", 834, 56);
	_ld->loadImage(L"waterInfo", L"Image/Item/general/water/waterInfo.png", 1448, 64);
	_ld->loadImage(L"soda", L"Image/Item/general/soda/soda.png", 463, 56);
	_ld->loadImage(L"soda2", L"Image/Item/general/soda/soda2.png", 664, 53);
	_ld->loadImage(L"sodaPrice", L"Image/Item/general/soda/soda-shop.png", 834, 56);
	_ld->loadImage(L"sodaInfo", L"Image/Item/general/soda/sodaInfo.png", 1448, 64);
	_ld->loadImage(L"candy", L"Image/Item/general/hardCandy/hardCandy.png", 463, 56);
	_ld->loadImage(L"candy2", L"Image/Item/general/hardCandy/hardCandy2.png", 664, 53);
	_ld->loadImage(L"candyPrice", L"Image/Item/general/hardCandy/hardCandy-shop.png", 834, 56);
	_ld->loadImage(L"candyInfo", L"Image/Item/general/hardCandy/hardCandyInfo.png", 1448, 64);
	_ld->loadImage(L"noneShop", L"Image/shop/none-shop.png", 834, 56);

	// 숫자 이미지
	_ld->loadImage(L"1", L"Image/Inven/1.png", 20, 25);
	_ld->loadImage(L"2", L"Image/Inven/2.png", 20, 25);
	_ld->loadImage(L"3", L"Image/Inven/3.png", 20, 25);
	_ld->loadImage(L"4", L"Image/Inven/4.png", 20, 25);
	_ld->loadImage(L"5", L"Image/Inven/5.png", 20, 25);
	_ld->loadImage(L"6", L"Image/Inven/6.png", 20, 25);
	_ld->loadImage(L"7", L"Image/Inven/7.png", 20, 25);
	_ld->loadImage(L"8", L"Image/Inven/8.png", 20, 25);
	_ld->loadImage(L"9", L"Image/Inven/9.png", 20, 25);
	_ld->loadImage(L"0", L"Image/Inven/0.png", 20, 25);
	_ld->loadImage(L"커서", L"Image/Inven/itemCursor.png", 52, 39);

	// ?? 이미지


	// ?? 이미지


}
void loadingScene::loadingSound()
{
	// 메뉴 쏴운드


	// Effect Sound
	_ld->loadSound(L"Back", L"Sound/DisgaeaBack.mp3", false, false);
	_ld->loadSound(L"Decision", L"Sound/DisgaeaDecision.mp3", false, false);
	_ld->loadSound(L"Heal_0", L"Sound/DisgaeaHeal_0.mp3", false, false);
	_ld->loadSound(L"Heal_1", L"Sound/DisgaeaHeal_1.mp3", false, false);
	_ld->loadSound(L"ItemGain_0", L"Sound/DisgaeaItemGain_0.mp3", false, false);
	_ld->loadSound(L"ItemGain_1", L"Sound/DisgaeaItemGain_1.mp3", false, false);
	_ld->loadSound(L"Laser_0", L"Sound/DisgaeaLaser_0.mp3", false, false);
	_ld->loadSound(L"Laser_1", L"Sound/DisgaeaLaser_1.mp3", false, false);
	_ld->loadSound(L"Laser_2", L"Sound/DisgaeaLaser_2.mp3", false, false);
	_ld->loadSound(L"LavelUp", L"Sound/DisgaeaLavelUp.mp3", false, false);
	_ld->loadSound(L"StageClear", L"Sound/DisgaeaClear.mp3", false, false);
	_ld->loadSound(L"UnitDead", L"Sound/DisgaeaUnitDead.mp3", false, false);
	

	// ?? Sound


	// ?? Sound

	
	// ?? Sound

	
	// ?? Sound
}