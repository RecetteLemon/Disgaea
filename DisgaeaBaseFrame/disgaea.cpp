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



}

//여기가 그려주는 곳
void disgaea::render(void)
{
	DIRECT2D->beginDraw();
	//==============================================================================
	
	
	


	//================================================================================
	//건들지마라 이거도
	TIMEMANAGER->render();
	DIRECT2D->endDraw();
	

	

}
