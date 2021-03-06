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

class characterManager : public gameNode
{
private:
	PLAYER _playerKind;
	player* _player;
	
	int _x, _y;	

	RECT _shadowRc;

public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	void selectPlayer(int kind);

	void playerTileCol(int num);

	inline RECT getShadowRC() { return _shadowRc; }

	inline void setPlayerX(int x) { return _player->setX(_player->getX() + x); }
	inline void setPlayerY(int y) { return _player->setY(_player->getY() + y); }

	inline void setMoveControl(bool state) { _player->setMoveControl(state); }
	inline bool getMoveControl() { return _player->getMoveControl(); }

	POINT getPlayerCenter() { return PointMake(_player->getX(), _player->getY()); }
	PLAYERSTAT getPlayerStat() { return _player->getStat(); }

	void setPlayerState(PLAYERSTAT ps) { _player->setStat(ps); }

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
	enemy* _enemy;

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

	void setEnemy(int x, int y);

	dungeonManager();
	~dungeonManager();
};
