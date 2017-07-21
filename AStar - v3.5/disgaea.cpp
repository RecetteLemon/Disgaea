#include "stdafx.h"
#include "disgaea.h"


disgaea::disgaea()
{
}


disgaea::~disgaea()
{
}

//초기화 해주는 함수
HRESULT disgaea::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene(L"LoadingScene", new loadingScene);
	SCENEMANAGER->addScene(L"MenuScene", new menuScene);
	SCENEMANAGER->addScene(L"MapToolScene", new mapToolScene);
	SCENEMANAGER->addScene(L"DungeonScene", new dungeonScene);
	SCENEMANAGER->addScene(L"TestScene", new testScene);
	SCENEMANAGER->changeScene(L"LoadingScene");


	return S_OK;
}

//메모리 해제 함수
void disgaea::release(void)
{
	gameNode::release();


}

//연산해주는 곳
void disgaea::update(void)
{
	gameNode::update();
	SCENEMANAGER->update();
	
}

//여기가 그려주는 곳
void disgaea::render(void)
{
	if (DIRECT2D->_renderTarget->CheckWindowState() != D2D1_WINDOW_STATE_OCCLUDED)
	{
		DIRECT2D->beginDraw();
		//==============================================================================


		SCENEMANAGER->render();


		//================================================================================
		//건들지마라 이거도
		TIMEMANAGER->render();
		DIRECT2D->endDraw();
		DIRECT2D->reCreateResource();
	}
}
