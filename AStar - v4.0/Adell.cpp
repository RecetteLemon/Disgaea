#include "stdafx.h"
#include "Adell.h"

Adell::Adell()
{
}

Adell::~Adell()
{
}

HRESULT Adell::init(const wstring characterName,const wchar_t* imageName, int x, int y)
{
	player::init(characterName, imageName, x, y);

	_player.stat = PLAYER_STAT_RT_STAND;
	if (!_player.pos[PLAYER_POS_RT_STAND]->isPlay())_player.pos[PLAYER_POS_RT_STAND]->start();

	return S_OK;
}

void Adell::posSet(void)
{
	int arrLB_STAND[] = { 0,1,2,3,4,5 };
	_player.pos[PLAYER_POS_LB_STAND]->setPlayFrame(arrLB_STAND, 6, 1);
	_player.pos[PLAYER_POS_LB_STAND]->setFPS(10);

	int arrRB_STAND[] = { 11,10,9,8,7,6 };
	_player.pos[PLAYER_POS_RB_STAND]->setPlayFrame(arrRB_STAND, 6, 1);
	_player.pos[PLAYER_POS_RB_STAND]->setFPS(10);

	int arrLT_STAND[] = { 12,13,14,15,16,17 };
	_player.pos[PLAYER_POS_LT_STAND]->setPlayFrame(arrLT_STAND, 6, 1);
	_player.pos[PLAYER_POS_LT_STAND]->setFPS(10);

	int arrRT_STAND[] = { 23,22,21,20,19,18 };
	_player.pos[PLAYER_POS_RT_STAND]->setPlayFrame(arrRT_STAND, 6, 1);
	_player.pos[PLAYER_POS_RT_STAND]->setFPS(10);


	////////////////////////////////////////////////////////////////////////////////////
	int arrLB_MOVE[] = { 24,25,26,27,28,29 };
	_player.pos[PLAYER_POS_LB_MOVE]->setPlayFrame(arrLB_MOVE, 6, 1);
	_player.pos[PLAYER_POS_LB_MOVE]->setFPS(10);

	int arrRB_MOVE[] = { 35,34,33,32,31,30 };
	_player.pos[PLAYER_POS_RB_MOVE]->setPlayFrame(arrRB_MOVE, 6, 1);
	_player.pos[PLAYER_POS_RB_MOVE]->setFPS(10);

	int arrLT_MOVE[] = { 36,37,38,39,40,41 };
	_player.pos[PLAYER_POS_LT_MOVE]->setPlayFrame(arrLT_MOVE, 6, 1);
	_player.pos[PLAYER_POS_LT_MOVE]->setFPS(10);

	int arrRT_MOVE[] = { 47,46,45,44,43,42 };
	_player.pos[PLAYER_POS_RT_MOVE]->setPlayFrame(arrRT_MOVE, 6, 1);
	_player.pos[PLAYER_POS_RT_MOVE]->setFPS(10);
	//////////////////////////////////////////////////////////////////////////////
	int arrLB_LIFT[] = { 48,49,50,51 };
	_player.pos[PLAYER_POS_LB_LIFT]->setPlayFrame(arrLB_LIFT, 4, 1);
	_player.pos[PLAYER_POS_LB_LIFT]->setFPS(10);

	int arrRB_LIFT[] = { 59,58,57,56 };
	_player.pos[PLAYER_POS_LB_LIFT]->setPlayFrame(arrRB_LIFT, 4, 1);
	_player.pos[PLAYER_POS_LB_LIFT]->setFPS(10);

	int arrLT_LIFT[] = { 60,61,62,63 };
	_player.pos[PLAYER_POS_LB_LIFT]->setPlayFrame(arrLT_LIFT, 4, 1);
	_player.pos[PLAYER_POS_LB_LIFT]->setFPS(10);

	int arrRT_LIFT[] = { 71,70,69,68 };
	_player.pos[PLAYER_POS_LB_LIFT]->setPlayFrame(arrRT_LIFT, 4, 1);
	_player.pos[PLAYER_POS_LB_LIFT]->setFPS(10);

	/////
	int arrLB_ATTACK[] = { 72,73,74,75 };
	_player.pos[PLAYER_POS_LB_ATTACK]->setPlayFrame(arrLB_ATTACK, 4, 1);
	_player.pos[PLAYER_POS_LB_ATTACK]->setFPS(10);

	int arrRB_ATTACK[] = { 83,82,81,80 };
	_player.pos[PLAYER_POS_LB_ATTACK]->setPlayFrame(arrRB_ATTACK, 4, 1);
	_player.pos[PLAYER_POS_LB_ATTACK]->setFPS(10);

	int arrLT_ATTACK[] = { 84,85,86,87 };
	_player.pos[PLAYER_POS_LB_ATTACK]->setPlayFrame(arrLT_ATTACK, 4, 1);
	_player.pos[PLAYER_POS_LB_ATTACK]->setFPS(10);

	int arrRT_ATTACK[] = { 95,94,93,92 };
	_player.pos[PLAYER_POS_LB_ATTACK]->setPlayFrame(arrRT_ATTACK, 4, 1);
	_player.pos[PLAYER_POS_LB_ATTACK]->setFPS(10);

	///////

	int arrLB_THROW[] = { 96,97,98,99 };
	_player.pos[PLAYER_POS_LB_THROW]->setPlayFrame(arrLB_LIFT, 4, 1);
	_player.pos[PLAYER_POS_LB_THROW]->setFPS(10);

	int arrRB_THROW[] = { 107,106,105,104 };
	_player.pos[PLAYER_POS_RB_THROW]->setPlayFrame(arrRB_THROW, 4, 1);
	_player.pos[PLAYER_POS_RB_THROW]->setFPS(10);

	int arrLT_THROW[] = { 108,109,110,111 };
	_player.pos[PLAYER_POS_LT_THROW]->setPlayFrame(arrLT_THROW, 4, 1);
	_player.pos[PLAYER_POS_LT_THROW]->setFPS(10);

	int arrRT_THROW[] = { 119,118,117,116 };
	_player.pos[PLAYER_POS_RT_THROW]->setPlayFrame(arrRT_THROW, 4, 1);
	_player.pos[PLAYER_POS_RT_THROW]->setFPS(10);


	int arrLB_SKILL[] = { 120,121,122,123 };
	_player.pos[PLAYER_POS_LB_SKILL]->setPlayFrame(arrLB_SKILL, 4, 1);
	_player.pos[PLAYER_POS_LB_SKILL]->setFPS(5);

	int arrRB_SKILL[] = { 131,130,129,128 };
	_player.pos[PLAYER_POS_RB_SKILL]->setPlayFrame(arrRB_SKILL, 4, 1);
	_player.pos[PLAYER_POS_RB_SKILL]->setFPS(5);

	int arrLT_SKILL[] = { 132,133,134,135 };
	_player.pos[PLAYER_POS_LT_SKILL]->setPlayFrame(arrLT_SKILL, 4, 1);
	_player.pos[PLAYER_POS_LT_SKILL]->setFPS(5);

	int arrRT_SKILL[] = { 143,142,141,140 };
	_player.pos[PLAYER_POS_RT_SKILL]->setPlayFrame(arrRT_SKILL, 4, 1);
	_player.pos[PLAYER_POS_RT_SKILL]->setFPS(5);

	int arrLB_JUMP[] = { 52 };
	_player.pos[PLAYER_POS_LB_JUMP]->setPlayFrame(arrLB_JUMP, 1, 0);

	int arrRB_JUMP[] = { 55 };
	_player.pos[PLAYER_POS_RB_JUMP]->setPlayFrame(arrRB_JUMP, 1, 0);

	int arrLT_JUMP[] = { 53 };
	_player.pos[PLAYER_POS_LT_JUMP]->setPlayFrame(arrLT_JUMP, 1, 0);

	int arrRT_JUMP[] = { 54 };
	_player.pos[PLAYER_POS_RT_JUMP]->setPlayFrame(arrRT_JUMP, 1, 0);

	int arrLB_HIT[] = { 64 };
	_player.pos[PLAYER_POS_LB_HIT]->setPlayFrame(arrLB_HIT, 1, 0);

	int arrRB_HIT[] = { 67 };
	_player.pos[PLAYER_POS_RB_HIT]->setPlayFrame(arrRB_HIT, 1, 0);

	int arrLT_HIT[] = { 65 };
	_player.pos[PLAYER_POS_LT_HIT]->setPlayFrame(arrLT_HIT, 1, 0);

	int arrRT_HIT[] = { 66 };
	_player.pos[PLAYER_POS_RT_HIT]->setPlayFrame(arrRT_HIT, 1, 0);
	
}


