#pragma once
#include "gameNode.h"

struct Grid
{
	int		_x;			// X 위치
	int		_y;			// Y 위치
	int     _xIndex;	// xIndex
	int		_yIndex;	// yIndex
	RECT	_rc;		// RECT
	image*	_img;		// IMAGE
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
	HRESULT init(int width, int height);
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
	void GridRange(float x, float y, float x1, float y1);
	void SetMapScene(mapScene* scene) { _mapScene = scene; }

};