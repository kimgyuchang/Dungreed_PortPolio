#pragma once
#include "gameNode.h"
#include "Stage.h"

class gameScene : public gameNode
{
private:
	float					_pivX;
	float					_pivY;
	Player*					_p;
	vector<string>			_vCharName;
	vector<string>			_CharExplanation;
public:
	HRESULT init();
	void initUI();
	void DungeonMapUIInit();
	void InventoryUIInit();
	void release();
	void update();
	void render();
};

