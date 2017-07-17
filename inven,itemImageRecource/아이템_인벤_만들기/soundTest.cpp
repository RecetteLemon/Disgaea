#include "stdafx.h"
#include "soundTest.h"


soundTest::soundTest()
{
}


soundTest::~soundTest()
{
}

HRESULT soundTest::init()
{
	SOUNDMANAGER->addSound("닌자참치", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("닌자참치2", "Kalimba.mp3", true, true);
	SOUNDMANAGER->addSound("닌자참치3", "Kalimba.mp3", true, true);

	

	return S_OK;
}

void soundTest::release()
{

}

void soundTest::update()
{
	//SOUNDMANAGER->play("닌자참치", 0.8f);


	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		SOUNDMANAGER->play("닌자참치", 0.8f);
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		SOUNDMANAGER->stop("닌자참치");
	}


	if (KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->pause("닌자참치");
	}

	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		SOUNDMANAGER->resume("닌자참치");
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->play("닌자참치2", 1.0f);
	}

	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		SOUNDMANAGER->play("닌자참치3", 1.0f);
	}
}