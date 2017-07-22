#include "stdafx.h"
#include "townScene.h"


townScene::townScene()
{
}


townScene::~townScene()
{
}
HRESULT townScene::init()
{
	_cm = new characterManager;
	_cm->init(2, 5);
	_cm->selectPlayer(3);

	
	this->loadTile();
	return S_OK;
}
void townScene::release()
{

}
void townScene::update()
{
	this->camControl();
	_cm->update();
	
}
void townScene::render()
{
	this->drawTile();
	_cm->render();
	
}
void townScene::drawTile()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		for (int j = 0; j <= _tile[i].z; j++)
		{
			IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[i].x - TILESIZEX / 2,
				_tile[i].y - j * TILESIZEZ,
				_tile[i].terFrame.x, _tile[i].terFrame.y, true, 1.0f);
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tile[i].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
			_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
			_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
	}
}
void townScene::camControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	}
}
void townScene::loadTile()
{
	CAMERAMANAGER->setPosition(INITX - WINSIZEX / 2, INITY + 22);
	HANDLE file;
	DWORD read;
	file = CreateFile(L"Tile/Town/TownTile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}