#include "stdafx.h"
#include "aStarManager.h"

aStarManager::aStarManager()
{}

aStarManager::~aStarManager()
{}

void aStarManager::release(void)
{
	deleteAll();
}

//A* 알고리즘을 적용할 캐릭터 추가
aStar* aStarManager::addAStar(tagIso* currentMap, wstring strKey, int startX, int startY)
{
	//동일한 키 값이 있는지 검색
	aStar* as = findAStar(strKey);

	//있다면 그것을 반환
	if (as) return as;

	//없다면 메모리 새로 할당
	as = new aStar;

	//초기화하고 실패했을 경우 메모리 해제
	if (FAILED(as->init(currentMap, startX, startY)))
	{
		SAFE_DELETE(as);

		return NULL;
	}

	//맵에 추가
	_mAStarList.insert(make_pair(strKey, as));
	
	return as;
}

//알고리즘을 적용할 캐릭터 찾기 
aStar* aStarManager::findAStar(wstring strKey)
{
	mapAStarIter key = _mAStarList.find(strKey);

	if (key != _mAStarList.end())
		return key->second;

	return NULL;
}


//더이상 알고리즘을 적용할 필요가 없다면 삭제 
BOOL aStarManager::deleteAStar(wstring strKey)
{
	mapAStarIter key = _mAStarList.find(strKey);

	if (key != _mAStarList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mAStarList.erase(key);

		return true;
	}

	return false;
}

//모두 삭 제
BOOL aStarManager::deleteAll(void)
{
	mapAStarIter iter = _mAStarList.begin();

	for (; iter != _mAStarList.end(); )
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mAStarList.erase(iter);
		}
		else
			++iter;
	}

	//마무리도 깔끔하게
	_mAStarList.clear();

	return TRUE;
}