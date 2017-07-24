#pragma once
#include "gameNode.h"
#include "progressBar.h"


class statUi : public gameNode
{
private:
	int _kind;

	int y;
	RECT _rc[5];
	RECT _selectRC;

	progressBar* _hp[5];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void showstatUI();

	


	statUi();
	~statUi();
};

