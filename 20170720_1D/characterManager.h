#pragma once
#include "gameNode.h"
#include "player.h"
#include "rozalin.h"
#include "valvatorez.h"
#include "Cleric.h"
#include "Adell.h"
#include "Pram.h"
#include "Prinny.h"

enum PLAYER
{
	PLAYER_ADELL,
	PLAYER_CLERIC,
	PLAYER_PRAM,
	PLAYER_ROZALIN,
	PLAYER_VALVATOREZ,
	PLAYER_END
};

enum ENEMY
{
	ENEMY_PRINNY,
	ENEMY_END
};

class characterManager : public gameNode
{
private:
	PLAYER _playerKind;
	ENEMY _enemyKind;

	player* _player;
	enemy* _enemy;
	int _x, _y;	

	RECT _shadowRc;

public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	void selectPlayer(int kind);
	void selectEnemy(int kind);

	void playerTileCol(int num);

	inline RECT getShadowRC() { return _shadowRc; }

	void setPlayerX(int x) { _player->setX(_player->getX() + x); }
	void setPlayerY(int y) { _player->setY(_player->getY() + y); }

	POINT getPlayerCenter() { return PointMake(_player->getX(), _player->getY()); }
	PLAYERSTAT getPlayerStat() { return _player->getStat(); }

	POINT getEnemyCenter() { return PointMake(_enemy->getX(), _enemy->getY()); }
	ENEMYSTAT getEnemyStat() { return _enemy->getStat(); }

	void setPlayerState(PLAYERSTAT ps) { _player->setStat(ps); }
	void setEnemyState(ENEMYSTAT ps) { _enemy->setStat(ps); }

	void moveOn() { _player->move(); }
	


	characterManager();
	~characterManager();
};



class dungeonManager : public gameNode
{
private:
	PLAYER _playerKind;
	player* _player[PLAYER_END];
	RECT _shadowRc[PLAYER_END];
	tagIso _tile[TILEX * TILEY];
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	inline RECT* getShadowRC() { return _shadowRc; }

	player* getPlayer(int plNum) { return _player[plNum]; }

	void setPlayerState(int plNum,PLAYERSTAT ps) { _player[plNum]->setStat(ps); }

	void setAdell(int x, int y);
	void setCleric(int x, int y);
	void setPram(int x, int y);
	void setRozalin(int x, int y);
	void setValvatorez(int x, int y);

	dungeonManager();
	~dungeonManager();
};
