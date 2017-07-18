#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "menuScene.h"
#include "mapToolScene.h"
#include "dungeonScene.h"


class disgaea : public gameNode
{
private:

	
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	

	disgaea();
	~disgaea();
};

