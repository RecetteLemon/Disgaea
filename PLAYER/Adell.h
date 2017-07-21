#pragma once
#include "player.h"
class Adell : public player
{
public:
	HRESULT init(const wchar_t* imageName, int x, int y);
	//void update(void);
	//void render(void);

	//void stand(void);
	//void move(void);
	void posSet(void);
	//void attack(void);
	//void lift(void);
	//void hit(void);
	//void throw_(void);
	//void control(void);

	Adell();
	~Adell();
};

