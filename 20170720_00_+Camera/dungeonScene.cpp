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
	this->drawTile();
}
void dungeonScene::loadFile()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"CurFile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY * TILEZ, &read, NULL);
	CloseHandle(file);
}
void dungeonScene::drawTile()
{
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[x][y][z].x - TILESIZEX / 2,
			_tile[x][y][z].y - _tile[x][y][z].z,
			_tile[x][y][z].terFrame.x, _tile[x][y][z].terFrame.y, true, 1.0f);
	}
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		if (_tile[x][y][z].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[x][y][z].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"isoObject")->getFrameWidth() + TILESIZEX,
			_tile[x][y][z].y - _tile[x][y][z].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
			_tile[x][y][z].objFrame.x, _tile[x][y][z].objFrame.y, true, 1.0f);
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
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		_tile[x][y][z].x = WINSIZEX / 2 + _tile[x][y][z].iso.left * TILESIZEX / 2 - (_tile[x][y][z].iso.top + z) * TILESIZEX / 2;
		_tile[x][y][z].y = WINSIZEY / 2 - TILEMAXSIZEY / 2 + _tile[x][y][z].iso.left * TILESIZEY / 2 + (_tile[x][y][z].iso.top + z) * TILESIZEY / 2;
		_tile[x][y][z].line[0] = { _tile[x][y][z].x, _tile[x][y][z].y - _tile[x][y][z].z };
		_tile[x][y][z].line[1] = { _tile[x][y][z].x - TILESIZEX / 2, _tile[x][y][z].y + TILESIZEY / 2 - _tile[x][y][z].z };
		_tile[x][y][z].line[2] = { _tile[x][y][z].x, _tile[x][y][z].y + TILESIZEY - _tile[x][y][z].z };
		_tile[x][y][z].line[3] = { _tile[x][y][z].x + TILESIZEX / 2, _tile[x][y][z].y + TILESIZEY / 2 - _tile[x][y][z].z };
	}
}