#pragma once
#include "gameNode.h"

struct Grid
{
	int				_x;					// X 위치
	int				_y;					// Y 위치
	int				_width;				// 렉트길이
	int				_height;			// 렉트세로길이
	int				_xIndex;			// xIndex
	int				_yIndex;			// yIndex
	RECT			_rc;				// RECT
	image*			_img;				// IMAGE
	image*			_img2;				// IMGE2
	vector<image*>	_vBeforeImg;		// 전IMAGE
	vector<image*>	_vBeforeImg2;		// 전IMAGE2
	image*			_checkImg;			// 체크이미지
	int				_alpha;
};

class mapScene;

class MapTool : public gameNode
{
private:

	vector<vector<Grid*>>			_vMapData;		// 맵 데이터를 가지고 있는 벡터
	vector<vector<vector<string>>>	_vEveData;		// 실행취소를 위해 행동 전 맵을 저장할 벡터

	mapScene*						_mapScene;		// 맵씬

	bool							_isLayer;		// 레이어 선택하기위한 불값
	bool							_useTwoLayer;	// FloodFill에서 두 레이어를 모두 사용한다
	float							_zoomWidth;
	float							_zoomHeight;
	
	// OBJECT 관련 //
	vector<MapObject*>				_vObjs;			// 오브젝트 목록

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
	void PreviewGridRange( int startIndexX, int startIndexY, int indexX, int indexY,int alpha);
	void GridRange(float x, float y, float x1, float y1);

	void SetMap();
	
	// GETSET // 
	void					SetMapScene(mapScene* scene)		{ _mapScene = scene; }
	vector<vector<Grid*>>&	GetGrid()							{ return _vMapData; }
	vector<MapObject *>&	GetVObject()						{ return _vObjs; }
	bool					getIsLayer()						{ return _isLayer; }
	void					setIsLayer(bool isLayer)			{ _isLayer = isLayer; }
	bool					getUseTwoLayer()					{ return _useTwoLayer; }
	void					setUseTwolayer(bool useTwoLayer)	{ _useTwoLayer = useTwoLayer; }
	float					getZoomWidth()						{ return _zoomWidth;}
	void					setZoomWidth(float width)			{ _zoomWidth = width; }
	float					getZoomHeight()						{ return _zoomHeight; }
	void					setZoomHeight(float height)			{ _zoomHeight = height; }
};