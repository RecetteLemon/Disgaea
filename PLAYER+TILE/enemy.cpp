#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(const wchar_t* imageName, int x, int y)
{
	_enemy.img = IMAGEMANAGER->findImage(imageName);
	_enemy.x = x;
	_enemy.y = y;
	for (int i = 0; i < ENEMY_POS_END; i++)
	{
		_enemy.pos[i] = new animation;
		_enemy.pos[i]->init(_enemy.img->getWidth(), _enemy.img->getHeight(),
			_enemy.img->getFrameWidth(), _enemy.img->getFrameHeight());
	}
	this->posSet();
	return S_OK;
}
void enemy::release()
{

}
void enemy::update()
{
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, 
		_enemy.img->getFrameWidth(), _enemy.img->getFrameHeight());


	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		_enemy.stat = ENEMY_STAT_LB_ATTACK;
	}

	this->move();
	this->stand();
	this->skill();
	this->attack();
	this->hit();
}
void enemy::posSet(void)
{

}

void enemy::render() 
{
	switch (_enemy.stat)
	{
		case ENEMY_STAT_LB_STAND:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LB_STAND], true, 1);
		break;
		case ENEMY_STAT_LB_ATTACK:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LB_ATTACK], true, 1);
		break;
		case ENEMY_STAT_LB_SKILL:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LB_SKILL], true, 1);
		break;
		case ENEMY_STAT_LB_MOVE:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LB_MOVE], true, 1);
		break;
		case ENEMY_STAT_LB_HIT:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LB_HIT], true, 1);
		break;
		case ENEMY_STAT_LT_STAND:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LT_STAND], true, 1);
		break;
		case ENEMY_STAT_LT_ATTACK:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LT_STAND], true, 1);
		break;
		case ENEMY_STAT_LT_SKILL:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LT_STAND], true, 1);
		break;
		case ENEMY_STAT_LT_MOVE:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LT_STAND], true, 1);
		break;
		case ENEMY_STAT_LT_HIT:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_LT_STAND], true, 1);
		break;
		case ENEMY_STAT_RB_STAND:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RB_STAND], true, 1);
		break;
		case ENEMY_STAT_RB_ATTACK:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RB_STAND], true, 1);
		break;
		case ENEMY_STAT_RB_SKILL:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RB_STAND], true, 1);
		break;
		case ENEMY_STAT_RB_MOVE:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RB_STAND], true, 1);
		break;
		case ENEMY_STAT_RB_HIT:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RB_STAND], true, 1);
		break;
		case ENEMY_STAT_RT_STAND:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RT_STAND], true, 1);
		break;
		case ENEMY_STAT_RT_ATTACK:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RT_STAND], true, 1);
		break;
		case ENEMY_STAT_RT_SKILL:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RT_STAND], true, 1);
		break;
		case ENEMY_STAT_RT_MOVE:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RT_STAND], true, 1);
		break;
		case ENEMY_STAT_RT_HIT:
			_enemy.img->aniRender(_enemy.rc.left, _enemy.rc.top, _enemy.pos[ENEMY_POS_RT_STAND], true, 1);
		break;
		case ENEMY_STAT_END:
			_enemy.img = NULL;
		break;
	}
}

