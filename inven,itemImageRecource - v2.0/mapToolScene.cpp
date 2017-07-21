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
	_sample[SAM_TERRAIN] = IMAGEMANAGER->findImage("isoTerrain");
	_sample[SAM_OBJECT] = IMAGEMANAGER->findImage("isoObject");
	_sample[SAM_ERASER] = IMAGEMANAGER->findImage("isoEraser");
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

	for (int i = 0; i < TILEY; i++) for (int j = 0; j < TILEX; j++)
	{
		_tile[i * TILEX + j].iso = RectMake(j, i, 1, 1);
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tile[i].screen.x = WINSIZEX / 2 + _tile[i].iso.left * TILESIZEX / 2 - _tile[i].iso.top * TILESIZEX / 2;
		_tile[i].screen.y = WINSIZEY / 2 - TILEMAXSIZEY / 2 + _tile[i].iso.left * TILESIZEY / 2 + _tile[i].iso.top * TILESIZEY / 2;
		_tile[i].line[0] = { _tile[i].screen.x - TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2 };
		_tile[i].line[1] = { _tile[i].screen.x, _tile[i].screen.y + TILESIZEY };
		_tile[i].line[2] = { _tile[i].screen.x + TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2 };
		_tile[i].line[3] = { _tile[i].screen.x, _tile[i].screen.y };
		_tile[i].ter = TER_LOAD;
		_tile[i].obj = OBJ_ERASE;
		_tile[i].terFrame.x = 0;
		_tile[i].terFrame.y = 0;
		_tile[i].objFrame.x = 0;
		_tile[i].objFrame.y = 0;
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
	//IMAGEMANAGER->findImage("menuz")->render(0, 0);
}
void mapToolScene::coordinateUpdate()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tile[i].screen.x = WINSIZEX / 2 + _tile[i].iso.left * TILESIZEX / 2 - _tile[i].iso.top * TILESIZEX / 2;
		_tile[i].screen.y = WINSIZEY / 2 - TILEMAXSIZEY / 2 + _tile[i].iso.left * TILESIZEY / 2 + _tile[i].iso.top * TILESIZEY / 2;
		_tile[i].line[0] = { _tile[i].screen.x - TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2 };
		_tile[i].line[1] = { _tile[i].screen.x, _tile[i].screen.y + TILESIZEY };
		_tile[i].line[2] = { _tile[i].screen.x + TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2 };
		_tile[i].line[3] = { _tile[i].screen.x, _tile[i].screen.y };
	}

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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || _ptMouse.x <= 0 + 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) || _ptMouse.y <= 0 + 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() + 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || _ptMouse.x >= WINSIZEX - 5)
	{
		CAMERAMANAGER->setX(CAMERAMANAGER->getX() - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || _ptMouse.y >= WINSIZEY - 5)
	{
		CAMERAMANAGER->setY(CAMERAMANAGER->getY() - 10);
	}
}
void mapToolScene::setTile()
{

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

		for (int i = 0; i < TILEX * TILEY; i++)
		{
			HRGN hRgn = CreatePolygonRgn(_tile[i].line, 4, WINDING);
			if (PtInRegion(hRgn, _ptMouse.x, _ptMouse.y) && !PtInRect(&_phaseSample.rc, _ptMouse) && !_phaseSample.isMove)
			{
				switch (_phaseSample.cur)
				{
				case SAM_TERRAIN:
					_tile[i].terFrame.x = _curTile.x;
					_tile[i].terFrame.y = _curTile.y;
					_tile[i].ter = this->terCreater({ _curTile.x, _curTile.y });
					break;
				case SAM_OBJECT:
					_tile[i].objFrame.x = _curTile.x;
					_tile[i].objFrame.y = _curTile.y;
					_tile[i].obj = this->objCreater({ _curTile.x, _curTile.y });
					break;
				case SAM_ERASER:
					_tile[i].objFrame.x = _curTile.x;
					_tile[i].objFrame.y = _curTile.y;
					_tile[i].obj = OBJ_ERASE;
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
	/*for (int i = 0; i < TILEX * TILEY; i++)
	{
		MoveToEx(_tile[i].screen.x, _tile[i].screen.y, NULL);
		LineTo(getMemDC(), _tile[i].screen.x - TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2);
		LineTo(getMemDC(), _tile[i].screen.x, _tile[i].screen.y + TILESIZEY);
		LineTo(getMemDC(), _tile[i].screen.x + TILESIZEX / 2, _tile[i].screen.y + TILESIZEY / 2);
		LineTo(getMemDC(), _tile[i].screen.x, _tile[i].screen.y);
	}*/

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->findImage("isoTerrain")->frameRender(_tile[i].screen.x - TILESIZEX / 2,
			_tile[i].screen.y,
			_tile[i].terFrame.x, _tile[i].terFrame.y);
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tile[i].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage("isoObject")->frameRender(_tile[i].screen.x - TILESIZEX / 2 - IMAGEMANAGER->findImage("isoObject")->getFrameWidth() + TILESIZEX,
			_tile[i].screen.y - IMAGEMANAGER->findImage("isoObject")->getFrameHeight() + TILESIZEY,
			_tile[i].objFrame.x, _tile[i].objFrame.y);
	}
}
void mapToolScene::drawSample()
{
	//for (int i = 0; i < SAMX * SAMY; i++) Rectangle(getMemDC(), _tileSample[i].rc.left, _tileSample[i].rc.top, _tileSample[i].rc.right, _tileSample[i].rc.bottom);
	_sample[_phaseSample.cur]->render(_phaseSample.rc.left, _phaseSample.rc.top);

}
void mapToolScene::initButton()
{
	for (int i = 0; i < BTN_END; i++)
	{
		_btn[(SAMPLE_TYPE)i] = new button;
	}
	_btn[BTN_START]->init("startButton", WINSIZEX - IMAGEMANAGER->findImage("saveButton")->getFrameWidth() * 3 + IMAGEMANAGER->findImage("saveButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("saveButton")->getFrameHeight() + IMAGEMANAGER->findImage("saveButton")->getFrameHeight() / 2, { 0, 1 }, { 0, 0 });
	_btn[BTN_SAVE]->init("saveButton", WINSIZEX - IMAGEMANAGER->findImage("saveButton")->getFrameWidth() * 2 + IMAGEMANAGER->findImage("saveButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("saveButton")->getFrameHeight() + IMAGEMANAGER->findImage("saveButton")->getFrameHeight() / 2, { 0, 1 }, { 0, 0 });
	_btn[BTN_LOAD]->init("loadButton", WINSIZEX - IMAGEMANAGER->findImage("saveButton")->getFrameWidth() + IMAGEMANAGER->findImage("saveButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("saveButton")->getFrameHeight() + IMAGEMANAGER->findImage("saveButton")->getFrameHeight() / 2, { 0, 1 }, { 0, 0 });
	_btn[BTN_TERRAIN]->init("terrainButton", WINSIZEX - IMAGEMANAGER->findImage("terrainButton")->getFrameWidth() + IMAGEMANAGER->findImage("terrainButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("terrainButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage("saveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
	_btn[BTN_OBJECT]->init("objectButton", WINSIZEX - IMAGEMANAGER->findImage("objectButton")->getFrameWidth() + IMAGEMANAGER->findImage("objectButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("objectButton")->getFrameHeight() - IMAGEMANAGER->findImage("objectButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage("saveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
	_btn[BTN_ERASER]->init("eraseButton", WINSIZEX - IMAGEMANAGER->findImage("eraseButton")->getFrameWidth() + IMAGEMANAGER->findImage("eraseButton")->getFrameWidth() / 2, WINSIZEY - IMAGEMANAGER->findImage("eraseButton")->getFrameHeight() * 2 - IMAGEMANAGER->findImage("eraseButton")->getFrameHeight() / 2 - IMAGEMANAGER->findImage("saveButton")->getFrameHeight(), { 0, 1 }, { 0, 0 });
}
void mapToolScene::updateButton()
{
	for (int i = 0; i < BTN_END; i++) _btn[(SAMPLE_TYPE)i]->update();
	if (_btn[BTN_TERRAIN]->getPush() == TRUE) _phaseSample.cur = SAM_TERRAIN;
	if (_btn[BTN_OBJECT]->getPush() == TRUE) _phaseSample.cur = SAM_OBJECT;
	if (_btn[BTN_ERASER]->getPush() == TRUE) _phaseSample.cur = SAM_ERASER;
	if (_btn[BTN_SAVE]->getPush() == TRUE) this->saveTile();
	if (_btn[BTN_LOAD]->getPush() == TRUE) this->loadTile();
}
void mapToolScene::drawButton()
{
	for (int i = 0; i < BTN_END; i++) _btn[(SAMPLE_TYPE)i]->render();
}
void mapToolScene::saveTile()
{
	OPENFILENAME save;
	char filePathSize[1028] = "*.map";
	ZeroMemory(&save, sizeof(OPENFILENAME));
	save.lStructSize = sizeof(OPENFILENAME);
	save.hwndOwner = NULL;
	save.lpstrFile = filePathSize;
	save.nMaxFile = sizeof(filePathSize);
	save.nFilterIndex = true;
	save.lpstrFileTitle = NULL;
	save.nMaxFileTitle = NULL;
	save.lpstrInitialDir = NULL;
	save.lpstrDefExt = "*.map";
	save.lpstrFilter = "맵 파일(*.map)\0*.map\0모든 파일(*.*)\0*.*";
	save.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;
	if (GetSaveFileName(&save) == FALSE) return;
	char temp[1028];
	strncpy_s(temp, strlen(save.lpstrFile) + 1, save.lpstrFile, strlen(save.lpstrFile));
	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
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
	char filePathSize[1028] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "맵 파일(*.map)\0*.map\0모든 파일(*.*)\0*.*";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == FALSE) return;
	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));
	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);
	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
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
	return TER_LOAD;
}
OBJECT_TYPE mapToolScene::objCreater(POINT tile)
{
	return OBJ_ITEM;
}