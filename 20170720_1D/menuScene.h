#pragma once
#include "gameNode.h"
enum MENU
{
	MENU_START,
	MENU_CONTINUE,
	MENU_SETTING,
	MENU_CREDITS,
	MENU_EXIT,
	MENU_END
};
class menuScene : public gameNode
{
private:
	MENU _menu;
	POINT _mouse;
	float _alpha;
	bool _changeScene[MENU_END];
public:
	menuScene();
	~menuScene();
	HRESULT init();
	void release();
	void update();
	void render();
	void mouseUpdate();
	void keyDownW();
	void keyDownS();
	void keyDownSpace();
	bool blackOut();
	bool blackIn();
	void sceneChange();
};

