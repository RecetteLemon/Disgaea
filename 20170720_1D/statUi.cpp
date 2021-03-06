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
		_hp[i]->init(L"UI/stat_hp", L"UI/stat_maxhp", 635, 64 + 52 * i, 230, 10);
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

	
	WCHAR str[128];
	if (y == 50)
	{
		IMAGEMANAGER->findImage(L"AdellFace")->render(5, 670, 195, 195, false, 1);
		swprintf_s(str, L"ADELL");
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 28, str, 50, 615, 400, 615);
	}
	if (y == 100)

	{
		IMAGEMANAGER->findImage(L"RozalinFace")->render(5, 670, 195, 195, false, 1);
		swprintf_s(str, L"ROZALIN");
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 28, str, 50, 615, 400, 615);
	}
	if (y == 150)
	{
		IMAGEMANAGER->findImage(L"PramFace")->render(5, 670, 195, 195, false, 1);
		swprintf_s(str, L"PRAM");
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 28, str, 50, 615, 400, 615);
	}
	if (y == 200)
	{
		IMAGEMANAGER->findImage(L"ValvatorezFace")->render(5, 670, 195, 195, false, 1);
		swprintf_s(str, L"VALVATOREZ");
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 28, str, 50, 615, 400, 615);
	}
	if (y == 250)
	{
		IMAGEMANAGER->findImage(L"ClericFace")->render(5, 670, 195, 195, false, 1);
		swprintf_s(str, L"CLERIC");
		DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 28, str, 50, 615, 400, 615);
	}


	
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[0]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 30, str, 535, 45 + 2, 580, 50 + 2);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[1]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 30, str, 535, 95 + 2 + 2, 580, 100 + 2 + 2);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[2]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 30, str, 535, 145 + 2 + 2 + 2, 580, 150 + 2 + 2 + 2);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[3]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 30, str, 535, 195 + 2 + 2 + 2 + 2, 580, 200 + 2 + 2 + 2 + 2);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[4]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 30, str, 535, 245 + 2 + 2 + 2 + 2 + 2, 580, 250 + 2 + 2 + 2 + 2 + 2);


	swprintf_s(str, L"Adell");
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 28, str, _rc[0].right + 100, 50 + 2, _rc[0].right + 300, 50 + 2);
	swprintf_s(str, L"Rozalin");
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 28, str, _rc[1].right + 100, 100 + 2 + 2, _rc[1].right + 300, 100 + 2 + 2);
	swprintf_s(str, L"Pram");
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 28, str, _rc[2].right + 100, 150 + 2 + 2 + 2, _rc[2].right + 300, 150 + 2 + 2 + 2);
	swprintf_s(str, L"Valvatorez");
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 28, str, _rc[3].right + 100, 200 + 2 + 2 + 2 + 2, _rc[3].right + 300, 200 + 2 + 2 + 2 + 2);
	swprintf_s(str, L"Cleric");
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(0, 0, 0), 1), L"����", 28, str, _rc[4].right + 100, 250 + 2 + 2 + 2 + 2, _rc[4].right + 300, 250 + 2 + 2 + 2 + 2);


	

	//����,������

	swprintf_s(str, L"%d / %d", STATMANAGER->getPlayerStat()[_kind]._hp, STATMANAGER->getPlayerStat()[_kind]._maxHp);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 825, 665, 1000, 700);

	swprintf_s(str, L"%d / %d", STATMANAGER->getPlayerStat()[_kind]._sp, STATMANAGER->getPlayerStat()[_kind]._maxSp);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 825, 710, 1000, 780);




	//���ݷ���
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._atk);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 500, 760, 550, 790);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._int);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 500, 790, 550, 810);


	//���ºκ�
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._def);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 870, 760, 950, 790);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._res);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 870, 790, 950, 800);

	//�����κ�
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._lv);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 150, 860, 200, 910);


	//ī����,�����ϼ��ִ�Ÿ�ϼ�,�����Ҽ��ִ³���,�������ִ�Ÿ�ϼ�
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._counter);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 495, 860, 530, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._mov);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 650, 860, 690, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._jm);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 820, 860, 870, 910);
	swprintf_s(str, L"%d", STATMANAGER->getPlayerStat()[_kind]._thr);
	DIRECT2D->drawTextD2D(DIRECT2D->createBrush(RGB(255, 255, 255), 1), L"����", 30, str, 985, 860, 1020, 910);

	
	for (int i = 0; i < 5; i++)
	{
		_hp[i]->render(false,1);
	}
	
}