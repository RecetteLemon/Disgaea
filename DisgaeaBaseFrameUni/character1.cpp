#include "stdafx.h"
#include "character1.h"


character1::character1()
{
}


character1::~character1()
{
}



HRESULT character1::init(const wchar_t* imageName, int x, int y)
{
	player::init(imageName, x, y);



	_player.stat = PLAYER_STAT_RT_STAND;
	if(!_player.pos[PLAYER_POS_RT_STAND]->isPlay())_player.pos[PLAYER_POS_RT_STAND]->start();

	
	return S_OK;
}

void character1::posSet(void)
{
	// ============서있기=============
	int arrLB_STAND[] = { 0,1,2,3,4,5 };
	_player.pos[PLAYER_POS_LB_STAND]->setPlayFrame(arrLB_STAND, 6, 1);
	_player.pos[PLAYER_POS_LB_STAND]->setFPS(10);

	int arrRB_STAND[] = { 6,7,8,9,10,11 };
	_player.pos[PLAYER_POS_RB_STAND]->setPlayFrame(arrRB_STAND, 6, 1);
	_player.pos[PLAYER_POS_RB_STAND]->setFPS(10);

	int arrLT_STAND[] = { 12,13,14,15,16,17 };
	_player.pos[PLAYER_POS_LT_STAND]->setPlayFrame(arrLT_STAND, 6, 1);
	_player.pos[PLAYER_POS_LT_STAND]->setFPS(10);

	int arrRT_STAND[] = { 18,19,20,21,22,23 };
	_player.pos[PLAYER_POS_RT_STAND]->setPlayFrame(arrRT_STAND, 6, 1);
	_player.pos[PLAYER_POS_RT_STAND]->setFPS(10);


	//============움직이기=============
	int arrLB_MOVE[] = { 24,25,26,27,28,29 };
	_player.pos[PLAYER_POS_LB_MOVE]->setPlayFrame(arrLB_MOVE, 6, 0);
	_player.pos[PLAYER_POS_LB_MOVE]->setFPS(10);

	int arrRB_MOVE[] = { 35,34,33,32,31,30 };
	_player.pos[PLAYER_POS_RB_MOVE]->setPlayFrame(arrRB_MOVE, 6, 0);
	_player.pos[PLAYER_POS_RB_MOVE]->setFPS(10);

	int arrLT_MOVE[] = { 36,37,38,39,40,41 };
	_player.pos[PLAYER_POS_LT_MOVE]->setPlayFrame(arrLT_MOVE, 6, 0);
	_player.pos[PLAYER_POS_LT_MOVE]->setFPS(10);

	int arrRT_MOVE[] = { 47,46,45,44,43,42 };
	_player.pos[PLAYER_POS_RT_MOVE]->setPlayFrame(arrRT_MOVE, 6, 0);
	_player.pos[PLAYER_POS_RT_MOVE]->setFPS(10);


	//============들기=============
	int arrLB_LIFT[] = { 48,49,50,51 };
	_player.pos[PLAYER_POS_LB_LIFT]->setPlayFrame(arrLB_LIFT, 4, 0);
	_player.pos[PLAYER_POS_LB_LIFT]->setFPS(6);

	int arrRB_LIFT[] = { 59,58,57,56 };
	_player.pos[PLAYER_POS_RB_LIFT]->setPlayFrame(arrRB_LIFT, 4, 0);
	_player.pos[PLAYER_POS_RB_LIFT]->setFPS(6);

	int arrLT_LIFT[] = { 72,73,74,75 };
	_player.pos[PLAYER_POS_LT_LIFT]->setPlayFrame(arrLT_LIFT, 4, 0);
	_player.pos[PLAYER_POS_LT_LIFT]->setFPS(6);

	int arrRT_LIFT[] = { 83,82,81,80 };
	_player.pos[PLAYER_POS_RT_LIFT]->setPlayFrame(arrRT_LIFT, 4, 0);
	_player.pos[PLAYER_POS_RT_LIFT]->setFPS(6);

	//============던지기=============
	int arrLB_THROW[] = { 60,61,62,63 };
	_player.pos[PLAYER_POS_LB_THROW]->setPlayFrame(arrLB_THROW, 4, 0);
	_player.pos[PLAYER_POS_LB_THROW]->setFPS(6);

	int arrRB_THROW[] = { 71,70,69,68 };
	_player.pos[PLAYER_POS_RB_THROW]->setPlayFrame(arrRB_THROW, 4, 0);
	_player.pos[PLAYER_POS_RB_THROW]->setFPS(6);

	int arrLT_THROW[] = { 84,85,86,87 };
	_player.pos[PLAYER_POS_LT_THROW]->setPlayFrame(arrLT_THROW, 4, 0);
	_player.pos[PLAYER_POS_LT_THROW]->setFPS(6);

	int arrRT_THROW[] = { 95,94,93,92 };
	_player.pos[PLAYER_POS_RT_THROW]->setPlayFrame(arrRT_THROW, 4, 0);
	_player.pos[PLAYER_POS_RT_THROW]->setFPS(6);

	//============공격=============
	int arrLB_ATTACK[] = { 96,97,98,99 };
	_player.pos[PLAYER_POS_LB_ATTACK]->setPlayFrame(arrLB_ATTACK, 4, 0);
	_player.pos[PLAYER_POS_LB_ATTACK]->setFPS(6);

	int arrRB_ATTACK[] = { 107,106,105,104 };
	_player.pos[PLAYER_POS_RB_ATTACK]->setPlayFrame(arrRB_ATTACK, 4, 0);
	_player.pos[PLAYER_POS_RB_ATTACK]->setFPS(6);

	int arrLT_ATTACK[] = { 108,109,110,111 };
	_player.pos[PLAYER_POS_LT_ATTACK]->setPlayFrame(arrLT_ATTACK, 4, 0);
	_player.pos[PLAYER_POS_LT_ATTACK]->setFPS(6);

	int arrRT_ATTACK[] = { 119,118,117,116 };
	_player.pos[PLAYER_POS_RT_ATTACK]->setPlayFrame(arrRT_ATTACK, 4, 0);
	_player.pos[PLAYER_POS_RT_ATTACK]->setFPS(6);

	//============스킬=============
	int arrSKILL[] = { 120,121,122,123,124,125,132,133,134,135,136,137,144,145,146,147};
	_player.pos[PLAYER_POS_SKILL]->setPlayFrame(arrSKILL, 16, 0);
	_player.pos[PLAYER_POS_SKILL]->setFPS(10);
}
void character1::release(void)										   
{


}
void character1::update(void)										   
{
	player::update();
}
void character1::render(void)										   
{
	player::render();
}

//각상태별로 개별적으로 필요하면 추가
void character1::stand(void)
{
	player::stand();
}

void character1::move(void)
{
	player::move();
}

void character1::attack(void)
{
	player::attack();
}
void character1::lift(void)	 
{
	player::lift();
}
void character1::hit(void)	 
{
	player::hit();
}
void character1::throw_(void)
{
	player::throw_();
}

void character1::control(void)
{
	player::control();
}