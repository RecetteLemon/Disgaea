#include "stdafx.h"
#include "statUi.h"


statUi::statUi()
{
}


statUi::~statUi()
{
}


HRESULT statUi::init()
{
	for (int i = 0; i < 5; i++)
	{
		_rc[i] = RectMake(110, 50 + 50 *i, 50, 50);
	}
	_kind = 0;
	y = 50;
	

	for (int i = 0; i < 5; i++)
	{
		_hp[i] = new progressBar;
		_hp[i]->init(L"UI/stat_hp", L"UI/stat_maxhp", 635, 60 + 50 * i, 230, 10);
	}
	

	return S_OK;

}
void statUi::release()
{


}
void statUi::update()
{

	if (_kind > 0 && KEYMANAGER->isOnceKeyDown('W'))
	{
		y -= 50;
		_kind -= 1;
	}
	if (_kind < 4 && KEYMANAGER->isOnceKeyDown('S'))
	{
		y += 50;
		_kind += 1;
	}
	
	
	
	for (int i = 0; i < 5; i++)
	{
		_hp[i]->setGauge(STATMANAGER->getPlayerStat()[i]._hp, STATMANAGER->getPlayerStat()[i]._maxHp);

	}
	/*_hp[0]->setGauge(STATMANAGER->getPlayerStat()[0]._hp, STATMANAGER->getPlayerStat()[0]._maxHp);
	_hp[1]->setGauge(STATMANAGER->getPlayerStat()[1]._hp, STATMANAGER->getPlayerStat()[1]._maxHp);
	_hp[2]->setGauge(STATMANAGER->getPlayerStat()[2]._hp, STATMANAGER->getPlayerStat()[2]._maxHp);
	_hp[3]->setGauge(STATMANAGER->getPlayerStat()[3]._hp, STATMANAGER->getPlayerStat()[3]._maxHp);
	_hp[4]->setGauge(STATMANAGER->getPlayerStat()[4]._hp, STATMANAGER->getPlayerStat()[4]._maxHp);
*/

	_selectRC = RectMake(50, y, 50, 50);
	STATMANAGER->update();
}
void statUi::render()
{
	showstatUI();
}


void statUi::showstatUI()
{
	IMAGEMANAGER->findImage(L"StatMain")->render(100, 0, false, 1);
	IMAGEMANAGER->findImage(L"StatUI")->render(0, WINSIZEY - 300, false, 0.5f);
	IMAGEMANAGER->findImage(L"StatUI1")->render(0, WINSIZEY - 300, false, 1);
	IMAGEMANAGER->findImage(L"MenuMouse")->render(_selectRC.left, _selectRC.top, false, 1);

	IMAGEMANAGER->findImage(L"AdellFace")->render(_rc[0].left, _rc[0].top,50,50, false, 1);
	IMAGEMANAGER->findImage(L"RozalinFace")->render(_rc[1].left, _rc[1].top,50,50, false, 1);
	IMAGEMANAGER->findImage(L"PramFace")->render(_rc[2].left, _rc[2].top,50,50, false, 1);
	IMAGEMANAGER->findImage(L"ValvatorezFace")->render(_rc[3].left, _rc[3].top,50,50, false, 1);
	IMAGEMANAGER->findImage(L"ClericFace")->render(_rc[4].left, _rc[4].top,50,50, false, 1);

	
	if(y == 50) IMAGEMANAGER->findImage(L"AdellFace")->render(5, 670,195,195 ,false, 1);
	if (y == 100) IMAGEMANAGER->findImage(L"RozalinFace")->render(5, 670, 195, 195, false, 1);
	if (y == 150) IMAGEMANAGER->findImage(L"PramFace")->render(5, 670, 195, 195, false, 1);
	if (y == 200) IMAGEMANAGER->findImage(L"ValvatorezFace")->render(5, 670, 195, 195, false, 1);
	if (y == 250) IMAGEMANAGER->findImage(L"ClericFace")->render(5, 670, 195, 195, false, 1);


	WCHAR str[128];
	
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[0]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"±Ã¼­Ã¼", 30, str, 535, 45, 580, 50);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[1]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"°íµñ", 30, str, 535, 95, 580, 100);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[2]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"°íµñ", 30, str, 535, 145, 580, 150);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[3]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"°íµñ", 30, str, 535, 195, 580, 200);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[4]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"°íµñ", 30, str, 535, 245, 580, 250);


	//ÇÇÅë,¿¥ÇÇÅë


	swprintf_s(str, L"%d", _kind);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2 + 100, WINSIZEY / 2 + 100);


	swprintf_s(str, L"%d / %d", STATMANAGER->getPlayerStat()[_kind]._hp, STATMANAGER->getPlayerStat()[_kind]._maxHp);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 825, 665, 1000, 700);

	swprintf_s(str, L"%d / %d", STATMANAGER->getPlayerStat()[_kind]._sp, STATMANAGER->getPlayerStat()[_kind]._maxSp);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 825, 710, 1000, 780);




	//°ø°Ý·ÂÂÊ
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._atk);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 500, 760, 550, 790);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._int);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 500, 790, 550, 810);


	//¹æ¾î·ÂºÎºÐ
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._def);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 870, 760, 950, 790);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._res);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 870, 790, 950, 800);

	//·¹º§ºÎºÐ
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 150, 860, 200, 910);


	//Ä«¿îÅÍ,¿òÁ÷ÀÏ¼öÀÖ´ÂÅ¸ÀÏ¼ö,Á¡ÇÁÇÒ¼öÀÖ´Â³ôÀÌ,´øÁú¼öÀÖ´ÂÅ¸ÀÏ¼ö
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._counter);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 495, 860, 530, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._mov);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 650, 860, 690, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._jm);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 820, 860, 870, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._thr);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"°íµñ", 30, str, 985, 860, 1020, 910);

	
	for (int i = 0; i < 5; i++)
	{
		_hp[i]->render(false,1);
	}
	
}