#include "stdafx.h"
#include "mapToolScene.h"


mapToolScene::mapToolScene()
{
}


mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	ZeroMemory(&_tileSample, sizeof(tagSample) * TILEX * TILEY);
	ZeroMemory(&_tile, sizeof(tagIso) * TILEX * TILEY);
	ZeroMemory(&_phaseSample, sizeof(tagSamplePhase));

	_sample[SAM_TERRAIN] = IMAGEMANAGER->findImage(L"IsoTerrain");
	_sample[SAM_OBJECT] = IMAGEMANAGER->findImage(L"IsoObject");
	_sample[SAM_OBJ_ERASER] = IMAGEMANAGER->findImage(L"IsoEraser");
	_phaseSample.x = 1359;
	_phaseSample.y = 124;
	_phaseSample.cur = SAM_TERRAIN;
	_phaseSample.rc = RectMakeCenter(_phaseSample.x, _phaseSample.y, 192, 192);
	_phaseSample.token = { 0, 0 };
	_phaseSample.isMove = false;
	_curTile.x = _curTile.y = 0;
	
	for (int i = 0; i < SAMY; i++) for (int j = 0; j < SAMX; j++)
	{
		_tileSample[i * SAMX + j].frame.x = j;
		_tileSample[i * SAMX + j].frame.y = i;
		SetRect(&_tileSample[i * SAMX + j].rc, _phaseSample.rc.left + j * SAMSIZEX,
			_phaseSample.rc.top + i * SAMSIZEY, _phaseSample.rc.left + j * SAMSIZEX + SAMSIZEX, _phaseSample.rc.top + i * SAMSIZEY + SAMSIZEY);
	}

	_sampleTile.frame.x = 0;
	_sampleTile.frame.y = 0;
	_sampleTile.rc = RectMakeCenter(_phaseSample.x, _phaseSample.y, 192, 192);

	for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		_tile[TILEX * y + x].iso = RectMake(x, y, 1, 1);
		_tile[TILEX * y + x].indexX = x;
		_tile[TILEX * y + x].indexY = y;
		_tile[TILEX * y + x].indexZ = 0;
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tile[i].x = INITX + _tile[i].iso.left * TILESIZEX / 2 - (_tile[i].iso.top) * TILESIZEX / 2;
		_tile[i].y = INITY + _tile[i].iso.left * TILESIZEY / 2 + (_tile[i].iso.top) * TILESIZEY / 2;
		_tile[i].z = 0;
		_tile[i].line[0] = { _tile[i].x, _tile[i].y};
		_tile[i].line[1] = { _tile[i].x - TILESIZEX / 2, _tile[i].y + TILESIZEY / 2};
		_tile[i].line[2] = { _tile[i].x, _tile[i].y + TILESIZEY };
		_tile[i].line[3] = { _tile[i].x + TILESIZEX / 2, _tile[i].y + TILESIZEY / 2 };
		_tile[i].centerX = _tile[i].x;
		_tile[i].centerY = _tile[i].y + TILESIZEY / 2;

		_tile[i].ter = TER_LOAD;
		_tile[i].obj = OBJ_ERASE;
		_tile[i].terFrame.x = 1;
		_tile[i].terFrame.y = 0;
		_tile[i].objFrame.x = 0;
		_tile[i].objFrame.y = 0;


		_tile[i].clickCheck = false;
	}

	_vertical = 1;

	this->initButton();

	_btnTileRight = RectMake(1459, 250, 50, 50);
	_btnTileLeft = RectMake(1209, 250, 50, 50);

	return S_OK;
}
void mapToolScene::release()
{
	for (int i = 0; i < BTN_END; i++)
	{
		_btn[i]->release();
		SAFE_DELETE(_btn[i]);
	}
}
void mapToolScene::update()
{
	this->updateButton();
	this->setTile();
	this->camControl();

	this->coordinateUpdate();
}
void mapToolScene::render()
{
	this->drawTile();
	this->drawSample();

	this->drawButton();
}
void mapToolScene::coordinateUpdate()
{
	for (int i = 0; i < SAMY; i++) for (int j = 0; j < SAMX; j++)
	{
		_phaseSample.rc = RectMakeCenter(_phaseSample.x, _phaseSample.y, 192, 192);
		_tileSample[i * SAMX + j].frame.x = j;
		_tileSample[i * SAMX + j].frame.y = i;
		SetRect(&_tileSample[i * SAMX + j].rc, _phaseSample.rc.left + j * SAMSIZEX,
			_phaseSample.rc.top + i * SAMSIZEY, _phaseSample.rc.left + j * SAMSIZEX + SAMSIZEX, _phaseSample.rc.top + i * SAMSIZEY + SAMSIZEY);
	}
}
void mapToolScene::camControl()
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
void mapToolScene::setTile()
{
	POINT mouse;

	mouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	mouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);

		if (PtInRegion(hRgn, mouse.x, mouse.y))
		{
			_tile[i].edgePaint = true;
		}
		else _tile[i].edgePaint = false;

		DeleteObject(hRgn);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_btnTileRight, _ptMouse))
		{
			switch (_phaseSample.cur)
			{
			case SAM_TERRAIN:
				++_phaseSample.token.x;
				if (_phaseSample.token.x > _sample[SAM_TERRAIN]->getMaxFrameX()) _phaseSample.token.x = 0;
				break;
			case SAM_OBJECT:
				++_phaseSample.token.x;
				if (_phaseSample.token.x > 4 && _phaseSample.token.y == 4)
				{
					_phaseSample.token.x = 0;
					++_phaseSample.token.y;
				}
				else if (_phaseSample.token.x > _sample[SAM_OBJECT]->getMaxFrameX())
				{
					_phaseSample.token.x = 0;
					++_phaseSample.token.y;
					if (_phaseSample.token.y > _sample[SAM_OBJECT]->getMaxFrameY()) _phaseSample.token.y = 0;
				}
				break;
			}
			
		}

		if (PtInRect(&_btnTileLeft, _ptMouse))
		{
			switch (_phaseSample.cur)
			{
			case SAM_TERRAIN:
				--_phaseSample.token.x;
				if (_phaseSample.token.x < 0) _phaseSample.token.x = _sample[SAM_OBJECT]->getMaxFrameX();
				break;
			case SAM_OBJECT:
				--_phaseSample.token.x;
				if (_phaseSample.token.x < 0 && _phaseSample.token.y == 5)
				{
					_phaseSample.token.x = 4;
					--_phaseSample.token.y;
				}
				else if (_phaseSample.token.x < 0)
				{
					_phaseSample.token.x = _sample[SAM_OBJECT]->getMaxFrameX();
					--_phaseSample.token.y;
					if (_phaseSample.token.y < 0) _phaseSample.token.y = _sample[SAM_OBJECT]->getMaxFrameY();
				}
				break;
			}
			
		}

		if (PtInRect(&_sampleTile.rc, _ptMouse))
		{
			_curTile.x = _phaseSample.token.x;
			_curTile.y = _phaseSample.token.y;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < TILEX * TILEY; i++) for (int j = 0; j < TILEZ; j++)
		{		
			if (_tile[i].clickCheck) continue;
			HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);
			if (PtInRegion(hRgn, mouse.x, mouse.y) && !PtInRect(&_phaseSample.rc, _ptMouse) && !_phaseSample.isMove && _tile[i].z == j)
			{
				switch (_phaseSample.cur)
				{
				case SAM_TERRAIN:
					if (this->terCreater({ _curTile.x, _curTile.y }) == TER_VOID)
					{
						_tile[i].z = 0;
						_tile[i].terFrame.x = _curTile.x;
						_tile[i].terFrame.y = _curTile.y;
						_tile[i].ter = this->terCreater({ _curTile.x, _curTile.y });
						_tile[i].clickCheck = true;
					}
					else
					{
						if (this->terCreater({ _tile[i].terFrame.x, _tile[i].terFrame.y }) == TER_VOID)
						{
							_tile[i].z = j;
							_tile[i].terFrame.x = _curTile.x;
							_tile[i].terFrame.y = _curTile.y;
							_tile[i].ter = this->terCreater({ _curTile.x, _curTile.y });
							_tile[i].clickCheck = true;
						}
						else
						{
							if (_tile[i].z < TILEZ - 1) _tile[i].z = j + 1;
							_tile[i].terFrame.x = _curTile.x;
							_tile[i].terFrame.y = _curTile.y;
							_tile[i].ter = this->terCreater({ _curTile.x, _curTile.y });
							_tile[i].clickCheck = true;
						}
					}
					break;
				case SAM_OBJECT:
					_tile[i].objFrame.x = _curTile.x;
					_tile[i].objFrame.y = _curTile.y;
					_tile[i].obj = this->objCreater({ _curTile.x, _curTile.y });
					break;
				case SAM_OBJ_ERASER:
					_tile[i].objFrame.x = _curTile.x;
					_tile[i].objFrame.y = _curTile.y;
					_tile[i].obj = OBJ_ERASE;
					break;
				}
			}		
			DeleteObject(hRgn);
		}
	}
}
void mapToolScene::drawTile()
{
	IMAGEMANAGER->findImage(L"IsoBackground")->render(0, 0, false, 1);

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (-CAMERAMANAGER->getX() + _tile[i].x + TILESIZEX / 2 < 22) continue;
		if (-CAMERAMANAGER->getX() + _tile[i].x - TILESIZEX / 2 > 22 + 1167) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y + TILESIZEY / 2 < 22) continue;
		if (-CAMERAMANAGER->getY() + _tile[i].y - TILESIZEY / 2 > 22 + 624) continue;

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
	IMAGEMANAGER->findImage(L"IsoEdgeFrame")->render(0, 0, false, 1);


	WCHAR ptr[128];
	wsprintf(ptr, L"X : %d, Y : %d", _ptMouse.x, _ptMouse.y);
	DIRECT2D->drawTextD2D(DIRECT2D->_defaultBrush, ptr, 20, 80, 400, 100);
}
void mapToolScene::drawSample()
{
	//_sample[_phaseSample.cur]->render(_phaseSample.rc.left, _phaseSample.rc.top, false, 1.0f);
	_sample[_phaseSample.cur]->frameRender(_phaseSample.rc.left, _phaseSample.rc.top, _phaseSample.token.x, _phaseSample.token.y, false, 1.0f);
}
void mapToolScene::initButton()
{
	for (int i = 0; i < BTN_END; i++)
	{
		_btn[(SAMPLE_TYPE)i] = new button;
	}

	_btn[BTN_LOAD]->init(L"LoadButton", IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() * 3 - IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() / 2 + 22 * 3, WINSIZEY - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() + IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() / 2 - 22, { 0, 1 }, { 0, 0 });
	_btn[BTN_SAVE]->init(L"SaveButton", IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() * 2 - IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() / 2 + 22 * 2, WINSIZEY - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() + IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() / 2 - 22, { 0, 1 }, { 0, 0 });
	_btn[BTN_START]->init(L"StartButton", IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() - IMAGEMANAGER->findImage(L"SaveButton")->getFrameWidth() / 2 + 22, WINSIZEY - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() + IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight() / 2 - 22, { 0, 1 }, { 0, 0 });
	_btn[BTN_TERRAIN]->init(L"TerrainButton", WINSIZEX - IMAGEMANAGER->findImage(L"TerrainButton")->getFrameWidth() + IMAGEMANAGER->findImage(L"TerrainButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage(L"TerrainButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
	_btn[BTN_OBJECT]->init(L"ObjectButton", WINSIZEX - IMAGEMANAGER->findImage(L"ObjectButton")->getFrameWidth() + IMAGEMANAGER->findImage(L"ObjectButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage(L"ObjectButton")->getFrameHeight() - IMAGEMANAGER->findImage(L"ObjectButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
	_btn[BTN_ERASER]->init(L"EraseButton", WINSIZEX - IMAGEMANAGER->findImage(L"EraseButton")->getFrameWidth() + IMAGEMANAGER->findImage(L"EraseButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage(L"EraseButton")->getFrameHeight() * 2 - IMAGEMANAGER->findImage(L"EraseButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage(L"SaveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
}
void mapToolScene::updateButton()
{
	for (int i = 0; i < BTN_END; i++) _btn[(SAMPLE_TYPE)i]->update();
	if (_btn[BTN_TERRAIN]->getPush() == TRUE) _phaseSample.cur = SAM_TERRAIN;
	if (_btn[BTN_OBJECT]->getPush() == TRUE) _phaseSample.cur = SAM_OBJECT;
	if (_btn[BTN_ERASER]->getPush() == TRUE) _phaseSample.cur = SAM_OBJ_ERASER;
	if (_btn[BTN_START]->getPush() == TRUE) this->startTile();
	if (_btn[BTN_SAVE]->getPush() == TRUE) this->saveTile();
	if (_btn[BTN_LOAD]->getPush() == TRUE) this->loadTile();
}
void mapToolScene::drawButton()
{
	for (int i = 0; i < BTN_END; i++) _btn[(SAMPLE_TYPE)i]->render();
}
void mapToolScene::startTile()
{
	CAMERAMANAGER->setPosition(INITX - WINSIZEX / 2, INITY + 22);
	HANDLE file;
	DWORD write;
	file = CreateFile(L"CurFile.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
	SCENEMANAGER->changeScene(L"DungeonScene");
}
void mapToolScene::saveTile()
{
	OPENFILENAME save;
	WCHAR filePathSize[1028] = L"*.map";
	ZeroMemory(&save, sizeof(OPENFILENAME));
	save.lStructSize = sizeof(OPENFILENAME);
	save.hwndOwner = NULL;
	save.lpstrFile = filePathSize;
	save.nMaxFile = sizeof(filePathSize);
	save.nFilterIndex = true;
	save.lpstrFileTitle = NULL;
	save.nMaxFileTitle = NULL;
	save.lpstrInitialDir = NULL;
	save.lpstrDefExt = L"*.map";
	save.lpstrFilter = L"맵 파일(*.map)\0*.map\0모든 파일(*.*)\0*.*";
	save.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	if (GetSaveFileName(&save) == FALSE) return;
	WCHAR temp[1028];
	wcsncpy_s(temp, wcslen(save.lpstrFile) + 1, save.lpstrFile, wcslen(save.lpstrFile));
	WCHAR* context = NULL;
	WCHAR* token = wcstok_s(temp, L"\\", &context);
	while (wcslen(context))
	{
		token = wcstok_s(NULL, L"\\", &context);
	}
	HANDLE file;
	DWORD write;
	file = CreateFile(save.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &write, NULL);
	DeleteObject(&save);
	CloseHandle(file);
}
void mapToolScene::loadTile()
{
	OPENFILENAME ofn;
	WCHAR filePathSize[1028] = L"";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = L"맵 파일(*.map)\0*.map\0모든 파일(*.*)\0*.*";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == FALSE) return;
	WCHAR temp[1028];
	wcsncpy_s(temp, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, wcslen(ofn.lpstrFile));
	WCHAR* context = NULL;
	WCHAR* token = wcstok_s(temp, L"\\", &context);
	while (wcslen(context))
	{
		token = wcstok_s(NULL, L"\\", &context);
	}
	HANDLE file;
	DWORD read;
	file = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY, &read, NULL);
	DeleteObject(&ofn);
	CloseHandle(file);
}
TERRAIN_TYPE mapToolScene::terCreater(POINT tile)
{
	if (tile.x == 0 && tile.y == 0) return TER_VOID;
	if (tile.x == 5 && tile.y == 0) return TER_WALL; //임시로 바꿈

	/*if (tile.x == 8 && tile.y == 3) return TER_WALL;
	if (tile.x == 9 && tile.y == 3) return TER_WALL;
	if (tile.x == 9 && tile.y == 4) return TER_WALL;
	for (int i = 1; i < 9; i++)
	{
		if (tile.x == i && tile.y == 2) return TER_WALL;
	}
	for (int i = 0; i < 8; i++)
	{
		if (tile.x == i && tile.y == 1) return TER_WALL;
	}*/
	return TER_LOAD;
}
OBJECT_TYPE mapToolScene::objCreater(POINT tile)
{
	return OBJ_ITEM;
}