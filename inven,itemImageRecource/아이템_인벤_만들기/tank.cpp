#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{

}

HRESULT tank::init()
{
	_direction = DIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));

	_speed = 100.0f;

	return S_OK;
}

void tank::release()
{

}

void tank::update()	
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = DIRECTION_RIGHT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = DIRECTION_LEFT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = DIRECTION_UP;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = DIRECTION_DOWN;
		tankMove();
	}

}

void tank::render()	
{
	
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	Rectangle(getMemDC(), _rc.left + 5, _rc.top + 5, _rc.right - 5, _rc.bottom - 5);
}


void tank::tankMove()
{
	//타일(렉트) 검출용 렉트를 하나 둔다
	RECT rcCollision;

	//타일 검출할때는 타일인덱스 2개면 충분!
	//tileIndex -> 타일 번호
	int tileIndex[2];
	int tileX, tileY;

	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;
	//탱크 무브
	switch (_direction)
	{
		case DIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);

			_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);

			_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);

			_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);

			_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	RECT tempRC;
	//타일과 충돌 범위
	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 10, _image->getFrameHeight() - 10);
	//현재위치 타일 X,Y
	//탱크의 좌측
	//탱크의 상단
	tileX = (int)((_x - ((rcCollision.right - rcCollision.left) / 2)) / TILESIZE);
	tileY = (int)((_y - ((rcCollision.bottom - rcCollision.top) / 2)) / TILESIZE);
	
	//타일 검출 및 충돌 처리
	switch (_direction)
	{
		case DIRECTION_LEFT:
			//타일검출은 여기서
			//ex) 
			tileIndex[0] = tileX + TILEX * tileY;
			tileIndex[1] = tileX + TILEX * (tileY + 1);
			if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
				{
					_x += moveSpeed;
				}
			}
			else if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc) && IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
				{
					_x += moveSpeed;
				}
			}
		break;
		case DIRECTION_RIGHT:
			tileIndex[0] = tileX + TILEX * tileY + 1;
			tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
			if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
				{
					_x -= moveSpeed;
				}
			}
			else if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc) && IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
				{
					_x -= moveSpeed;
				}
			}
		break;
		case DIRECTION_UP:
			tileIndex[0] = tileX + TILEX * tileY;
			tileIndex[1] = tileX + TILEX * tileY + 1;
			if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
				{
					_y += moveSpeed;
				}
			}
			else if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc) && IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
				{
					_y += moveSpeed;
				}
			}
		break;
		case DIRECTION_DOWN:
			tileIndex[0] = tileX + TILEX * (tileY + 1);
			tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
			if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
				{
					_y -= moveSpeed;
				}
			}
			else if (IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc) && IntersectRect(&tempRC, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
				{
					_y -= moveSpeed;
				}
			}
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}


void tank::setTankPosition()
{
	_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
