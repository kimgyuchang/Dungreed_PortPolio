#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "Object.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<vector<UIImage*>>	_vUiBrushGrid;		// 그리드 브러시
	vector<vector<Object*>>		_vUiBrushObject;	// 오브젝트 브러시
	mapScene*					_mapScene;			

	int							_page;				// 현재 페이지
	bool						_isObject;			// 현재 오브젝트를 선택했는지
	bool						_isOn;				// 현재 페이지가 나와있는지
	float						_xPos;				// 프레임의 X위치

public:
	HRESULT init();
	void UIInit();
	void PageViewChange();
	void release();
	void update();
	void MoveBrushTool();
	void MenuCollisionCheck();
	void mouseCollisionCheck();
	void render();

	vector<vector<UIImage*>>& GetUiBrushGrid() { return _vUiBrushGrid; }
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
	int GetPage() { return _page; }
	void SetPage(int page) { _page = page; }
};