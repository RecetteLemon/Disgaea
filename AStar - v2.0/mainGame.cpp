#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("mapTiles", "mapTiles.bmp", 640, 288, 20, 9, true, RGB(255, 0, 255));
	SCENEMANAGER->addScene("��ã���", new aStarScene);

	SCENEMANAGER->changeScene("��ã���");

	return S_OK;
}

//�޸� ���� �Լ�
void mainGame::release(void)
{
	gameNode::release();


}

//�������ִ� ��
void mainGame::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();
	
}

//���Ⱑ �׷��ִ� ��
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	SCENEMANAGER->render();
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
