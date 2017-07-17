#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//상호참조하게되었을 떄 무한루프를 빠져나오기 위한 전방선언
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;

	missile* _missile;
	thaadMissile* _thaad;

	enemyManager* _em;

	progressBar* _hpBar;
	float _maxHP, _currentHP;

	int _alphaValue;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void collision();

	void removeMissile(int arrNum);

	void hitDamage(float damage);

	image* getShipImage() { return _ship; }

	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }

	thaadMissile* getThaadMissile() { return _thaad; }

	spaceShip();
	~spaceShip();
};

