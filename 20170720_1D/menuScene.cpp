#include "stdafx.h"
#include "menuScene.h"


menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}
HRESULT menuScene::init()
{
	_menu = MENU_START;
	_mouse = { 615, 530 };

	SOUNDMANAGER->play(L"MenuScene");

	return S_OK;
}
void menuScene::release()
{
	SOUNDMANAGER->stop(L"MenuScene");
}
void menuScene::update()
{
	this->mouseUpdate();
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->play(L"Pick");
		this->keyDownW();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play(L"Pick");
		this->keyDownS();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play(L"Decision");
		this->keyDownSpace();
	}
}
void menuScene::render()
{
	IMAGEMANAGER->findImage(L"Menu")->render(false, 1.0f);
	IMAGEMANAGER->findImage(L"MenuMouse")->render(_mouse.x, _mouse.y, false, 1.0f);

	WCHAR str[100];
	swprintf_s(str, L"x: %d, y: %d", _ptMouse.x, _ptMouse.y);
	DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, str, 500, 50, 200, 70);
}
void menuScene::mouseUpdate()
{
	switch (_menu)
	{
	case MENU_START:
		_mouse = { 635, 540 };
		break;
	case MENU_CONTINUE:
		_mouse = { 635, 597 };
		break;
	case MENU_SETTING:
		_mouse = { 635, 654 };
		break;
	case MENU_CREDITS:
		_mouse = { 635, 711 };
		break;
	case MENU_EXIT:
		_mouse = { 635, 768 };
		break;
	}
}
void menuScene::keyDownW()
{
	switch (_menu)
	{
	case MENU_START:

		break;
	case MENU_CONTINUE:
		_menu = MENU_START;
		break;
	case MENU_SETTING:
		_menu = MENU_CONTINUE;
		break;
	case MENU_CREDITS:
		_menu = MENU_SETTING;
		break;
	case MENU_EXIT:
		_menu = MENU_CREDITS;
		break;
	}
}
void menuScene::keyDownS()
{
	switch (_menu)
	{
	case MENU_START:
		_menu = MENU_CONTINUE;
		break;
	case MENU_CONTINUE:
		_menu = MENU_SETTING;
		break;
	case MENU_SETTING:
		_menu = MENU_CREDITS;
		break;
	case MENU_CREDITS:
		_menu = MENU_EXIT;
		break;
	case MENU_EXIT:

		break;
	}
}
void menuScene::keyDownSpace()
{
	switch (_menu)
	{
	case MENU_START:
		SCENEMANAGER->changeScene(L"TownScene");
		break;
	case MENU_CONTINUE:
		SCENEMANAGER->changeScene(L"ShopScene");
		break;
	case MENU_SETTING:
		//SCENEMANAGER->changeScene();
		break;
	case MENU_CREDITS:
		SCENEMANAGER->changeScene(L"MapToolScene");
		break;
	case MENU_EXIT:
		SCENEMANAGER->changeScene(L"DungeonScene");
		break;
	}
}
