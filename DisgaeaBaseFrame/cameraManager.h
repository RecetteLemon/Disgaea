#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	float _x;
	float _y;
public:
	cameraManager() {};
	~cameraManager() {};
	HRESULT init();
	void release();
	void render(HDC hdc);
	inline float getX() { return _x; }
	inline float getY() { return _y; }
	inline void setX(float x) { _x = x; }
	inline void setY(float y) { _y = y; }
	inline void setPosition(float x, float y)
	{
		_x = x;
		_y = y;
	}
};

