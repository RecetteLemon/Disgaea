#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

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
	vector<Item> _vWeapon;  //���� ���� ���� - 1ĭ
	vector<Item> _vArmor;	//���� �Ƹ� ���� - 3ĭ ����

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

	//������ ���� �� ��ü�� ���� ���� ���� ����
	vector<Item> &getVWeapon(int i) { return _plStat[i]._vWeapon; }
	vector<Item> &getVArmor(int i) { return _plStat[i]._vArmor; }
	//Ǫ�ù�
	void pushBackVWeapon(int i, Item item) { _plStat[i]._vWeapon.push_back(item); }
	void pushBackVArmor(int i, Item Item) { _plStat[i]._vArmor.push_back(Item); }
	//����� 1 - ���ø� �����
	void eraseVWeapon(int playerArray, int itemAraay) { _plStat[(playerNum)playerArray]._vWeapon.erase(_plStat[(playerNum)playerArray]._vWeapon.begin() + itemAraay); }
	void eraseVArmor(int playerArray, int itemAraay) { _plStat[(playerNum)playerArray]._vArmor.erase(_plStat[(playerNum)playerArray]._vArmor.begin() + itemAraay); }
	//����� 2 - ���ú��� ������ �����
	void erase2VWeapon(int playerArray, int itemAraay) { _plStat[(playerNum)playerArray]._vWeapon.erase(_plStat[(playerNum)playerArray]._vWeapon.begin() + itemAraay, _plStat[(playerNum)playerArray]._vWeapon.end()); }
	void erase2VArmor(int playerArray, int itemAraay) { _plStat[(playerNum)playerArray]._vArmor.erase(_plStat[(playerNum)playerArray]._vArmor.begin() + itemAraay, _plStat[(playerNum)playerArray]._vArmor.end()); }

	statDataBase();
	~statDataBase();
};