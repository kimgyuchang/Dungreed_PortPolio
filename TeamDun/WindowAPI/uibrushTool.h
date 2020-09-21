#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "Object.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<vector<Grid*>>	_vUiBrushGrid;		// 그리드 브러시
	vector<vector<Object*>> _vUiBrushObject;	// 오브젝트 브러시
	mapScene*				_mapScene;			

	int						_page;				// 현재 페이지
	bool					_isObject;			// 현재 오브젝트를 선택했는지
	bool					_isOn;				// 현재 페이지가 나와있는지
	float					_xPos;				// 프레임의 X위치
public:

	HRESULT init();
	void UIInit();
	void release();
	void update();
	void MoveBrushTool();
	void MenuCollisionCheck();
	void render();

	void mouseCollisionCheck();
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};

