#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	RECT _rc;
	RECT _rc2;
	float _angle;
	image* _img;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

