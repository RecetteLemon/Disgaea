#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	_btnAngleDown = new button;
	_btnAngleDown->init("¹öÆ°", WINSIZEX / 2 + 250, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbAngleDown);

	_btnAngleUp = new button;
	_btnAngleUp->init("¹öÆ°", WINSIZEX / 2 - 250, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbAngleUp);

	

	return S_OK;
}

void selectScene::release()
{

}

void  selectScene::update()
{
	_btnSceneChange->update();
	_btnAngleDown->update();
	_btnAngleUp->update();
}

void  selectScene::render()
{
	_btnSceneChange->render();
	_btnAngleDown->render();
	_btnAngleUp->render();

	char str[128];

	sprintf(str, "¿©±ä ¼¿·ºÆ® ¾À");
	TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));
}

void selectScene::cbSceneChange(void)
{
	SCENEMANAGER->changeScene("°ÔÀÓ¾À");
}

void selectScene::cbAngleUp(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle + 0.2f);
}

void selectScene::cbAngleDown(void)
{
	DATABASE->setElementDataAngle("battle", DATABASE->getElementData("battle")->angle - 0.2f);
}