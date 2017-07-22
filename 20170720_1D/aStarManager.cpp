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

//A* �˰����� ������ ĳ���� �߰�
aStar* aStarManager::addAStar(tagIso* currentMap, wstring strKey, int startX, int startY)
{
	//������ Ű ���� �ִ��� �˻�
	aStar* as = findAStar(strKey);

	//�ִٸ� �װ��� ��ȯ
	if (as) return as;

	//���ٸ� �޸� ���� �Ҵ�
	as = new aStar;

	//�ʱ�ȭ�ϰ� �������� ��� �޸� ����
	if (FAILED(as->init(currentMap, startX, startY)))
	{
		SAFE_DELETE(as);

		return NULL;
	}

	//�ʿ� �߰�
	_mAStarList.insert(make_pair(strKey, as));
	
	return as;
}

//�˰����� ������ ĳ���� ã�� 
aStar* aStarManager::findAStar(wstring strKey)
{
	mapAStarIter key = _mAStarList.find(strKey);

	if (key != _mAStarList.end())
		return key->second;

	return NULL;
}


//���̻� �˰����� ������ �ʿ䰡 ���ٸ� ���� 
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

//��� �� ��
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

	//�������� ����ϰ�
	_mAStarList.clear();

	return TRUE;
}