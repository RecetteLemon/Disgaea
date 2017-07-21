#pragma once
#include "gameNode.h"
#include "button.h"
#include "tile.h"
#define SAMX (_sample[_phaseSample.cur]->getMaxFrameX() + 1)
#define SAMY (_sample[_phaseSample.cur]->getMaxFrameY() + 1)
#define SAMSIZEX _sample[_phaseSample.cur]->getFrameWidth()
#define SAMSIZEY _sample[_phaseSample.cur]->getFrameHeight()
#define SAMMAXSIZEX SAMSIZEX * SAMX
#define SAMMAXSIZEY SAMSIZEY * SAMY
enum BUTTON_TYPE
{
	BTN_START,
	BTN_SAVE,
	BTN_LOAD,
	BTN_TERRAIN,
	BTN_OBJECT,
	BTN_ERASER,
	BTN_END
};
enum SAMPLE_TYPE
{
	SAM_TERRAIN = 0,
	SAM_OBJECT,
	SAM_OBJ_ERASER,
	SAM_END
};
struct tagSamplePhase
{
	RECT rc;
	float x;
	float y;
	POINT token;
	BOOL isMove;
	SAMPLE_TYPE cur;
};
struct tagSample
{
	RECT rc;
	POINT frame;
};
class mapToolScene : public gameNode
{
private:
	button* _btn[BTN_END];
	image* _sample[SAM_END];
	tagSamplePhase _phaseSample;
	tagSample _tileSample[TILEX * TILEY];
	tagIso _tile[TILEX * TILEY];
	POINT _curTile;

	int _vertical;
	
	tagSample _sampleTile;

	RECT _btnTileRight;
	RECT _btnTileLeft;
	RECT _tileMonitor;

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
	void startTile();
	void saveTile();
	void loadTile();

	void coordinateUpdate();
	void setTile();
	void camControl();

	void drawTile();
	void drawSample();

	void initButton();
	void updateButton();
	void drawButton();

	TERRAIN_TYPE terCreater(POINT tileNum);
	OBJECT_TYPE objCreater(POINT tileNum);
};

