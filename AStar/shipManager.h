#pragma once
#include "gameNode.h"
#include "battle.h"
#include "battle2.h"
#include "space.h"

enum SHIPKIND
{
	SHIPKIND_BATTLE1,
	SHIPKIND_BATTLE2,
	SHIPKIND_END
};

class shipManager : public gameNode
{
private:
	ship* _ship[SHIPKIND_END];
	ship* _focusShip;

	space* _space;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	shipManager();
	~shipManager();
};

