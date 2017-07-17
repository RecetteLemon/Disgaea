#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}


jump::~jump()
{

}

HRESULT jump::init()
{
	_isJumping = _jumpPower = _gravity = 0;

	return S_OK;
}

void jump::release()
{

}

void jump::update()	
{
	if (!_isJumping) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	//뛰었다가 처음 뛴 좌표지점까지 왔으면
	if (_startY <= *_y)
	{
		_isJumping = false;
		*_y = _startY;	//고정해라
	}

}

void jump::render()	
{

}

void jump::jumping(float* x, float* y, float power, float gravity)
{
	//점프 중이면 중복으로 뛰게하지마라
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_jumpPower = power;
}