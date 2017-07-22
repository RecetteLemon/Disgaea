#pragma once
#include "singletonBase.h"
#include "aStar.h"
#include <map>

class aStarManager : public singletonBase<aStarManager>
{
public:
	typedef map<wstring, aStar*> mapAStarList;
	typedef map<wstring, aStar*>::iterator mapAStarIter;

private:
	mapAStarList _mAStarList;

public:
	void release(void);

	//A* 알고리즘을 적용할 캐릭터나 적 추가(적용할 맵, 이름, 시작지점)
	aStar* addAStar(tagIso* currentMap, wstring strKey, int startX, int startY);

	//A* 알고리즘을 적용할 캐릭터 찾기 
	aStar* findAStar(wstring strKey);

	BOOL deleteAStar(wstring strKey);

	BOOL deleteAll(void);

	aStarManager();
	~aStarManager();

};