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
	ASTARMANAGER->addAStar(_tile, L"캐릭터", _cm->getCenter().x, _cm->getCenter().y);

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
	this->aStarMove();
	_cm->update();
	_npcFrame->frameUpdate(0.2);
	
	
}
void townScene::render()
{
	this->drawTile();
	ASTARMANAGER->findAStar(L"캐릭터")->render();
	ASTARMANAGER->findAStar(L"캐릭터")->renderGoalList();
	_mUI->render();
}

void townScene::aStarMove()
{
	bool isStart = false;
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);
		HRGN playerTile = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		//실시간으로 플레이어 위치를 받아서 스타트타일 셋팅
		if (PtInRegion(playerTile, _cm->getCenter().x, _cm->getCenter().y))
		{
			ASTARMANAGER->findAStar(L"캐릭터")->setStartTile(i);
		}

		if (PtInRegion(hRgn, _ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY()))
		{
			_tile[i].edgePaint = true;

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				ASTARMANAGER->findAStar(L"캐릭터")->setGoalTile(i);
				ASTARMANAGER->findAStar(L"캐릭터")->pathFinder(ASTARMANAGER->findAStar(L"캐릭터")->getStartTile());
			}
		}
		else _tile[i].edgePaint = false;

		DeleteObject(hRgn);
		DeleteObject(playerTile);
	}

	if (ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile().size() != NULL)
	{
		if ((int)_cm->getCenter().x < ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y < ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_RB_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x > ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y < ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_LB_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x < ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y > ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_RT_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x > ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y > ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_LT_MOVE);
			_cm->moveOn();
		}

		switch (_cm->getStat())
		{
		case PLAYER_STAT_RB_MOVE:
			if (_cm->getCenter().x >= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
				_cm->getCenter().y >= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
			{
				_cm->setState(PLAYER_STAT_RB_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_LB_MOVE:
			if (_cm->getCenter().x <= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
				_cm->getCenter().y >= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
			{
				_cm->setState(PLAYER_STAT_LB_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_RT_MOVE:
			if (_cm->getCenter().x >= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
				_cm->getCenter().y <= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
			{
				_cm->setState(PLAYER_STAT_RT_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_LT_MOVE:
			if (_cm->getCenter().x <= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerX &&
				_cm->getCenter().y <= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile()[_tileNum].centerY)
			{
				_cm->setState(PLAYER_STAT_LT_STAND);
				++_tileNum;
			}
			break;
		}
		if (_tileNum >= ASTARMANAGER->findAStar(L"캐릭터")->getMoveTile().size())
		{
			_tileNum = 0;
		}

		if (ASTARMANAGER->findAStar(L"캐릭터")->getStartTile() == ASTARMANAGER->findAStar(L"캐릭터")->getGoalTile())
		{
			ASTARMANAGER->findAStar(L"캐릭터")->vectorClear();
			ASTARMANAGER->findAStar(L"캐릭터")->moveListUpdate();
		}
	}
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
				if (_tile[i].obj != OBJ_NPC)
				{
					IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
						_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() - TILESIZEY * (_tile[i].z - 1),
						_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
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
