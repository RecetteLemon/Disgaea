#pragma once
#include "gameNode.h"
#include "image.h"

//�� Ÿ�� �԰� 32 32X32
#define TILESIZE 64

//�� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�� �� �԰�
#define OBJTILEX 8
#define OBJTILEY 7
#define GROUNDTILEX 10
#define GROUNDTILEY 5

enum TILESET
{
	GROUNDTILE, OBJTILE, ENDTILE
};

enum SAVENLOAD
{
	TILE_SAVE, TILE_LOAD, SLEND
};

struct tagImageSetting
{
	image* img;
	RECT rc;
	RECT objRc[OBJTILEX * OBJTILEY];
	RECT groundRc[GROUNDTILEX * GROUNDTILEY];
	float x, y;

};


class tileMapUI : public gameNode
{
private:
	tagImageSetting _uiImage;
	tagImageSetting _listImage[ENDTILE];
	tagImageSetting _tileImage[ENDTILE]; // obj, tile;
	

	RECT _selectRect[ENDTILE];
	RECT _listRect[ENDTILE];
	RECT _tileRect;

	TILESET _tileInfo;


	float _saveX, _saveY;

	bool _tileCollision;	// Ÿ�� �̹����� �Դ�
	bool _listCollision;	// Ÿ�� ����Ʈ �̹����� �Դ�
	bool _rectSetting;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSetting();
	void lButtonClick();

	
	//		���� Ÿ���� ������Ʈ���� ����� �������� ��ȯ
	inline TILESET getTileInfo() { return _tileInfo; }
	inline int getGroundTileFrameX() { return _listImage[GROUNDTILE].img->getFrameX(); }
	inline int getGroundTileFrameY() { return _listImage[GROUNDTILE].img->getFrameY(); }
	inline int getObjTileFrameX() { return _listImage[OBJTILE].img->getFrameX(); }
	inline int getObjTileFrameY() { return _listImage[OBJTILE].img->getFrameY(); }





	tileMapUI();
	~tileMapUI();
};

