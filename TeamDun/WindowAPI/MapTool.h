#pragma once
#include "gameNode.h"

struct Grid
{
	int		_x;		// X 위치
	int		_y;		// Y 위치
	int		_xIndex;
	int		_yIndex;
	RECT	_rc;	// RECT
	image* _img;	// IMAGE
};

class mapScene;

class MapTool : public gameNode
{
private:
	vector<vector<Grid*>>	_vMapData;
	vector<Grid*>			_vUiBrushGrid;
	mapScene*				_mapScene;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	vector<vector<Grid*>>& GetGrid() { return _vMapData; }

	Grid* mouseCollisionCheck();
	void SaveData();
	void LoadData();
	void MapLineAddRow();
	void MapLineAddCol();
	void MapLineRemoveCol();
	void MapLineRemoveRow();
	void fillAll(image * img);
	void fill(image * targetImage, int indexX, int indexY);
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};