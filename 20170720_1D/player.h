#pragma once
#include "gameNode.h"
#include "townInven.h"

enum PLAYERKIND
{
	CHARACTER1, CHARACTER2,
	CHARACTER3, CHARACTER4,
	CHARACTER5, CHARACTER_END
};
//플레이어 상태값
enum PLAYERSTAT
{
	PLAYER_STAT_RT_STAND, PLAYER_STAT_RT_HIT,
	PLAYER_STAT_RT_MOVE, PLAYER_STAT_RT_ATTACK,
	PLAYER_STAT_RT_LIFT, PLAYER_STAT_RT_THROW,
	PLAYER_STAT_RT_SKILL, PLAYER_STAT_RT_JUMP,

	PLAYER_STAT_LB_STAND, PLAYER_STAT_LB_HIT,
	PLAYER_STAT_LB_MOVE, PLAYER_STAT_LB_ATTACK,
	PLAYER_STAT_LB_LIFT, PLAYER_STAT_LB_THROW,
	PLAYER_STAT_LB_SKILL, PLAYER_STAT_LB_JUMP,

	PLAYER_STAT_LT_STAND, PLAYER_STAT_LT_HIT,
	PLAYER_STAT_LT_MOVE, PLAYER_STAT_LT_ATTACK,
	PLAYER_STAT_LT_LIFT, PLAYER_STAT_LT_THROW,
	PLAYER_STAT_LT_SKILL, PLAYER_STAT_LT_JUMP,

	PLAYER_STAT_RB_STAND, PLAYER_STAT_RB_HIT,
	PLAYER_STAT_RB_MOVE, PLAYER_STAT_RB_ATTACK,
	PLAYER_STAT_RB_LIFT, PLAYER_STAT_RB_THROW,
	PLAYER_STAT_RB_SKILL, PLAYER_STAT_RB_JUMP,

	PLAYER_STAT_END
};
//플레이어 애니메이션에 사용할 enum문
enum PLAYERPOSITION
{
	PLAYER_POS_RT_STAND, PLAYER_POS_RT_HIT,
	PLAYER_POS_RT_MOVE, PLAYER_POS_RT_ATTACK,
	PLAYER_POS_RT_LIFT, PLAYER_POS_RT_THROW,
	PLAYER_POS_RT_SKILL, PLAYER_POS_RT_JUMP,

	PLAYER_POS_LB_STAND, PLAYER_POS_LB_HIT,
	PLAYER_POS_LB_MOVE, PLAYER_POS_LB_ATTACK,
	PLAYER_POS_LB_LIFT, PLAYER_POS_LB_THROW,
	PLAYER_POS_LB_SKILL, PLAYER_POS_LB_JUMP,

	PLAYER_POS_LT_STAND, PLAYER_POS_LT_HIT,
	PLAYER_POS_LT_MOVE, PLAYER_POS_LT_ATTACK,
	PLAYER_POS_LT_LIFT, PLAYER_POS_LT_THROW,
	PLAYER_POS_LT_SKILL, PLAYER_POS_LT_JUMP,

	PLAYER_POS_RB_STAND, PLAYER_POS_RB_HIT,
	PLAYER_POS_RB_MOVE, PLAYER_POS_RB_ATTACK,
	PLAYER_POS_RB_LIFT, PLAYER_POS_RB_THROW,
	PLAYER_POS_RB_SKILL, PLAYER_POS_RB_JUMP,

	PLAYER_POS_END
};

class player : public gameNode
{
protected:                                      



	enum playerCol
	{
		PLAYER_COL_LB,
		PLAYER_COL_RB,
		PLAYER_COL_LT,
		PLAYER_COL_RT,
		PLAYER_NULL		
	};
	struct PLAYER
	{
		wstring _characterName;
		animation* pos[PLAYER_POS_END];
		PLAYERSTAT stat;
		image* shadowImg;
		image* img;
		RECT rc;
		RECT shadowRC;
		int x, y;
	
	};
	
	PLAYER _player;

	playerCol _tileCol;

	int _kind;
	
	townInven* _townInven;
	bool _invenOn;
	bool _shopOn;

public:
	virtual HRESULT init(const wstring characterName ,const wchar_t* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//애니메이션 초기화해줄 함수
	virtual void posSet(void);
	//상태값변하는 조건처리할 함수
	virtual void control(void);
	//상태별 처리할함수들
	virtual void stand(void);
	virtual void attack(void);
	virtual void lift(void);
	virtual void hit(void);
	virtual void throw_(void);
	virtual void move(void);
	virtual void skill(void);

	virtual void AstarMove(void);


	inline RECT getShadowRect() { return _player.shadowRC; }

	void setPlayerCol(int stat) { _tileCol = (playerCol)stat; }

	int getX() { return _player.x; }
	int getY() { return _player.y; }
	PLAYERSTAT getStat() { return _player.stat; }

	void setStat(PLAYERSTAT ps) { _player.stat = ps; }

	player();
	~player();
};

