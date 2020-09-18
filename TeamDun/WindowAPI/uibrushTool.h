#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "Object.h"

class mapScene;
class uibrushTool : public gameNode
{
private:
	vector<Grid*>	_vUiBrushGrid;		// 그리드 브러시
	vector<Object*> _vUiBrushObject;	
	mapScene*		_mapScene;			

	int				_page;			

public:


	HRESULT init();
	void release();
	void update();
	void render();

	void mouseCollisionCheck();
	void SetMapScene(mapScene* scene) { _mapScene = scene; }
};

