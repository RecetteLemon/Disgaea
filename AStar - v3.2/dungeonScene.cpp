#include "stdafx.h"
#include "dungeonScene.h"


dungeonScene::dungeonScene()
{
}


dungeonScene::~dungeonScene()
{
}
HRESULT dungeonScene::init()
{
	this->loadFile();

	_aStar = new aStar;
	_aStar->init();

	_aStar->loadCurrentMap(_tile);

	return S_OK;
}
void dungeonScene::release()
{

}
void dungeonScene::update()
{
	this->camControl();
	this->coordinateUpdate();
}
void dungeonScene::render()
{
//	this->drawTile();
	_aStar->render();
}
void dungeonScene::loadFile()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"CurFile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
void dungeonScene::drawTile()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 < 22) continue;
		if (-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + 624) continue;
		if (_tile[i].ter == TER_NONE) continue;

		IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[i].x - TILESIZEX / 2,
			_tile[i].y - _tile[i].z,
			_tile[i].terFrame.x, _tile[i].terFrame.y, true, 1.0f);

	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 < 22) continue;
		if (-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + 624) continue;
		if (_tile[i].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
			_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
			_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
	}
}
void dungeonScene::camControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x <= 0 + 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y <= 0 + 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x >= WINSIZEX - 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y >= WINSIZEY - 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	}
}
void dungeonScene::coordinateUpdate()
{

}