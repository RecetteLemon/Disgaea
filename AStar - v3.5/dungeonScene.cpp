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

	_tank = new tankk;
	_tank->init();

	_tank->setPosition(_tile[0].centerX, _tile[0].centerY);

	_aStar->link(_tank);

	_aStar->setStartTile(_tank->getCenter().x + CAMERAMANAGER->getX(), _tank->getCenter().y + CAMERAMANAGER->getY());

	return S_OK;
}
void dungeonScene::release()
{

}
void dungeonScene::update()
{
	//gameNode::update();
	this->camControl();
	this->coordinateUpdate();
	_tank->update();
	_aStar->update();
	//_aStar->setStartTile(_tank->getCenter().x + CAMERAMANAGER->getX(), _tank->getCenter().y + CAMERAMANAGER->getY());
	
	POINT mouse;
	mouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	mouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hrgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hrgn, mouse.x, mouse.y))
		{
			_tile[i].edgePaint = true;

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_aStar->setEndTile(_tile[i]);
			}
		}
		else _tile[i].edgePaint = false;

		DeleteObject(hrgn);
	}
}
void dungeonScene::render()
{
	this->drawTile();
	_aStar->render();
	_tank->render();
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
		//if (-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 < 22) continue;
		//if (-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		//if (-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22) continue;
		//if (-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + 624) continue;
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
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tile[i].edgePaint) IMAGEMANAGER->findImage(L"IsoEdge")->render(_tile[i].x - TILESIZEX / 2, _tile[i].y - _tile[i].z, true, 1);
	}
}
void dungeonScene::camControl()
{
	if (KEYMANAGER->isStayKeyDown('A') || _ptMouse.x <= 0 + 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown('W') || _ptMouse.y <= 0 + 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	}
	if (KEYMANAGER->isStayKeyDown('D') || _ptMouse.x >= WINSIZEX - 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown('S') || _ptMouse.y >= WINSIZEY - 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	}
}
void dungeonScene::coordinateUpdate()
{

}