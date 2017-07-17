#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}



HRESULT loadItem::initForImage(string keyName, const WCHAR* fileName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;


	return S_OK;
}


HRESULT loadItem::initForFrameImage(string keyName, const WCHAR* fileName, int width, int height,
	int frameX, int frameY)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;

	return S_OK;
}


loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	//_background = IMAGEMANAGER->addImage("�ε���׶���", "����������.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//_loadingBar = new progressBar;
	//_loadingBar->init("loadingBarTop", "loadingBarBottom", WINSIZEX / 2, WINSIZEY - 20, WINSIZEX, 20);
	//_loadingBar->setGauge(0, 0);

	//_currentGauge = 0;
	
	return S_OK;
}

void loading::release()
{
	//SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	//_loadingBar->update();
}

void loading::render() 
{
	//_background->render(getMemDC(), 0 ,0);
	//_loadingBar->render();
}




void loading::loadImage(string keyName, const WCHAR* fileName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height);

	_vLoadItem.push_back(item);
}


void loading::loadFrameImage(string keyName, const WCHAR* fileName, int width, int height, int frameX, int frameY)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY);

	_vLoadItem.push_back(item);
}



//�ε��ϴ� ��
BOOL loading::loadingDone()
{

	//�ε� �������� �ö󰣴ٴ� ���� �޸𸮿� �̹���, ���� ���� �ö󰡰��ְ�,
	//���ͻ������ ���ų� ũ�ٴ� ����. �ε��� �����ٴ� �� �ǹ�
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height);
		}
		break;

		

		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY);
		}
		break;


		case LOAD_KIND_SOUND:
		{
			//����� ����!!! ����!!!
		}
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	_currentGauge++;


	return FALSE;
}
