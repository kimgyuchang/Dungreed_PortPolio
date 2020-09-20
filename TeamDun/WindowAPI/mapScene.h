#pragma once
#include "uibrushTool.h"
#include "MapTool.h"
class mapScene : public gameNode
{
private:
	// UI BRUSH 관련 //
	uibrushTool*	_uiBrushTool;
	
	// MAP TOOL 관련 //
	MapTool*		_mapTool;
	image*			_targetImage;

	// FILL RANGE 관련 //
	bool			_isFillClicked;
	POINT			_clickedPointOne;
	POINT			_clickedPointTwo;

	// 초기 사이즈 설정 관련 //
	int				_heightNum;
	int				_widthNum;
	bool			_isSettingPage;

	// 회전 관련 (테스트용) //
	int				_rotateTester;
	int				_rotTimer;

public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void SetMapSize();
	void RemovePaint();
	void FillSquareRange();
	void Paint();
	void FloodFill();
	void FillAll();
	void GetUiBrush();
	void saveData();
	void AddMapLine();
	void loadData();
	void render();

	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
};

