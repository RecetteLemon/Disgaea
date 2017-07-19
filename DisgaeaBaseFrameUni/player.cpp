#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}


HRESULT player::init(const wchar_t* imageName, int x, int y)
{


	IMAGEMANAGER->addFrameImage(L"호석이병신", L"image/player/Valvatorez.png", 2964, 2873, 12, 13);

	_player.x = x;
	_player.y = y;
	_player.img = IMAGEMANAGER->findImage(imageName);

	//애니메이션초기화해줌!
	for (int i = 0; i < PLAYER_POS_END; i++)
	{
		_player.pos[i] = new animation;
		_player.pos[i]->init(_player.img->getWidth(), _player.img->getHeight(),
			_player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	

	this->posSet();
	

	return S_OK;
}
void player::release(void)
{

}
void player::update(void) 
{
	//통상 렉트
	_player.rc = RectMakeCenter(_player.x, _player.y,
		_player.img->getFrameWidth(), _player.img->getFrameHeight());


	this->control();
	this->move();
	this->attack();
	this->lift();
	this->hit();
	this->throw_();
	this->stand();
}

void player::posSet(void) 
{



}

void player::render(void) 
{
	//상태별로 애니메이션 그려줌
	switch (_player.stat)
	{
		//==================서있음====================//
		case player::PLAYER_STAT_RT_STAND:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_STAND]);
		break;
		case player::PLAYER_STAT_LB_STAND:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_STAND]);
		break;
		case player::PLAYER_STAT_LT_STAND:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_STAND]);
		break;
		case player::PLAYER_STAT_RB_STAND:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_STAND]);
		break;

		//==================움직임====================//
		case player::PLAYER_STAT_RT_MOVE:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_MOVE]);
		break;
		case player::PLAYER_STAT_LB_MOVE:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_MOVE]);
		break;
		case player::PLAYER_STAT_LT_MOVE:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_MOVE]);
		break;
		case player::PLAYER_STAT_RB_MOVE:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_MOVE]);
		break;

		//==================공격함====================//
		case player::PLAYER_STAT_RT_ATTACK:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_ATTACK]);
		break;
		case player::PLAYER_STAT_LB_ATTACK:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_ATTACK]);
		break;
		case player::PLAYER_STAT_LT_ATTACK:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_ATTACK]);
		break;
		case player::PLAYER_STAT_RB_ATTACK:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_ATTACK]);
		break;

		//==================쳐맞음====================//
		case player::PLAYER_STAT_RT_HIT:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_HIT]);
		break;																		   
		case player::PLAYER_STAT_LB_HIT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_HIT]);
		break;																		   
		case player::PLAYER_STAT_LT_HIT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_HIT]);
		break;																		   
		case player::PLAYER_STAT_RB_HIT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_HIT]);
		break;																		   
																					   
		//==================던진다====================//								 
		case player::PLAYER_STAT_RT_THROW:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_THROW]);
		break;																		   
		case player::PLAYER_STAT_LB_THROW:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_THROW]);
		break;																		   
		case player::PLAYER_STAT_LT_THROW:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_THROW]);
		break;																		   
		case player::PLAYER_STAT_RB_THROW:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_THROW]);
		break;																		   
																					   
		//==================쳐들다====================//								 
		case player::PLAYER_STAT_LB_LIFT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LB_LIFT]);
		break;																		   
		case player::PLAYER_STAT_LT_LIFT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_LT_LIFT]);
		break;																		   
		case player::PLAYER_STAT_RT_LIFT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RT_LIFT]);
		break;																		   
		case player::PLAYER_STAT_RB_LIFT:											   
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_RB_LIFT]);
		break;																		   
	
		//==================스킬씀====================//
		case player::PLAYER_STAT_SKILL:
			_player.img->aniRender(_player.rc.left, _player.rc.top, _player.pos[PLAYER_POS_SKILL]);
		break;


		case player::PLAYER_STAT_END:
			_player.img = NULL;
		break;
	}
}

