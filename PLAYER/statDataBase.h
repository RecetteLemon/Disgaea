#pragma once
#include "gameNode.h"

enum playerNum
{
	DB_PLAYER_ADELL,
	DB_PLAYER_CLERIC,
	DB_PLAYER_ROZELIN,
	DB_PLAYER_VALVATOREZ,
	DB_PLAYER_PRAM,
	DB_PLAYER_END
};

struct playerStat
{
	int _lv;
	int _hp, _maxHp, _sp , _maxSp;
	int _exp, _maxExp;
	int _atk, _int, _def, _res;
	int	_mov, _thr, _counter, _jm;

};

class statDataBase : public singletonBase<statDataBase>
{
private:

	playerStat _plStat[DB_PLAYER_END];
	unsigned int _money;
public:

	void update(void);

	void LvUp(void);
	void hit(int i ,int x);
	void skill(int i,int x);

	void setLv(int i, int lv) { _plStat[i]._lv = lv; }
	void setHp(int i, int hp) { _plStat[i]._hp = hp; }
	void setSp(int i, int sp) { _plStat[i]._sp = sp; }
	void setExp(int i, int exp) { _plStat[i]._exp = exp; }
	void setAtk(int i, int atk) { _plStat[i]._atk = atk; }
	void setInt(int i, int _int) { _plStat[i]._int = _int; }
	void setDef(int i, int def) { _plStat[i]._def = def; }
	void setRes(int i, int res) { _plStat[i]._res = res; }


	playerStat* getPlayerStat() { return _plStat; }

	void setMoney(unsigned int money) { _money = money; }
	unsigned int getMoney() { return _money; }

	statDataBase();
	~statDataBase();
};

