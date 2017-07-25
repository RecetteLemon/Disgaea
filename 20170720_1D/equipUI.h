#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "equip.h"

class equipUI : public gameNode
{
private:
	int _kind;

	int y;
	RECT _rc[5];
	RECT _selectRC;

	progressBar* _hp[5];

	equip* _equip;
	bool _equipOn;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void showstatUI();


	equipUI();
	~equipUI();
};

