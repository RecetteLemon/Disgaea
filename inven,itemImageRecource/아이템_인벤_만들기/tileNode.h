#include "stdafx.h"

//한 타일 규격 32 32X32
#define TILESIZE 32

//타일 갯수
#define TILEX 20
#define TILEY 20

//총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일 셋 규격
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//타일 지형에 속성
//갈수있는 타일, 못가는 타일, 밟으면 느려지는~
#define ATTR_UNMOVE		0x00000001
#define ATTR_SWAMP		0x00000002
#define ATTR_MOVE		0x00000003
#define ATTR_POISON		0x00000004


enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

//포지션(리스폰 위치 셋팅)
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//지형 이넘문
	OBJECT obj;				//오브젝트 이넘문
	RECT rc;				//렉트
	int terrainFrameX;		//지형 프레임 번호
	int terrainFrameY;
	int objFrameX;			//오브젝트 프레임 번호
	int objFrameY;
	//int attr;
};

//타일셋
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 정보
struct tagCurrentTile
{
	int x;
	int y;
};