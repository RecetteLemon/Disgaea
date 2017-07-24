#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{
	//´õºí ½½·¦
	Item doubleSlap;
	ZeroMemory(&doubleSlap, sizeof(Item));
	doubleSlap.Name = L"doubleSlap";
	doubleSlap.Type = WEAPON;
	doubleSlap.Image = IMAGEMANAGER->findImage(L"glove");
	doubleSlap.Image2 = IMAGEMANAGER->findImage(L"glove2");
	doubleSlap.priceImage = IMAGEMANAGER->findImage(L"glovePrice");
	doubleSlap.info = IMAGEMANAGER->findImage(L"gloveInfo");
	doubleSlap.Atk = 12;
	doubleSlap.Int = 0;
	doubleSlap.Def = 0;
	doubleSlap.Res = 0;
	doubleSlap.HP = 0;
	doubleSlap.SP = 0;
	doubleSlap.Price = 210;
	_vItem.push_back(doubleSlap);

	//·¹ÀÌÇÇ¾î
	Item rapier;
	ZeroMemory(&rapier, sizeof(Item));
	rapier.Name = L"rapier";
	rapier.Type = WEAPON;
	rapier.Image = IMAGEMANAGER->findImage(L"rapier");
	rapier.Image2 = IMAGEMANAGER->findImage(L"rapier2");
	rapier.priceImage = IMAGEMANAGER->findImage(L"rapierPrice");
	rapier.info = IMAGEMANAGER->findImage(L"rapierInfo");
	rapier.Atk = 15;
	rapier.Int = 0;
	rapier.Def = 0;
	rapier.Res = 0;
	rapier.HP = 0;
	rapier.SP = 0;
	rapier.Price = 210;
	_vItem.push_back(rapier);

	//Æ®·´Æê
	Item trumpet;
	ZeroMemory(&trumpet, sizeof(Item));
	trumpet.Name = L"trumpet";
	trumpet.Type = WEAPON;
	trumpet.Image = IMAGEMANAGER->findImage(L"trumpet");
	trumpet.Image2 = IMAGEMANAGER->findImage(L"trumpet2");
	trumpet.priceImage = IMAGEMANAGER->findImage(L"trumpetPrice");
	trumpet.info = IMAGEMANAGER->findImage(L"trumpetInfo");
	trumpet.Atk = 0;
	trumpet.Int = 0;
	trumpet.Def = 0;
	trumpet.Res = 1;
	trumpet.HP = 0;
	trumpet.SP = 0;
	trumpet.Price = 230;
	_vItem.push_back(trumpet);

	//º» ½ºÅ×ÇÁ
	Item boneStaff;
	ZeroMemory(&boneStaff, sizeof(Item));
	boneStaff.Name = L"boneStaff";
	boneStaff.Type = WEAPON;
	boneStaff.Image = IMAGEMANAGER->findImage(L"staff");
	boneStaff.Image2 = IMAGEMANAGER->findImage(L"staff2");
	boneStaff.priceImage = IMAGEMANAGER->findImage(L"staffPrice");
	boneStaff.info = IMAGEMANAGER->findImage(L"staffInfo");
	boneStaff.Atk = 9;
	boneStaff.Int = 16;
	boneStaff.Def = 0;
	boneStaff.Res = 0;
	boneStaff.HP = 0;
	boneStaff.SP = 0;
	boneStaff.Price = 220;
	_vItem.push_back(boneStaff);

	//³°Àº ¿Ê
	Item oldCloth;
	ZeroMemory(&oldCloth, sizeof(Item));
	oldCloth.Name = L"oldCloth";
	oldCloth.Type = ARMOR;
	oldCloth.Image = IMAGEMANAGER->findImage(L"cloth");
	oldCloth.Image2 = IMAGEMANAGER->findImage(L"cloth2");
	oldCloth.priceImage = IMAGEMANAGER->findImage(L"clothPrice");
	oldCloth.info = IMAGEMANAGER->findImage(L"clothInfo");
	oldCloth.Atk = 0;
	oldCloth.Int = 0;
	oldCloth.Def = 4;
	oldCloth.Res = 4;
	oldCloth.HP = 0;
	oldCloth.SP = 0;
	oldCloth.Price = 34;
	_vItem.push_back(oldCloth);

	//Æ©´Ð
	Item tunic;
	ZeroMemory(&tunic, sizeof(Item));
	tunic.Name = L"tunic";
	tunic.Type = ARMOR;
	tunic.Image = IMAGEMANAGER->findImage(L"tunic");
	tunic.Image2 = IMAGEMANAGER->findImage(L"tunic2");
	tunic.priceImage = IMAGEMANAGER->findImage(L"tunicPrice");
	tunic.info = IMAGEMANAGER->findImage(L"tunicInfo");
	tunic.Atk = 0;
	tunic.Int = 0;
	tunic.Def = 6;
	tunic.Res = 2;
	tunic.HP = 0;
	tunic.SP = 0;
	tunic.Price = 84;
	_vItem.push_back(tunic);

	//¹öÅ¬·¯
	Item buckler;
	ZeroMemory(&buckler, sizeof(Item));
	buckler.Name = L"buckler";
	buckler.Type = ARMOR;
	buckler.Image = IMAGEMANAGER->findImage(L"buckler");
	buckler.Image2 = IMAGEMANAGER->findImage(L"buckler2");
	buckler.priceImage = IMAGEMANAGER->findImage(L"bucklerPrice");
	buckler.info = IMAGEMANAGER->findImage(L"bucklerInfo");
	buckler.Atk = 0;
	buckler.Int = 0;
	buckler.Def = 14;
	buckler.Res = 8;
	buckler.HP = 0;
	buckler.SP = 0;
	buckler.Price = 230;
	_vItem.push_back(buckler);

	//¹ÎÆ®²ô¾ö
	Item mintGum;
	ZeroMemory(&mintGum, sizeof(Item));
	mintGum.Name = L"mintGum";
	mintGum.Type = GENERAL;
	mintGum.Image = IMAGEMANAGER->findImage(L"mintGum");
	mintGum.Image2 = IMAGEMANAGER->findImage(L"mintGum2");
	mintGum.priceImage = IMAGEMANAGER->findImage(L"mintGumPrice");
	mintGum.info = IMAGEMANAGER->findImage(L"mintGumInfo");
	mintGum.Atk = 0;
	mintGum.Int = 0;
	mintGum.Def = 0;
	mintGum.Res = 0;
	mintGum.HP = 50;
	mintGum.SP = 0;
	mintGum.Price = 10;
	_vItem.push_back(mintGum);

	//¼Ò´Ù
	Item soda;
	ZeroMemory(&soda, sizeof(Item));
	soda.Name = L"soda";
	soda.Type = GENERAL;
	soda.Image = IMAGEMANAGER->findImage(L"soda");
	soda.Image2 = IMAGEMANAGER->findImage(L"soda2");
	soda.priceImage = IMAGEMANAGER->findImage(L"sodaPrice");
	soda.info = IMAGEMANAGER->findImage(L"sodaInfo");
	soda.Atk = 0;
	soda.Int = 0;
	soda.Def = 0;
	soda.Res = 0;
	soda.HP = 0;
	soda.SP = 20;
	soda.Price = 22;
	_vItem.push_back(soda);

	//¸¶´Ã¹°?
	Item garlic_water;
	ZeroMemory(&garlic_water, sizeof(Item));
	garlic_water.Name = L"water";
	garlic_water.Type = GENERAL;
	garlic_water.Image = IMAGEMANAGER->findImage(L"water");
	garlic_water.Image2 = IMAGEMANAGER->findImage(L"water2");
	garlic_water.priceImage = IMAGEMANAGER->findImage(L"waterPrice");
	garlic_water.info = IMAGEMANAGER->findImage(L"waterInfo");
	garlic_water.Atk = 0;
	garlic_water.Int = 0;
	garlic_water.Def = 0;
	garlic_water.Res = 0;
	garlic_water.HP = 10;
	garlic_water.SP = 40;
	garlic_water.Price = 69;
	_vItem.push_back(garlic_water);

	//µüµüÇÑ »çÅÁ
	Item hard_candy;
	ZeroMemory(&hard_candy, sizeof(Item));
	hard_candy.Name = L"hardcandy";
	hard_candy.Type = GENERAL;
	hard_candy.Image = IMAGEMANAGER->findImage(L"candy");
	hard_candy.Image2 = IMAGEMANAGER->findImage(L"candy2");
	hard_candy.priceImage = IMAGEMANAGER->findImage(L"candyPrice");
	hard_candy.info = IMAGEMANAGER->findImage(L"candyInfo");
	hard_candy.Atk = 0;
	hard_candy.Int = 0;
	hard_candy.Def = 0;
	hard_candy.Res = 0;
	hard_candy.HP = 100;
	hard_candy.SP = 0;
	hard_candy.Price = 34;
	_vItem.push_back(hard_candy);

	return S_OK;
}

void item::release()
{
	
}

void item::sellItem(int a)
{
	//_vItem.erase(_vItem.begin() + a);
	_vItem[a].priceImage = IMAGEMANAGER->findImage(L"noneShop");
}

void item::buyItem(int a)
{
	switch (a)
	{
	case 0:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"glovePrice");
		break;
	case 1:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"rapierPrice");
		break;
	case 2:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"trumpetPrice");
		break;
	case 3:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"staffPrice");
		break;
	case 4:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"clothPrice");
		break;
	case 5:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"tunicPrice");
		break;
	case 6:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"bucklerPrice");
		break;
	case 7:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"mintGumPrice");
		break;
	case 8:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"sodaPrice");
		break;
	case 9:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"waterPrice");
		break;
	case 10:
		_vItem[a].priceImage = IMAGEMANAGER->findImage(L"candyPrice");
		break;
	}
}