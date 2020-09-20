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

	vector<vector<Grid*>>			_vMapData;		// 맵 데이터를 가지고 있는 벡터
	vector<Grid*>					_vUiBrushGrid;	// 선택 가능한 브러식들을 가지고 있는 벡터
	vector<vector<vector<string>>>	_vEveData;		// 실행취소를 위해 행동 전 맵을 저장할 벡터

	mapScene*						_mapScene;		// 맵씬

public:
	HRESULT init();
	HRESULT init(int width, int height);
	void release();
	void update();
	void render();


	Grid* mouseCollisionCheck();
	void SaveData(string name);
	void LoadData(string name);
	void EveSaveData();
	void EveLoadData();
	void MapLineAddRow();
	void MapLineAddCol();
	void MapLineRemoveCol();
	void MapLineRemoveRow();
	void FillAll();
	void FloodFill(image * targetImage, int indexX, int indexY);
	void GridRange(float x, float y, float x1, float y1);
	
	// GETSET // 
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
	vector<vector<Grid*>>& GetGrid() { return _vMapData; }

};