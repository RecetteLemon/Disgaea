#pragma once
#include "gameNode.h"
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

public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	void selectPlayer(int kind);
	void selectEnemy(int kind);

	POINT getCenter() { return PointMake(_player->getX(), _player->getY()); }
	PLAYERSTAT getStat() { return _player->getStat(); }

	void setState(PLAYERSTAT ps) { _player->setState(ps); }
	void moveOn() { _player->move(); }


	characterManager();
	~characterManager();
};

