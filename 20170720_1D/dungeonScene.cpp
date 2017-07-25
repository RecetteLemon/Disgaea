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


	_tileIndex = 0;
	_cm = new characterManager;
	_cm->init(2, 5);
	_cm->selectPlayer(0);

	//a* 알고리즘을 적용할 캐릭터 수 만큼 호출
	//	ASTARMANAGER->addAStar(_tile, _cm->getName(), _cm->getPlayerX(), _cm->getPlayerY());
	//							현재맵, 캐릭터명, 캐릭터 시작점

	_tileNum = 0;
	_isMoveStart = false;
	_findPlayer = false;

	_rcEdge = RectMakeCenter(0, 0, 192, 96);
	_edgeNum = 0;
	_edgeMouseMove = false;
	_edgeMouseY = 0;
	_edge = IMAGEMANAGER->findImage(L"DungeonEdge");
	_edgeMouse = IMAGEMANAGER->findImage(L"DungeonEdgeMouse");

	return S_OK;
}
void dungeonScene::release()
{
	
}
void dungeonScene::update()
{
	this->camControl();
	this->coordinateUpdate();
	this->aStarMove();
	_cm->update();
}
void dungeonScene::render()
{
	this->drawTile();
	//_cm->render();

	//차례가 된 캐릭터(플레이어)의 moveList 표시
	//ASTARMANAGER->findAStar(_cm->getName())->renderGoalList();
	//적은 안표시요 

	ASTARMANAGER->render();
	ASTARMANAGER->renderGoalList();
	ASTARMANAGER->drawMovableTile();
}
void dungeonScene::loadFile()
{
	HANDLE file;
	DWORD read;
	file = CreateFile(L"Tile/Dungeon/DungeonTile2.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	CloseHandle(file);
}
void dungeonScene::drawTile()
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
				if (_tile[i].z > 0)
				{
					IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[i].x - TILESIZEX / 2,
						_tile[i].y - j * TILESIZEZ,
						_tile[i].terFrame.x, _tile[i].terFrame.y, true, 1.0f);
				}
			}

			if (_tile[i].z <= 0)
			{
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[0].x, _tile[i].line[0].y, _tile[i].line[1].x, _tile[i].line[1].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[1].x, _tile[i].line[1].y, _tile[i].line[2].x, _tile[i].line[2].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[2].x, _tile[i].line[2].y, _tile[i].line[3].x, _tile[i].line[3].y, true, 1);
				DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[i].line[3].x, _tile[i].line[3].y, _tile[i].line[0].x, _tile[i].line[0].y, true, 1);
			}

			if (_edgeNum == i)
			{
				if (_tile[_edgeNum].z >= 0)
				{
					_edge->render(_rcEdge.left, _rcEdge.top - _tile[i].z * TILESIZEZ, true, 1.0);
					_edgeMouse->render(_rcEdge.left, _rcEdge.top - 100 + _edgeMouseY - _tile[i].z * TILESIZEZ, true, 1.0);
				}
				else
				{
					_edge->render(_rcEdge.left, _rcEdge.top, true, 1.0);
					_edgeMouse->render(_rcEdge.left, _rcEdge.top - 100 + _edgeMouseY, true, 1.0);
				}
			}

			if (_tile[i].obj != OBJ_ERASE)
			{
				IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[i].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
					_tile[i].y - _tile[i].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() - TILESIZEY * (_tile[i].z - 1),
					_tile[i].objFrame.x, _tile[i].objFrame.y, true, 1.0f);
			}

			if (_tileIndex == i) _cm->render();
		}
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
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, _cm->getShadowRC().left + 40, _cm->getShadowRC().bottom + 20))
		{
			_tileIndex = i;
		}

		DeleteObject(hRgn);
	}


	POINT mouse;
	mouse.x = CAMERAMANAGER->getX() + _ptMouse.x;
	mouse.y = CAMERAMANAGER->getY() + _ptMouse.y;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, mouse.x, mouse.y))
		{
			_rcEdge.left = (_tile[i].x - TILESIZEX / 2) + (_rcEdge.left - (_tile[i].x - TILESIZEX / 2)) * 0.3;
			_rcEdge.right = _rcEdge.left + 96;
			_rcEdge.top = _tile[i].y + (_rcEdge.top - _tile[i].y) * 0.3;
			_rcEdge.bottom = _rcEdge.top + 48;
		}

		DeleteObject(hRgn);
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, _rcEdge.left + 96, _rcEdge.top + 48))
		{
			_edgeNum = i;
		}

		DeleteObject(hRgn);
	}

	if (_edgeMouseMove)
	{
		_edgeMouseY += 1;

		if (_edgeMouseY > 15)
		{
			_edgeMouseMove = false;
		}
	}
	else
	{
		_edgeMouseY -= 1;

		if (_edgeMouseY < -15)
		{
			_edgeMouseMove = true;
		}
	}
}

