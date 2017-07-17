#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,

	LOAD_KIND_FRAMEIMAGE_0,

	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;
	const WCHAR* fileName;
	float x, y;
	int width, height;
	int frameX, frameY;
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public:
	
	HRESULT initForImage(string keyName, const WCHAR* fileName, int width, int height);
	

	HRESULT initForFrameImage(string keyName, const WCHAR* fileName, int width, int height,
		int frameX, int frameY);


	LOAD_KIND getLoadingKind(void) { return _kind; }

	tagImageResource getImageResource(void) { return _imageResource; }

	loadItem();
	~loadItem();
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem		_vLoadItem;

	image*			_background;
	progressBar*	_loadingBar;

	int				_currentGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	
	void loadImage(string keyName, const WCHAR* fileName, int width, int height);
	
	void loadFrameImage(string keyName, const WCHAR* fileName, int width, int height, int frameX, int frameY);
	

	BOOL loadingDone();

	vector<loadItem*> getLoadItem() { return _vLoadItem; }

	loading();
	~loading();
};

