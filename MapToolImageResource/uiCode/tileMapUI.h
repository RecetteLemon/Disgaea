#pragma once
#include "gameNode.h"
#include "image.h"

//한 타일 규격 32 32X32
#define TILESIZE 64

//타일 갯수
#define TILEX 10
#define TILEY 10

//총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일 셋 규격
#define OBJTILEX 8
#define OBJTILEY 7
#define GROUNDTILEX 10
#define GROUNDTILEY 5

enum TILESET
{
	GROUNDTILE, OBJTILE, ENDTILE
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

	bool _tileCollision;	// 타일 이미지에 왔니
	bool _listCollision;	// 타일 리스트 이미지에 왔니
	bool _rectSetting;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void tileSetting();





	tileMapUI();
	~tileMapUI();
};

