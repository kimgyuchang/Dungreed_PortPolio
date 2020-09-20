#pragma once
#include "uibrushTool.h"
#include "MapTool.h"
class mapScene : public gameNode
{
private:
	uibrushTool*	_uiBrushTool;
	MapTool*		_mapTool;
	image*			_targetImage;
	string			_targetKey;
	bool			_isCheck;
	POINT			_clickedPointOne;
	POINT			_clickedPointTwo;

	int				_heightNum;
	int				_widthNum;

	bool			_endSetPage;

	int				_rotateTester;
	int				_rotTimer;
public :
	HRESULT init();
	void release();
	void update();
	void render();
	void saveData();
	void AddMapLine();
	void loadData();


	string GetTargetKey() { return _targetKey; }
	image* GetTargetImage() { return _targetImage; }

	void SetTargetKey(string key) { _targetKey = key; }
	void SetTargetImage(image* img) { _targetImage = img; }
};

