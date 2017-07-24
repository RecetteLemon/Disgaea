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
	_mUI = new menuUI;
	_mUI->init();

	_cm = new characterManager;
	_cm->init(2, 5);
	_cm->selectPlayer(3);
	_tileNum = 0;
	_tileIndex = 0;
	this->loadTile();

	_npc = IMAGEMANAGER->addFrameImage(L"npc", L"image/face/NPC.png", 588, 156, 6, 1);

	_npcFrame = new animation;
	_npcFrame->init(588, 156, 98, 156);
	_npcFrame->setDefPlayFrame(false, true);
	_npcFrame->setFPS(1);
	_npcFrame->start();


	return S_OK;
}
void townScene::release()
{

}
void townScene::update()
{
	_mUI->update();
	this->playerTileCol();
	this->camControl();
	_cm->update();
	_npcFrame->frameUpdate(0.2);
	
	
}
void townScene::render()
{
	this->drawTile();
	_mUI->render();
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
			IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[i].x - TILESIZEX / 2,
				_tile[i].y,
				_tile[i].terFrame.x, _tile[i].terFrame.y, true, 1.0f);
			
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if ((-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 > 22 ||
			-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 < 22 + TILEMONITORSIZEW ||
			-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22 ||
			-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + TILEMONITORSIZEH))
		{
			for (int j = 1; j < _tile[i].z + 1; j++)
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

			if (_tile[i].obj == OBJ_NPC)
			{
				_npc->aniRender(_tile[i].x - TILESIZEX / 2 - _npc->getFrameWidth() + TILESIZEX - 38,
					_tile[i].y - _tile[i].z - _npc->getFrameHeight() - TILESIZEY * (_tile[i].z - 1) - 30,
					_npcFrame, true, 1.0);
			}

			if (_tile[i].obj != OBJ_ERASE)
			{
				if (_tile[i].obj == OBJ_HOUSERENDER)
				{
					//	if(_tile[i].indexX )
					IMAGEMANAGER->findImage(L"obj_house")->render(_tile[i].x - (TILESIZEX * 4) / 2,
						_tile[i].y + TILESIZEY - IMAGEMANAGER->findImage(L"obj_house")->getHeight(), true, 1.0f);
				}
				else if (_tile[i].obj != OBJ_HOUSE)
				{
					if (_tile[i].objFrame.x == 5 && _tile[i].objFrame.y == 1)
					{
						IMAGEMANAGER->findImage(L"Tree")->render(_tile[i].x - IMAGEMANAGER->findImage(L"Tree")->getWidth() / 2,
							_tile[i].y - IMAGEMANAGER->findImage(L"Tree")->getHeight() / 2 - TILESIZEZ / 2, true, 1.0f);
					}
					else if (_tile[i].obj != OBJ_NPC)
					{
						IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
							_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() - TILESIZEY * (_tile[i].z - 1),
							_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
					}
				}
			}
			
		}
		if (_tileIndex == i) _cm->render();
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
	file = CreateFile(L"Tile/Town/TownTile2.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
void townScene::playerTileCol()
{

	
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (_tile[i].z > 0 || _tile[i].ter == TER_WALL || _tile[i].ter == TER_VOID)
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

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, _cm->getShadowRC().left + 50, _cm->getShadowRC().top + 20))
		{
			_tileIndex = i;
		}

		DeleteObject(hRgn);
	}
}
