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
	//¹ÎÆ®²ô¾ö
	Item mintGum;
	ZeroMemory(&mintGum, sizeof(Item));
	mintGum.Name = L"mintGum";
	mintGum.Type = GENERAL;
	mintGum.Image = IMAGEMANAGER->findImage("mintGum");
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
	soda.Image = IMAGEMANAGER->findImage("soda");
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
	garlic_water.Image = IMAGEMANAGER->findImage("water");
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
	hard_candy.Image = IMAGEMANAGER->findImage("candy");
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

void item::itemSet()
{
	//¹ÎÆ®²ô¾ö
	Item mintGum;
	ZeroMemory(&mintGum, sizeof(Item));
	mintGum.Name = L"mintGum";
	mintGum.Type = GENERAL;
	mintGum.Image = IMAGEMANAGER->findImage("mintGum");
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
	soda.Image = IMAGEMANAGER->findImage("soda");
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
	garlic_water.Image = IMAGEMANAGER->findImage("water");
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
	hard_candy.Image = IMAGEMANAGER->findImage("candy");
	hard_candy.Atk = 0;
	hard_candy.Int = 0;
	hard_candy.Def = 0;
	hard_candy.Res = 0;
	hard_candy.HP = 100;
	hard_candy.SP = 0;
	hard_candy.Price = 34;
	_vItem.push_back(hard_candy);
}