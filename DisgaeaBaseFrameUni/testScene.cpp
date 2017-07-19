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
	_character1->init(L"호석이병신", WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}
void testScene::release(void)
{

}
void testScene::update(void) 
{
	_character1->update();
}
void testScene::render(void) 
{
	_character1->render();
}