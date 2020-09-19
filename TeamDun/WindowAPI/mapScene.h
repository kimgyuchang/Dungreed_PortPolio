#pragma once
#include "uibrushTool.h"
#include "MapTool.h"
class mapScene : public gameNode
{
private:
	uibrushTool*			_uiBrushTool;
	MapTool*				_mapTool;
	image*					_targetImage;
	string					_targetKey;
		
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