void player::stand(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_STAND:
			_player.pos[PLAYER_POS_RT_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_STAND]->isPlay()) _player.pos[PLAYER_POS_RT_STAND]->start();
		break;
		case PLAYER_STAT_LB_STAND:
			_player.pos[PLAYER_POS_LB_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_STAND]->isPlay()) _player.pos[PLAYER_POS_LB_STAND]->start();
		break;
		case PLAYER_STAT_LT_STAND:
			_player.pos[PLAYER_POS_LT_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_STAND]->isPlay()) _player.pos[PLAYER_POS_LT_STAND]->start();
		break;
		case PLAYER_STAT_RB_STAND:
			_player.pos[PLAYER_POS_RB_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_STAND]->isPlay()) _player.pos[PLAYER_POS_RB_STAND]->start();
		break;
	}
}
void player::move(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_MOVE:
			_player.pos[PLAYER_POS_RT_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_MOVE]->isPlay()) _player.pos[PLAYER_POS_RT_MOVE]->start();
		break;
		case PLAYER_STAT_LB_MOVE:
			_player.pos[PLAYER_POS_LB_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_MOVE]->isPlay()) _player.pos[PLAYER_POS_LB_MOVE]->start();
		break;
		case PLAYER_STAT_LT_MOVE:
			_player.pos[PLAYER_POS_LT_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_MOVE]->isPlay()) _player.pos[PLAYER_POS_LT_MOVE]->start();
		break;
		case PLAYER_STAT_RB_MOVE:
			_player.pos[PLAYER_POS_RB_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_MOVE]->isPlay()) _player.pos[PLAYER_POS_RB_MOVE]->start();
		break;
	}
}
void player::attack(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_ATTACK:
			_player.pos[PLAYER_POS_RT_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_ATTACK]->isPlay()) _player.pos[PLAYER_POS_RT_ATTACK]->start();
		break;
		case PLAYER_STAT_LB_ATTACK:
			_player.pos[PLAYER_POS_LB_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_ATTACK]->isPlay()) _player.pos[PLAYER_POS_LB_ATTACK]->start();
		break;
		case PLAYER_STAT_LT_ATTACK:
			_player.pos[PLAYER_POS_LT_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_ATTACK]->isPlay()) _player.pos[PLAYER_POS_LT_ATTACK]->start();
		break;
		case PLAYER_STAT_RB_ATTACK:
			_player.pos[PLAYER_POS_RB_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_ATTACK]->isPlay()) _player.pos[PLAYER_POS_RB_ATTACK]->start();
		break;
		case PLAYER_STAT_SKILL:
		_player.pos[PLAYER_POS_SKILL]->frameUpdate(TIMEMANAGER->getElapsedTime());
	//	if (!_player.pos[PLAYER_POS_SKILL]->isPlay()) _player.pos[PLAYER_POS_SKILL]->start();
		break;
	}
}
void player::lift(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_LIFT:
			_player.pos[PLAYER_POS_RT_LIFT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_LIFT]->isPlay()) _player.pos[PLAYER_POS_RT_LIFT]->start();
		break;
		case PLAYER_STAT_LB_LIFT:
			_player.pos[PLAYER_POS_LB_LIFT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_LIFT]->isPlay()) _player.pos[PLAYER_POS_LB_LIFT]->start();
		break;
		case PLAYER_STAT_LT_LIFT:
			_player.pos[PLAYER_POS_LT_LIFT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_LIFT]->isPlay()) _player.pos[PLAYER_POS_LT_LIFT]->start();
		break;
		case PLAYER_STAT_RB_LIFT:
			_player.pos[PLAYER_POS_RB_LIFT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_LIFT]->isPlay()) _player.pos[PLAYER_POS_RB_LIFT]->start();
		break;
	}
}
void player::hit(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_HIT:
			_player.pos[PLAYER_POS_RT_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_HIT]->isPlay()) _player.pos[PLAYER_POS_RT_HIT]->start();
		break;
		case PLAYER_STAT_LB_HIT:
			_player.pos[PLAYER_POS_LB_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_HIT]->isPlay()) _player.pos[PLAYER_POS_LB_HIT]->start();
		break;
		case PLAYER_STAT_LT_HIT:
			_player.pos[PLAYER_POS_LT_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_HIT]->isPlay()) _player.pos[PLAYER_POS_LT_HIT]->start();
		break;
		case PLAYER_STAT_RB_HIT:
			_player.pos[PLAYER_POS_RB_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_HIT]->isPlay()) _player.pos[PLAYER_POS_RB_HIT]->start();
		break;
	}
}
void player::throw_(void)
{
	switch (_player.stat)
	{
		case PLAYER_STAT_RT_THROW:
			_player.pos[PLAYER_POS_RT_THROW]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RT_THROW]->isPlay()) _player.pos[PLAYER_POS_RT_THROW]->start();
		break;
		case PLAYER_STAT_LB_THROW:
			_player.pos[PLAYER_POS_LB_THROW]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LB_THROW]->isPlay()) _player.pos[PLAYER_POS_LB_THROW]->start();
		break;
		case PLAYER_STAT_LT_THROW:
			_player.pos[PLAYER_POS_LT_THROW]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_LT_THROW]->isPlay()) _player.pos[PLAYER_POS_LT_THROW]->start();
		break;
		case PLAYER_STAT_RB_THROW:
			_player.pos[PLAYER_POS_RB_THROW]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_player.pos[PLAYER_POS_RB_THROW]->isPlay()) _player.pos[PLAYER_POS_RB_THROW]->start();
		break;
	}
}

void player::control(void)
{
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_player.stat = PLAYER_STAT_RT_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('W'))
	{
		_player.stat = PLAYER_STAT_RT_STAND;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_player.stat = PLAYER_STAT_RB_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_player.stat = PLAYER_STAT_RB_STAND;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_player.stat = PLAYER_STAT_LB_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		_player.stat = PLAYER_STAT_LB_STAND;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_player.stat = PLAYER_STAT_LT_MOVE;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_player.stat = PLAYER_STAT_LT_STAND;
	}

	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_player.stat = PLAYER_STAT_SKILL;
	}
}