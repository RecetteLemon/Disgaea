#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
public:
	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:

	void release(void);


	/*
	===================================================================
	�̹��� �߰�
	===================================================================
	*/

	//���ҽ����� �̹��� �߰�
	//Image* AddImage(string strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor, BOOL useAlphaBlend = false);

	//�Ϲ� �̹��� �߰�
	image* addImage(string strKey, LPCWSTR fileName, int width, int height);

	//������ �̹��� �߰�
	image* addFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY);




	//�̹��� ã�� �Լ�
	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll(void);



	/*
	===================================================================
	���� �Լ� - Left Top �������� ����
	===================================================================
	*/


	//�⺻ ���
	void render(string strKey, float opacity);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����
	void render(string strKey, float destX, float destY, float opacity);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���̤� ����
	void render(string strKey, float destX, float destY, int showWidth, int showHeight, float opacity);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(string strKey, float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void render(string strKey, float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);





	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float opacity);

	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void frameRender(string strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float opacity);


	//���� ���� - Image::LoopRender ���� �ʿ�
	//void LoopRender(string strKey, const LPRECT drawArea, int offSetX = 0, int offSetY = 0, float opacity = 1.0f);



	imageManager();
	~imageManager();
};

