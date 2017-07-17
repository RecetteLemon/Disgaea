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
	//Ÿ��(��Ʈ) ����� ��Ʈ�� �ϳ� �д�
	RECT rcCollision;

	//Ÿ�� �����Ҷ��� Ÿ���ε��� 2���� ���!
	//tileIndex -> Ÿ�� ��ȣ
	int tileIndex[2];
	int tileX, tileY;

	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;
	//��ũ ����
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
	//Ÿ�ϰ� �浹 ����
	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 10, _image->getFrameHeight() - 10);
	//������ġ Ÿ�� X,Y
	//��ũ�� ����
	//��ũ�� ���
	tileX = (int)((_x - ((rcCollision.right - rcCollision.left) / 2)) / TILESIZE);
	tileY = (int)((_y - ((rcCollision.bottom - rcCollision.top) / 2)) / TILESIZE);
	
	//Ÿ�� ���� �� �浹 ó��
	switch (_direction)
	{
		case DIRECTION_LEFT:
			//Ÿ�ϰ����� ���⼭
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
