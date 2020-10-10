#pragma once
#include "gameNode.h"
#include "Stage.h"

class gameScene : public gameNode
{
private:
	float				_pivX;
	float				_pivY;
	Player*				_p;
public:
	HRESULT init();
	void initUI();
	void release();
	void update();
	void render();
};

