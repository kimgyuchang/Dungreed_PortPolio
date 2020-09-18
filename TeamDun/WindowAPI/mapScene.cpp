#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	_uiBrushTool = new uibrushTool();
	_uiBrushTool->init();
	_uiBrushTool->SetMapScene(this);

	_mapTool = new MapTool();
	_mapTool->init();
	_mapTool->SetMapScene(this);
	
	return S_OK;
}

void mapScene::release()
{
}

void mapScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		_uiBrushTool->mouseCollisionCheck();
	}

	if (_targetImage != nullptr && INPUT->GetKey(VK_RBUTTON))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			cout << _targetKey << endl;
			grid->SetImage(_targetImage);
			grid->SetIgKey(_targetKey);
		}
	}

	if (_targetImage != nullptr && INPUT->GetKeyDown(VK_SPACE))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			grid->SetImage(nullptr);
			grid->SetIgKey("-1");
		}
	}

	saveData();
	loadData();
}

void mapScene::render()
{
	_uiBrushTool->render();
	_mapTool->render();
}

void mapScene::saveData()
{
	if (INPUT->GetKeyDown('S'))
	{
		_mapTool->SaveData();
	}
}

void mapScene::loadData()
{
	if (INPUT->GetKeyDown('L'))
	{
		_mapTool->LoadData();
	}
}
