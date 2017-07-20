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
	_sample[SAM_TERRAIN] = IMAGEMANAGER->findImage(L"IsoTerrain");
	_sample[SAM_OBJECT] = IMAGEMANAGER->findImage(L"IsoObject");
	_sample[SAM_ERASER] = IMAGEMANAGER->findImage(L"IsoEraser");
	_phaseSample.x = WINSIZEX / 2;
	_phaseSample.y = WINSIZEY / 2;
	_phaseSample.cur = SAM_TERRAIN;
	_phaseSample.rc = RectMakeCenter(_phaseSample.x, _phaseSample.y, SAMMAXSIZEX, SAMMAXSIZEY);
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

	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		_tile[x][y][z].iso = RectMake(x, y - z, 1, 1);
		_tile[x][y][z].edgePaint = false;
	}

	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		_tile[x][y][z].x = INITX + _tile[x][y][z].iso.left * TILESIZEX / 2 - (_tile[x][y][z].iso.top + z) * TILESIZEX / 2;
		_tile[x][y][z].y = INITY + _tile[x][y][z].iso.left * TILESIZEY / 2 + (_tile[x][y][z].iso.top + z) * TILESIZEY / 2;
		_tile[x][y][z].z = z * TILESIZEZ;
		_tile[x][y][z].line[0] = { _tile[x][y][z].x, _tile[x][y][z].y - _tile[x][y][z].z };
		_tile[x][y][z].line[1] = { _tile[x][y][z].x - TILESIZEX / 2, _tile[x][y][z].y + TILESIZEY / 2 - _tile[x][y][z].z };
		_tile[x][y][z].line[2] = { _tile[x][y][z].x, _tile[x][y][z].y + TILESIZEY - _tile[x][y][z].z };
		_tile[x][y][z].line[3] = { _tile[x][y][z].x + TILESIZEX / 2, _tile[x][y][z].y + TILESIZEY / 2 - _tile[x][y][z].z };

		_tile[x][y][z].ter = TER_LOAD;
		_tile[x][y][z].obj = OBJ_ERASE;
		_tile[x][y][z].terFrame.x = 1;
		_tile[x][y][z].terFrame.y = 0;
		_tile[x][y][z].objFrame.x = 0;
		_tile[x][y][z].objFrame.y = 0;
	}


	this->initButton();

	return S_OK;
}
void mapToolScene::release()
{

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
		_phaseSample.rc = RectMakeCenter(_phaseSample.x, _phaseSample.y, SAMMAXSIZEX, SAMMAXSIZEY);
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

	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		HRGN hRgn = CreatePolygonRgn(_tile[x][y][z].line, 4, WINDING);

		if (PtInRegion(hRgn, mouse.x, mouse.y))
		{
			_tile[x][y][z].edgePaint = true;
		}
		else _tile[x][y][z].edgePaint = false;

		DeleteObject(hRgn);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMX * SAMY; i++)
		{
			if (PtInRect(&_tileSample[i].rc, _ptMouse))
			{
				_curTile.x = _tileSample[i].frame.x;
				_curTile.y = _tileSample[i].frame.y;
				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_phaseSample.rc, _ptMouse) && !_phaseSample.isMove)
		{
			_phaseSample.isMove = true;
			_phaseSample.token.x = _ptMouse.x - _phaseSample.x;
			_phaseSample.token.y = _ptMouse.y - _phaseSample.y;
		}

		for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
		{
			HRGN hRgn = CreatePolygonRgn(_tile[x][y][z].line, 4, WINDING);
			if (PtInRegion(hRgn, mouse.x, mouse.y) && !PtInRect(&_phaseSample.rc, _ptMouse) && !_phaseSample.isMove)
			{
				switch (_phaseSample.cur)
				{
				case SAM_TERRAIN:
					_tile[x][y][z].terFrame.x = _curTile.x;
					_tile[x][y][z].terFrame.y = _curTile.y;
					_tile[x][y][z].ter = this->terCreater({ _curTile.x, _curTile.y });
					break;
				case SAM_OBJECT:
					_tile[x][y][z].objFrame.x = _curTile.x;
					_tile[x][y][z].objFrame.y = _curTile.y;
					_tile[x][y][z].obj = this->objCreater({ _curTile.x, _curTile.y });
					break;
				case SAM_ERASER:
					_tile[x][y][z].objFrame.x = _curTile.x;
					_tile[x][y][z].objFrame.y = _curTile.y;
					_tile[x][y][z].obj = OBJ_ERASE;
					break;
				}
			}
			DeleteObject(hRgn);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_phaseSample.isMove = false;
		_phaseSample.token.x = 0;
		_phaseSample.token.y = 0;
	}
	if (_phaseSample.isMove)
	{
		_phaseSample.x = _ptMouse.x - _phaseSample.token.x;
		_phaseSample.y = _ptMouse.y - _phaseSample.token.y;
	}
}
void mapToolScene::drawTile()
{
	IMAGEMANAGER->findImage(L"IsoBackground")->render(0, 0, false, 1);
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		IMAGEMANAGER->findImage(L"IsoTerrain")->frameRender(_tile[x][y][z].x - TILESIZEX / 2,
			_tile[x][y][z].y - _tile[x][y][z].z,
			_tile[x][y][z].terFrame.x, _tile[x][y][z].terFrame.y, true, 1.0f);
	}
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		if (_tile[x][y][z].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"IsoObject")->frameRender(_tile[x][y][z].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"IsoObject")->getFrameWidth() + TILESIZEX,
			_tile[x][y][z].y - _tile[x][y][z].z - IMAGEMANAGER->findImage(L"IsoObject")->getFrameHeight() + TILESIZEY,
			_tile[x][y][z].objFrame.x, _tile[x][y][z].objFrame.y, true, 1.0f);
	}
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[x][y][z].line[0].x, _tile[x][y][z].line[0].y, _tile[x][y][z].line[1].x, _tile[x][y][z].line[1].y, true, 1);
		DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[x][y][z].line[1].x, _tile[x][y][z].line[1].y, _tile[x][y][z].line[2].x, _tile[x][y][z].line[2].y, true, 1);
		DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[x][y][z].line[2].x, _tile[x][y][z].line[2].y, _tile[x][y][z].line[3].x, _tile[x][y][z].line[3].y, true, 1);
		DIRECT2D->drawLine(DIRECT2D->_defaultBrush, _tile[x][y][z].line[3].x, _tile[x][y][z].line[3].y, _tile[x][y][z].line[0].x, _tile[x][y][z].line[0].y, true, 1);
	}
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		if (_tile[x][y][z].edgePaint) IMAGEMANAGER->findImage(L"IsoEdge")->render(_tile[x][y][z].x - TILESIZEX / 2, _tile[x][y][z].y - _tile[x][y][z].z, true, 1);
	}
	IMAGEMANAGER->findImage(L"IsoEdgeFrame")->render(0, 0, false, 1);
}
void mapToolScene::drawSample()
{
	//for (int i = 0; i < SAMX * SAMY; i++) Rectangle(getMemDC(), _tileSample[i].rc.left, _tileSample[i].rc.top, _tileSample[i].rc.right, _tileSample[i].rc.bottom);
	_sample[_phaseSample.cur]->render(_phaseSample.rc.left, _phaseSample.rc.top, false, 1.0f);

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
	if (_btn[BTN_ERASER]->getPush() == TRUE) _phaseSample.cur = SAM_ERASER;
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
	CAMERAMANAGER->setPosition(0, 0);
	HANDLE file;
	DWORD write;
	file = CreateFile(L"CurFile.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(tagIso) * TILEX * TILEY * TILEZ, &write, NULL);
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
	WriteFile(file, _tile, sizeof(tagIso) * TILEX * TILEY * TILEZ, &write, NULL);
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
	ReadFile(file, _tile, sizeof(tagIso) * TILEX * TILEY * TILEZ, &read, NULL);
	DeleteObject(&ofn);
	CloseHandle(file);
}
TERRAIN_TYPE mapToolScene::terCreater(POINT tile)
{
	if (tile.x == 0 && tile.y == 0) return TER_WALL;
	if (tile.x == 8 && tile.y == 3) return TER_WALL;
	if (tile.x == 9 && tile.y == 3) return TER_WALL;
	if (tile.x == 9 && tile.y == 4) return TER_WALL;
	for (int i = 1; i < 9; i++)
	{
		if (tile.x == i && tile.y == 2) return TER_WALL;
	}
	for (int i = 0; i < 8; i++)
	{
		if (tile.x == i && tile.y == 1) return TER_WALL;
	}
	return TER_LOAD;
}
OBJECT_TYPE mapToolScene::objCreater(POINT tile)
{
	return OBJ_ITEM;
}