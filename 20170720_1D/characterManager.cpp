#include "stdafx.h"
#include "characterManager.h"


characterManager::characterManager()
{
}


characterManager::~characterManager()
{
}


HRESULT characterManager::init(int x, int y)
{

	_x = x;
	_y = y;

	_playerKind = PLAYER_END;
	_enemyKind = ENEMY_END;
	

	return S_OK;
}
void characterManager::release(void)
{

}
void characterManager::update(void)
{
	if (_playerKind != PLAYER_END ) _player->update();
	if (_enemyKind != ENEMY_END) _enemy->update();
	_shadowRc = _player->getShadowRect();

	
}
void characterManager::render(void)
{
	if (_playerKind != PLAYER_END ) _player->render();
	if (_enemyKind != ENEMY_END) _enemy->render();
	
	
}

void characterManager::selectPlayer(int kind)
{
	_playerKind = (PLAYER)kind;

	switch (_playerKind)
	{
		case PLAYER_ADELL:
			_player = new Adell;
			_player->init(L"NameAdell", L"Adell", _x, _y);
		break;
		case PLAYER_CLERIC:
			_player = new Cleric;
			_player->init(L"NameCleric", L"Cleric", _x, _y);
		break;
		case PLAYER_PRAM:
			_player = new Pram;
			_player->init(L"NamePram", L"Pram", _x, _y);
		break;
		case PLAYER_ROZALIN:
			_player = new rozalin;
			_player->init(L"NameRozalin", L"Rozalin", _x, _y);
		break;
		case PLAYER_VALVATOREZ:
			_player = new valvatorez;
			_player->init(L"NameValvatorez", L"Valvatorez", _x, _y);
		break;
		case PLAYER_END:
		break;
	}
}
void characterManager::selectEnemy(int kind)
{
	_enemyKind = (ENEMY)kind;

	switch (_enemyKind)
	{
		case ENEMY_PRINNY:
			_enemy = new Prinny;
			_enemy->init(L"NamePrinny", L"Prinny", _x, _y);
		break;
		case ENEMY_END:
		break;
	}

}

void characterManager::playerTileCol(int num)
{
	_player->setPlayerCol(num);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
dungeonManager::dungeonManager()
{

}
dungeonManager::~dungeonManager()
{

}

HRESULT dungeonManager::init(void)
{

	_player[PLAYER_ADELL] = new Adell;
	_player[PLAYER_ADELL]->init(L"NameAdell", L"Adell", 0, 0);

	_player[PLAYER_CLERIC] = new Cleric;
	_player[PLAYER_CLERIC]->init(L"NameCleric", L"Cleric", 80, 80);

	_player[PLAYER_PRAM] = new Pram;
	_player[PLAYER_PRAM]->init(L"NamePram", L"Pram", 160, 160);

	_player[PLAYER_ROZALIN] = new rozalin;
	_player[PLAYER_ROZALIN]->init(L"NameRozalin", L"Rozalin", 240, 240);

	_player[PLAYER_VALVATOREZ] = new valvatorez;
	_player[PLAYER_VALVATOREZ]->init(L"NameValvatorez", L"Valvatorez", 320, 320);


	return S_OK;
}
void dungeonManager::release(void)
{

}
void dungeonManager::update(void)
{
	for (int i = 0; i < PLAYER_END; i++)
	{
		_player[i]->update();
		_shadowRc[i] = _player[i]->getShadowRect();
	}
}

void dungeonManager::render(void)
{
	for (int i = 0; i < PLAYER_END; i++)
	{
		_player[i]->render();
	}
}

