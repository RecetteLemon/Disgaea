#pragma once
#include "gameNode.h"
#include "rozalin.h"
#include "valvatorez.h"
#include "Cleric.h"
#include "Adell.h"
#include "Pram.h"
#include "Prinny.h"
#include "statUi.h"

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

	statUi* _sUI;

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

	

	characterManager();
	~characterManager();
};

