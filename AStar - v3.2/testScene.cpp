#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{

}


HRESULT testScene::init(void)
{

	_character1 = new character1;
	_character1->init(L"Valvatorez", WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}
void testScene::release(void)
{

}
void testScene::update(void) 
{
	_character1->update();

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10.0f);
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10.0f);

	if (KEYMANAGER->isStayKeyDown(VK_OEM_6)) CAMERAMANAGER->setZoomSize(CAMERAMANAGER->getZoomSize() + 0.01);
	if (KEYMANAGER->isStayKeyDown(VK_OEM_4)) CAMERAMANAGER->setZoomSize(CAMERAMANAGER->getZoomSize() - 0.01);

}
void testScene::render(void) 
{
	_character1->render();
}