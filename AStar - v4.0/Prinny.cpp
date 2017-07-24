#include "stdafx.h"
#include "Prinny.h"


Prinny::Prinny()
{
}


Prinny::~Prinny()
{
}

HRESULT Prinny::init(const wstring characternName, const wchar_t* imageName, int x, int y)
{
	enemy::init(characternName, imageName, x, y);

	_enemy.stat = ENEMY_STAT_RT_STAND;
	_enemy.pos[ENEMY_POS_RT_STAND]->start();

	return S_OK;
}

void Prinny::posSet(void)
{
	// ============서있기=============
	int arrLB_STAND[] = { 0,1,2,3,4,5,6 };
	_enemy.pos[ENEMY_POS_LB_STAND]->setPlayFrame(arrLB_STAND, 7, 1);
	_enemy.pos[ENEMY_POS_LB_STAND]->setFPS(10);

	int arrRB_STAND[] = { 31,30,29,28,27,26,25 };
	_enemy.pos[ENEMY_POS_RB_STAND]->setPlayFrame(arrRB_STAND, 7, 1);
	_enemy.pos[ENEMY_POS_RB_STAND]->setFPS(10);

	int arrLT_STAND[] = { 32,33,34,35,36,37,38 };
	_enemy.pos[ENEMY_POS_LT_STAND]->setPlayFrame(arrLT_STAND, 7, 1);
	_enemy.pos[ENEMY_POS_LT_STAND]->setFPS(10);

	int arrRT_STAND[] = { 63,62,61,60,59,58,57 };
	_enemy.pos[ENEMY_POS_RT_STAND]->setPlayFrame(arrRT_STAND, 7, 1);
	_enemy.pos[ENEMY_POS_RT_STAND]->setFPS(10);


	//============움직이기=============
	int arrLB_MOVE[] = { 64,65,66,67,68,69,70 };
	_enemy.pos[ENEMY_POS_LB_MOVE]->setPlayFrame(arrLB_MOVE, 7, 0);
	_enemy.pos[ENEMY_POS_LB_MOVE]->setFPS(10);

	int arrRB_MOVE[] = { 95,94,93,92,91,90,89 };
	_enemy.pos[ENEMY_POS_RB_MOVE]->setPlayFrame(arrRB_MOVE, 7, 0);
	_enemy.pos[ENEMY_POS_RB_MOVE]->setFPS(10);

	int arrLT_MOVE[] = { 96,97,98,99,100,101,102 };
	_enemy.pos[ENEMY_POS_LT_MOVE]->setPlayFrame(arrLT_MOVE, 7, 0);
	_enemy.pos[ENEMY_POS_LT_MOVE]->setFPS(10);

	int arrRT_MOVE[] = { 127,126,125,124,123,122,121 };
	_enemy.pos[ENEMY_POS_RT_MOVE]->setPlayFrame(arrRT_MOVE, 7, 0);
	_enemy.pos[ENEMY_POS_RT_MOVE]->setFPS(10);


	//============공격=============
	int arrLB_ATTACK[] = { 128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143 };
	_enemy.pos[ENEMY_POS_LB_ATTACK]->setPlayFrame(arrLB_ATTACK, 16, 0);
	_enemy.pos[ENEMY_POS_LB_ATTACK]->setFPS(30);

	int arrRB_ATTACK[] = { 159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144 };
	_enemy.pos[ENEMY_POS_RB_ATTACK]->setPlayFrame(arrRB_ATTACK, 16, 0);
	_enemy.pos[ENEMY_POS_RB_ATTACK]->setFPS(6);

	int arrLT_ATTACK[] = { 128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143 };
	_enemy.pos[ENEMY_POS_LT_ATTACK]->setPlayFrame(arrLT_ATTACK, 16, 0);
	_enemy.pos[ENEMY_POS_LT_ATTACK]->setFPS(6);

	int arrRT_ATTACK[] = { 159,158,157,156,155,154,153,152,151,150,149,148,147,146,145,144 };
	_enemy.pos[ENEMY_POS_RT_ATTACK]->setPlayFrame(arrRT_ATTACK, 16, 0);
	_enemy.pos[ENEMY_POS_RT_ATTACK]->setFPS(6);

	//============맞음=============
	int arrLB_HIT[] = { 7,8 };
	_enemy.pos[ENEMY_POS_LB_HIT]->setPlayFrame(arrLB_HIT, 2, 0);

	int arrLT_HIT[] = { 24,23 };
	_enemy.pos[ENEMY_POS_LT_HIT]->setPlayFrame(arrLT_HIT, 2, 0);

	int arrRT_HIT[] = { 39,40 };
	_enemy.pos[ENEMY_POS_RT_HIT]->setPlayFrame(arrRT_HIT, 2, 0);

	int arrRB_HIT[] = { 56,55 };
	_enemy.pos[ENEMY_POS_RB_HIT]->setPlayFrame(arrRB_HIT, 2, 0);

	//============스킬=============
	int arrLB_SKILL[] = { 160,161,162,163,164,165,166,167,168,169,170,171,172 };
	_enemy.pos[ENEMY_POS_LB_SKILL]->setPlayFrame(arrLB_SKILL, 13, 0);
	_enemy.pos[ENEMY_POS_LB_SKILL]->setFPS(10);

	int arrRB_SKILL[] = { 191,190,189,188,187,186,185,184,183,182,180,179,178 };
	_enemy.pos[ENEMY_POS_RB_SKILL]->setPlayFrame(arrRB_SKILL, 13, 0);


	int arrLT_SKILL[] = { 192,193,194,195,196,197,198,199,200,201,202,203,204 };
	_enemy.pos[ENEMY_POS_LT_SKILL]->setPlayFrame(arrLT_SKILL, 13, 0);


	int arrRT_SKILL[] = { 223,222,221,220,219,218,217,216,215,214,213,212,211 };
	_enemy.pos[ENEMY_POS_RT_SKILL]->setPlayFrame(arrRT_SKILL, 13, 1);
}
void Prinny::release(void)
{

}
void Prinny::update(void)
{
	enemy::update();
	EFFECTMANAGER->update();
}
void Prinny::render(void)
{
	enemy::render();
	EFFECTMANAGER->render(true, 1);
}

void Prinny::skill(void)
{
	enemy::skill();
	if (_enemy.pos[ENEMY_POS_LB_SKILL]->isPlay() && _enemy.pos[ENEMY_POS_LB_SKILL]->getFrameNum() >= 5)
	{
		EFFECTMANAGER->play(L"칼질", _enemy.x, _enemy.y);
	}

}