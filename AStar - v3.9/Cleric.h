#pragma once
#include "player.h"
class Cleric : public player
{
public:

	HRESULT init(const wstring characterName, const wchar_t* imageName, int x, int y);
	void posSet(void);
	Cleric();
	~Cleric();
};

