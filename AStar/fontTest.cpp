#include "stdafx.h"
#include "fontTest.h"


fontTest::fontTest()
{
}


fontTest::~fontTest()
{
}

HRESULT fontTest::init()
{

	return S_OK;
}

void fontTest::release()
{

}

void fontTest::update()
{

}

void fontTest::render()
{
	//TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, "무조건 완성해라", strlen("무조건 완성해라"));
	
	//CreateFont로 글자 출력하기
	char str[128];
	HFONT oldFont, font1;
	
	/*
	CreateFont(40,				//문자폭
		0,						//문자 넓이
		40,						//문자 기울기(각도)
		0,						//문자 방향
		600,					//문자 굵기
		0,						//bool 문자 기울기 true, false
		0,						//bool 문자 밑줄칠지 true, false
		0,						//bool 문자 취소선 true, false
		HANGUL_CHARSET,			//문자 셋팅
		0,						//출력 정확도
		0,						//클리핑 정확도
		0,						//출력의 퀄리티
		0,						//자간
		TEXT("궁서체"));
	*/

	font1 = CreateFont(80, 0, 0, 0, 300, true, 1, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("돋움체"));
	oldFont = (HFONT)SelectObject(getMemDC(), font1);
	sprintf(str, "치킨먹지마");
	TextOut(getMemDC(), 10, 100, str, strlen(str));
	DeleteObject(font1);

	RECT rcText = RectMake(10, 300, 400, 100);

	HFONT font2 = CreateFont(80, 0, 0, 0, 300, false, false, false, 
		DEFAULT_CHARSET, OUT_STROKE_PRECIS, CLIP_CHARACTER_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Import"));

	HFONT oldfont2 = (HFONT)SelectObject(getMemDC(), font2);
	DrawText(getMemDC(), TEXT("SUCCESS"), 8, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DeleteObject(oldfont2);
	DeleteObject(font2);


}
