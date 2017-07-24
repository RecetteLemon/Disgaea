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

	//A* �˰����� ������ ĳ���ͳ� �� �߰�(�̸�)
	//aStar* addAStar(tagIso* currentMap, wstring strKey, int startX, int startY); ���� �Ʒ��� ����(�μ�)
	aStar* addAStar(wstring strKey);

	//A* �˰����� ������ ĳ���� ã�� 
	aStar* findAStar(wstring strKey);

	BOOL deleteAStar(wstring strKey);

	BOOL deleteAll(void);

	aStarManager();
	~aStarManager();

};