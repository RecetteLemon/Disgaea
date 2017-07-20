#include "stdafx.h"
#include "cameraManager.h"
HRESULT cameraManager::init()
{
	_x = _y = 0;
	return S_OK;
}
void cameraManager::release()
{

}
void cameraManager::render(HDC hdc)
{
	/*wchar_t str[100];
	wsprintf(str, L"xCamera: %d, yCamera: %d", (int)-_x, (int)-_y);
	TextOutW(hdc, 0, 80, str, wcslen(str));*/
}