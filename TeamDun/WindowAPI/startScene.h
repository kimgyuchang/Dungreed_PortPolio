#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	RECT _rc;
	RECT _rc2;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

