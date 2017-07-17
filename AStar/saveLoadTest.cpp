#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) load();
}

void saveLoadTest::save(void)
{
	//파일 입출력
	//C - FILE*
	//C++ - ifstream, ofstream
	//WIN32 - CreateFile

	//슈팅게임에 꼭 들어가야할 기능
	//HPBar, Save & Load, 

	HANDLE file;

	char str[128] = "기남아 주말에 고생했다";
	DWORD write;

	file = CreateFile("지영이꺼어딨어.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load(void)
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile("지영이꺼어딨어.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "올~희남", MB_OK);
}