#pragma once
#include "gameNode.h"

class gameScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

