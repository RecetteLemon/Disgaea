#pragma once
#include "gameNode.h"
#include "valvatorez.h"
#include "rozalin.h"
#include "characterManager.h"


class testScene : public gameNode
{
private:
	valvatorez* _val;
	rozalin* _roz;
	
	characterManager* _cm;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	testScene();
	~testScene();
};