void dungeonScene::aStarMove()
{
	//움직일때(예외처리)
	if (ASTARMANAGER->getMoveTile().size() != NULL && _isMoveStart)
	{
		if ((int)_cm->getPlayerCenter().x < ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getPlayerCenter().y < ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setPlayerState(PLAYER_STAT_RB_MOVE);
			_cm->moveOn();
		}
		else if ((int)_cm->getPlayerCenter().x > ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getPlayerCenter().y < ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setPlayerState(PLAYER_STAT_LB_MOVE);
			_cm->moveOn();
		}
		else if ((int)_cm->getPlayerCenter().x < ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getPlayerCenter().y > ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setPlayerState(PLAYER_STAT_RT_MOVE);
			_cm->moveOn();
		}
		else if ((int)_cm->getPlayerCenter().x > ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
			(int)_cm->getPlayerCenter().y > ASTARMANAGER->getMoveTile()[_tileNum].centerY)
		{
			_cm->setPlayerState(PLAYER_STAT_LT_MOVE);
			_cm->moveOn();
		}

		switch (_cm->getPlayerStat())
		{
		case PLAYER_STAT_RB_MOVE:
			if (_cm->getPlayerCenter().x >= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
				_cm->getPlayerCenter().y >= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
			{
				_cm->setPlayerState(PLAYER_STAT_RB_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_LB_MOVE:
			if (_cm->getPlayerCenter().x <= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
				_cm->getPlayerCenter().y >= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
			{
				_cm->setPlayerState(PLAYER_STAT_LB_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_RT_MOVE:
			if (_cm->getPlayerCenter().x >= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
				_cm->getPlayerCenter().y <= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
			{
				_cm->setPlayerState(PLAYER_STAT_RT_STAND);
				++_tileNum;
			}
			break;
		case PLAYER_STAT_LT_MOVE:
			if (_cm->getPlayerCenter().x <= ASTARMANAGER->getMoveTile()[_tileNum].centerX &&
				_cm->getPlayerCenter().y <= ASTARMANAGER->getMoveTile()[_tileNum].centerY)
			{
				_cm->setPlayerState(PLAYER_STAT_LT_STAND);
				++_tileNum;
			}
			break;
		}
		if (_tileNum >= ASTARMANAGER->getMoveTile().size())
		{
			ASTARMANAGER->vectorClear();
			_tileNum = 0;
			_isMoveStart = false;
			_findPlayer = false;
		}
	}

	//움직이지 않을때(예외처리)
	if (!_isMoveStart)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);
			HRGN playerTile = CreatePolygonRgn(_tile[i].line, 4, WINDING);

			//실시간으로 플레이어 위치를 받아서 스타트타일 셋팅
			if (!_findPlayer)
			{
				if (PtInRegion(playerTile, _cm->getPlayerCenter().x, _cm->getPlayerCenter().y))
				{
					//키 값에 현재 맵 값과 시작좌표(타일배열번호)를 넘겨줍니다!
					ASTARMANAGER->setCurrentMap(_tile, i);
					ASTARMANAGER->getMovablePath(_tile, i, 3);
					_findPlayer = true;
				}
			}

			if (PtInRegion(hRgn, _ptMouse.x + CAMERAMANAGER->getX(), _ptMouse.y + CAMERAMANAGER->getY()))
			{
				_tile[i].edgePaint = true;

				if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
				{
					//키 값에 도착좌표(타일배열번호)를 넘겨줍니다!
					ASTARMANAGER->setGoalTile(i);
					//키 값에 길찾기를 시작합니다!
					ASTARMANAGER->startPathFinder();
					_isMoveStart = true;
				}
			}
			else _tile[i].edgePaint = false;

			DeleteObject(hRgn);
			DeleteObject(playerTile);

			if (_isMoveStart) break;
		}
	}

}