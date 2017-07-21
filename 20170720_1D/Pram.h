#pragma once
#include "player.h"
class Pram : public player
{
public:

	HRESULT init(const wchar_t* imageName, int x, int y);
	void release(void);
	void update(void);
	void render(void);

	void posSet(void);


	Pram();
	~Pram();
};

