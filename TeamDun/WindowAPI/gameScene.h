#pragma once
#include "gameNode.h"

struct Tile
{
	int		_x;		// X 위치
	int		_y;		// Y 위치
	image*	_img;	// IMAGE
	image*	_img2;	// IMAGE2
};

class gameScene : public gameNode
{
private:
	vector <vector<Tile*>>	_vMapData;
	vector <Object*>		_vObjs;
	float					_pivX;
	float					_pivY;
	Player*					_p;

public:
	HRESULT init();
	void LoadMap(string fileName);
	void release();
	void update();
	void render();
};

