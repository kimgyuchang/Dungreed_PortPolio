#pragma once
#include "gameNode.h"
#include "MapTool.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<Grid*>	_vUiBrushGrid;
	mapScene*		_mapScene;
public:


	HRESULT init();
	void release();
	void update();
	void render();

	void mouseCollisionCheck();

	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};

