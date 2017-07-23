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
			_player->init(L"Adell", _x, _y);
		break;
		case PLAYER_CLERIC:
			_player = new Cleric;
			_player->init(L"Cleric", _x, _y);
		break;
		case PLAYER_PRAM:
			_player = new Pram;
			_player->init(L"Pram", _x, _y);
		break;
		case PLAYER_ROZALIN:
			_player = new rozalin;
			_player->init(L"Rozalin", _x, _y);
		break;
		case PLAYER_VALVATOREZ:
			_player = new valvatorez;
			_player->init(L"Valvatorez", _x, _y);
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
			_enemy->init(L"Prinny", _x, _y);
		break;
		case ENEMY_END:
		break;
	}

}