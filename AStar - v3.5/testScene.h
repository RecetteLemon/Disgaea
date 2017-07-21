#pragma once
#include "gameNode.h"
#include "character1.h"


class testScene : public gameNode
{
private:
	character1* _character1;
	


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	testScene();
	~testScene();
};

