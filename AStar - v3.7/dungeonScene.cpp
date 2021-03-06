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

	_cm = new characterManager;
	_cm->init(2, 5);
	_cm->selectPlayer(0);

	ASTARMANAGER->loadCurrentMap(_tile);

	_findWay = false;

	return S_OK;
}
void dungeonScene::release()
{

}
void dungeonScene::update()
{
	this->camControl();
	this->coordinateUpdate();
	_cm->update();

	// ���콺
	POINT mouse;

	mouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	mouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, mouse.x, mouse.y))
		{
			_tile[i].edgePaint = true;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				ASTARMANAGER->loadCurrentMap(_tile);
				ASTARMANAGER->setStartTile(i);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				ASTARMANAGER->setEndTile(i);
				_findWay = true;
			}
		}
		else _tile[i].edgePaint = false;

		DeleteObject(hRgn);
	}

	if (_findWay)
	{
		ASTARMANAGER->pathFinder(ASTARMANAGER->getStartTile());
		_findWay = false;
	}
}
void dungeonScene::render()
{
	this->drawTile();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tile[i].edgePaint)
		{
			if (_tile[i].z >= 0)
			{
				IMAGEMANAGER->findImage(L"IsoEdge")->render(_tile[i].x - TILESIZEX / 2,
					_tile[i].y - _tile[i].z * TILESIZEZ, true, 1);
			}
			else if (_tile[i].z < 0)
			{
				IMAGEMANAGER->findImage(L"IsoEdge")->render(_tile[i].x - TILESIZEX / 2,
					_tile[i].y, true, 1);
			}
		}
	}

	_cm->render();

	ASTARMANAGER->render();
}
void dungeonScene::loadFile()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"Tile/Dungeon/DungeonTile.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
void dungeonScene::drawTile()
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
void dungeonScene::camControl()
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
void dungeonScene::coordinateUpdate()
{

}