void enemy::stand(void) 
{
	switch (_enemy.stat)
	{
	case ENEMY_STAT_LB_STAND:
		_enemy.pos[ENEMY_POS_LB_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LB_STAND]->isPlay()) _enemy.pos[ENEMY_POS_LB_STAND]->start();
		break;
	
	case ENEMY_STAT_LT_STAND:
		_enemy.pos[ENEMY_POS_LT_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LT_STAND]->isPlay()) _enemy.pos[ENEMY_POS_LT_STAND]->start();
		break;
	
	case ENEMY_STAT_RB_STAND:
		_enemy.pos[ENEMY_POS_RB_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RB_STAND]->isPlay()) _enemy.pos[ENEMY_POS_RB_STAND]->start();
		break;
	
	case ENEMY_STAT_RT_STAND:
		_enemy.pos[ENEMY_POS_RT_STAND]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RT_STAND]->isPlay()) _enemy.pos[ENEMY_POS_RT_STAND]->start();
		break;
	}
}
void enemy::move(void)	
{
	switch (_enemy.stat)
	{

	case ENEMY_STAT_LB_MOVE:
		_enemy.pos[ENEMY_POS_LB_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LB_MOVE]->isPlay()) _enemy.pos[ENEMY_POS_LB_MOVE]->start();
		break;
	
	case ENEMY_STAT_LT_MOVE:
		_enemy.pos[ENEMY_POS_LT_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LT_MOVE]->isPlay()) _enemy.pos[ENEMY_POS_LT_MOVE]->start();
		break;
	
	case ENEMY_STAT_RB_MOVE:
		_enemy.pos[ENEMY_POS_RB_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RB_MOVE]->isPlay()) _enemy.pos[ENEMY_POS_RB_MOVE]->start();
		break;
	
	case ENEMY_STAT_RT_MOVE:
		_enemy.pos[ENEMY_POS_RT_MOVE]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RT_MOVE]->isPlay()) _enemy.pos[ENEMY_POS_RT_MOVE]->start();
		break;
	
	}
}
void enemy::attack(void)
{
	switch (_enemy.stat)
	{
	
	case ENEMY_STAT_LB_ATTACK:
		_enemy.pos[ENEMY_POS_LB_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LB_ATTACK]->isPlay()) _enemy.pos[ENEMY_POS_LB_ATTACK]->start();
		break;
	
	case ENEMY_STAT_LT_ATTACK:
		_enemy.pos[ENEMY_POS_LT_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LT_ATTACK]->isPlay()) _enemy.pos[ENEMY_POS_LT_ATTACK]->start();
		break;
	
	case ENEMY_STAT_RB_ATTACK:
		_enemy.pos[ENEMY_POS_RB_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RB_ATTACK]->isPlay()) _enemy.pos[ENEMY_POS_RB_ATTACK]->start();
		break;
	
	case ENEMY_STAT_RT_ATTACK:
		_enemy.pos[ENEMY_POS_RT_ATTACK]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RT_ATTACK]->isPlay()) _enemy.pos[ENEMY_POS_RT_ATTACK]->start();
		break;
	
	}
}
void enemy::skill(void)	
{
	switch (_enemy.stat)
	{
	
	case ENEMY_STAT_LB_SKILL:
		_enemy.pos[ENEMY_POS_LB_SKILL]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LB_SKILL]->isPlay()) _enemy.pos[ENEMY_POS_LB_SKILL]->start();
		break;
	
	case ENEMY_STAT_LT_SKILL:
		_enemy.pos[ENEMY_POS_LT_SKILL]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LT_SKILL]->isPlay()) _enemy.pos[ENEMY_POS_LT_SKILL]->start();
		break;
	
	case ENEMY_STAT_RB_SKILL:
		_enemy.pos[ENEMY_POS_RB_SKILL]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RB_SKILL]->isPlay()) _enemy.pos[ENEMY_POS_RB_SKILL]->start();
		break;
	
		break;
	case ENEMY_STAT_RT_SKILL:
		_enemy.pos[ENEMY_POS_RT_SKILL]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RT_SKILL]->isPlay()) _enemy.pos[ENEMY_POS_RT_SKILL]->start();
		break;
	
		
	}
}
void enemy::hit(void)	
{
	switch (_enemy.stat)
	{
	
	case ENEMY_STAT_LB_HIT:
		_enemy.pos[ENEMY_POS_LB_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LB_HIT]->isPlay()) _enemy.pos[ENEMY_POS_LB_HIT]->start();
		break;
	
	case ENEMY_STAT_LT_HIT:
		_enemy.pos[ENEMY_POS_LT_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_LT_HIT]->isPlay()) _enemy.pos[ENEMY_POS_LT_HIT]->start();
		break;
	
	case ENEMY_STAT_RB_HIT:
		_enemy.pos[ENEMY_POS_RB_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RB_HIT]->isPlay()) _enemy.pos[ENEMY_POS_RB_HIT]->start();
		break;
	
	case ENEMY_STAT_RT_HIT:
		_enemy.pos[ENEMY_POS_RT_HIT]->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (!_enemy.pos[ENEMY_POS_RT_HIT]->isPlay()) _enemy.pos[ENEMY_POS_RT_HIT]->start();
		break;
	
	}
}

