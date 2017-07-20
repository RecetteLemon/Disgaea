#include "stdafx.h"
#include "statDataBase.h"


statDataBase::statDataBase()
{
	for (int i = 0; i < DB_PLAYER_END; i++)
	{
		//체력
		_plStat[i]._maxHp = 100;
		_plStat[i]._hp = _plStat[i]._maxHp;
		//기력
		_plStat[i]._maxSp = 100;
		_plStat[i]._sp = _plStat[i]._maxSp;
		//경험치
		_plStat[i]._maxExp = 100;
		_plStat[i]._exp = 0;
		//기타 능력치
		_plStat[i]._lv = 1;
		_plStat[i]._atk = 10;
		_plStat[i]._def = 10;
		_plStat[i]._int = 10;
		_plStat[i]._res = 10;

		_plStat[i]._jm = 25;
		_plStat[i]._mov = 5;
		_plStat[i]._thr = 5;
		_plStat[i]._counter = 3;
	}
}


statDataBase::~statDataBase()
{
}

void statDataBase::update(void)
{
	LvUp();
}

void statDataBase::LvUp(void)
{
	for (int i = 0; i < DB_PLAYER_END; i++)
	{
		if (_plStat[i]._maxExp <= _plStat[i]._exp)
		{
			_plStat[i]._maxHp += 50;
			_plStat[i]._maxSp += 50;
			_plStat[i]._hp = _plStat[i]._maxHp;
			_plStat[i]._sp = _plStat[i]._maxSp;

			_plStat[i]._exp -= _plStat[i]._maxExp;
			_plStat[i]._maxExp += 50;
			
			_plStat[i]._lv++;
			_plStat[i]._atk += 5;
			_plStat[i]._def += 5;
			_plStat[i]._int += 5;
			_plStat[i]._res += 5;
		}
	}
}
void statDataBase::hit(int i, int x)
{
	if(x >_plStat[i]._def) _plStat[i]._hp -= (x - _plStat[i]._def);
	else _plStat[i]._hp--;
}
void statDataBase::skill(int i,int x)
{
	if (_plStat[i]._sp >= x)_plStat[i]._sp -= x;
}