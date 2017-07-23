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
	_tileNum = 0;

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

	// 마우스
	POINT mouse;

	mouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	mouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	if (ASTARMANAGER->getMoveTile().size() != NULL)
	{
		if ((int)_cm->getCenter().x < ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y < ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_RB_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x > ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y < ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_LB_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x < ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y > ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_RT_MOVE);
			_cm->moveOn();
		}
		if ((int)_cm->getCenter().x > ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getCenter().y > ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setState(PLAYER_STAT_LT_MOVE);
			_cm->moveOn();
		}

		switch (_cm->getStat())
		{
			case PLAYER_STAT_RB_MOVE:
				if (_cm->getCenter().x >= ASTARMANAGER->getMoveTile()[_tileNum].centerX && 
					_cm->getCenter().y >= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
					++_tileNum;
				break;
			case PLAYER_STAT_LB_MOVE:
				if (_cm->getCenter().x <= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
					_cm->getCenter().y >= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
					++_tileNum;
				break;
			case PLAYER_STAT_RT_MOVE:
				if (_cm->getCenter().x >= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
					_cm->getCenter().y <= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
					++_tileNum;
				break;
			case PLAYER_STAT_LT_MOVE:
				if (_cm->getCenter().x <= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
					_cm->getCenter().y <= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
					++_tileNum;
				break;
		}
		if (_tileNum >= ASTARMANAGER->getMoveTile().size())
		{
			_tileNum = 0;
			ASTARMANAGER->moveListUpdate();
		}
	}
	

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);
		HRGN playerTile = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		//실시간으로 플레이어 위치를 받아서 스타트타일 셋팅
		if (PtInRegion(playerTile, _cm->getCenter().x, _cm->getCenter().y))
		{
			ASTARMANAGER->setStartTile(i);
		}

		if (PtInRegion(hRgn, mouse.x, mouse.y))
		{
			_tile[i].edgePaint = true;

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				ASTARMANAGER->setEndTile(i);
				_findWay = true;
			}
		}
		else _tile[i].edgePaint = false;

		DeleteObject(hRgn);
		DeleteObject(playerTile);
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