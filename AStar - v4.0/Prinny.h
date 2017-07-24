#pragma once
#include "enemy.h"

class Prinny : public enemy
{
public:
	HRESULT init(const wstring characternName ,const wchar_t* imageName, int x, int y);
	void release(void);
	void update(void);
	void render(void);


	void posSet(void);
	void skill(void);

	Prinny();
	~Prinny();
};

