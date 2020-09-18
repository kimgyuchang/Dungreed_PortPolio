#pragma once
#include "gameNode.h"
#include "Grid.h"

class mapScene;
class MapTool : public gameNode
{
private:
	vector<vector<Grid*>>	_vMapData;
	mapScene*				_mapScene;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	Grid* mouseCollisionCheck();
	void SaveData();
	void LoadData();
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};
