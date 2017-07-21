#pragma once
#include "gameNode.h"



enum STAT
{
	ENEMY_STAT_LB_STAND, ENEMY_STAT_LB_ATTACK,
	ENEMY_STAT_LB_SKILL, ENEMY_STAT_LB_MOVE,
	ENEMY_STAT_LB_HIT,

	ENEMY_STAT_LT_STAND, ENEMY_STAT_LT_ATTACK,
	ENEMY_STAT_LT_SKILL, ENEMY_STAT_LT_MOVE,
	ENEMY_STAT_LT_HIT,

	ENEMY_STAT_RB_STAND, ENEMY_STAT_RB_ATTACK,
	ENEMY_STAT_RB_SKILL, ENEMY_STAT_RB_MOVE,
	ENEMY_STAT_RB_HIT,

	ENEMY_STAT_RT_STAND, ENEMY_STAT_RT_ATTACK,
	ENEMY_STAT_RT_SKILL, ENEMY_STAT_RT_MOVE,
	ENEMY_STAT_RT_HIT,

	ENEMY_STAT_END

};
enum POSITION
{
	ENEMY_POS_LB_STAND, ENEMY_POS_LB_ATTACK,
	ENEMY_POS_LB_SKILL, ENEMY_POS_LB_MOVE,
	ENEMY_POS_LB_HIT,

	ENEMY_POS_LT_STAND, ENEMY_POS_LT_ATTACK,
	ENEMY_POS_LT_SKILL, ENEMY_POS_LT_MOVE,
	ENEMY_POS_LT_HIT,

	ENEMY_POS_RB_STAND, ENEMY_POS_RB_ATTACK,
	ENEMY_POS_RB_SKILL, ENEMY_POS_RB_MOVE,
	ENEMY_POS_RB_HIT,

	ENEMY_POS_RT_STAND, ENEMY_POS_RT_ATTACK,
	ENEMY_POS_RT_SKILL, ENEMY_POS_RT_MOVE,
	ENEMY_POS_RT_HIT,

	ENEMY_POS_END
};

struct ENEMY_
{
	image* img;
	animation* pos[ENEMY_POS_END];
	STAT stat;
	RECT rc;
	int x, y;
};
class enemy : public gameNode
{
protected:
	ENEMY_ _enemy;
	



public:

	virtual HRESULT init(const wchar_t* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void posSet(void);
	virtual void stand(void);
	virtual void move(void);
	virtual void attack(void);
	virtual void skill(void);
	virtual void hit(void);
	

	enemy();
	~enemy();
};

