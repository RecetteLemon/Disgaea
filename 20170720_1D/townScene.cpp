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
	this->playerTileCol();
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
		if ((-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 > 22 ||
			-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 < 22 + TILEMONITORSIZEW ||
			-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22 ||
			-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + TILEMONITORSIZEH))
		{
			for (int j = 0; j < _tile[i].z + 1; j++)
			{
				IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[i].x - TILESIZEX / 2,
					_tile[i].y - j * TILESIZEZ,
					_tile[i].terFrame.x, _tile[i].terFrame.y, true, 1.0f);
			}

			if (_tile[i].z <= 0)
			{
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[0].x, _tile[i].line[0].y, _tile[i].line[1].x, _tile[i].line[1].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[1].x, _tile[i].line[1].y, _tile[i].line[2].x, _tile[i].line[2].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[2].x, _tile[i].line[2].y, _tile[i].line[3].x, _tile[i].line[3].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[3].x, _tile[i].line[3].y, _tile[i].line[0].x, _tile[i].line[0].y, true, 1);
			}

			if (_tile[i].obj != OBJ_ERASE)
			{
				IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
					_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() - TILESIZEY * (_tile[i].z - 1),
					_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
			}
		}
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
void townScene::playerTileCol()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (_tile[i].z > 0 || _tile[i].ter == TER_WALL)
		{
			if (PtInRegion(hRgn, _cm->getShadowRC().left, _cm->getShadowRC().bottom))
			{
				_cm->playerTileCol(0);
				break;
			}
			else if (PtInRegion(hRgn, _cm->getShadowRC().right, _cm->getShadowRC().bottom))
			{
				_cm->playerTileCol(1);
				break;
			}
			else if (PtInRegion(hRgn, _cm->getShadowRC().left, _cm->getShadowRC().top))
			{
				//_num = i;
				_cm->playerTileCol(2);
				break;
			}
			else if (PtInRegion(hRgn, _cm->getShadowRC().right, _cm->getShadowRC().top))
			{
				_cm->playerTileCol(3);
				break;
			}
			else _cm->playerTileCol(4);
		}
		DeleteObject(hRgn);
	}
}
