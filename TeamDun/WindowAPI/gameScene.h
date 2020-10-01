#pragma once
#include "gameNode.h"
#include "BigWhiteSkel.h"
#include "FieldMap.h"

class gameScene : public gameNode
{
private:
	float					_pivX;
	float					_pivY;
	Player*					_p;

	vector<FieldMap*>		_maps;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

