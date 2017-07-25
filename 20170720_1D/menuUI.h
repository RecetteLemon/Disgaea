#pragma once
#include "gameNode.h"
#include "statUi.h"
#include "townInven.h"
#include "equipUI.h"

enum cursor
{
	SLOT_ITEM,
	SLOT_EQUIP,
	SLOT_STATUS,
	SLOT_EXIT
};

class menuUI : public gameNode
{
private:
	statUi* _sUI;
	townInven* _townInven;
	equipUI* _equip;

	cursor _cursor;
	int _selectNum;
	RECT _selectRc[SLOT_EXIT];
	
	bool _turnMenu;
	bool _invenOn;
	bool _showui;
	bool _equipOn;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void cursorDraw();
	void control();

	menuUI();
	~menuUI();
};

