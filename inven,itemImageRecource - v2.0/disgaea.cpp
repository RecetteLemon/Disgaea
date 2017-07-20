#include "stdafx.h"
#include "disgaea.h"


disgaea::disgaea()
{
}


disgaea::~disgaea()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT disgaea::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("LoadingScene", new loadingScene);
	SCENEMANAGER->addScene("MenuScene", new menuScene);
	SCENEMANAGER->addScene("MapToolScene", new mapToolScene);
	SCENEMANAGER->addScene("TestScene", new testScene);
	SCENEMANAGER->changeScene("LoadingScene");


	return S_OK;
}

//�޸� ���� �Լ�
void disgaea::release(void)
{
	gameNode::release();


}

//�������ִ� ��
void disgaea::update(void)
{
	gameNode::update();
	SCENEMANAGER->update();
	
}

//���Ⱑ �׷��ִ� ��
void disgaea::render(void)
{
	DIRECT2D->beginDraw();
	//==============================================================================
	
	
	SCENEMANAGER->render();


	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render();
	DIRECT2D->endDraw();
}
