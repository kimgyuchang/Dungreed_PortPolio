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

	_isCheck = false;
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

	if (_targetImage != nullptr && INPUT->GetKeyDown('P'))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			_mapTool->fillAll(_targetImage);
		}
	}
	if (_targetImage != nullptr && INPUT->GetKeyDown('O'))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			if (grid->_img != _targetImage)
			{
				_mapTool->fill(grid->_img, grid->_xIndex, grid->_yIndex);
			}
		}
	}

	if (_targetImage != nullptr && INPUT->GetKey(VK_RBUTTON))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if(grid) grid->_img = _targetImage;
	}

	if (_targetImage != nullptr && INPUT->GetKeyDown('A'))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{

			if (_isCheck == false)
			{
				_clickedPointOne = POINT{ grid->_xIndex, grid->_yIndex };
				_isCheck = true;
			}

			else
			{
				_clickedPointTwo = POINT{ grid->_xIndex, grid->_yIndex };
				_mapTool->GridRange(_clickedPointOne.x, _clickedPointOne.y, _clickedPointTwo.x, _clickedPointTwo.y);
				_isCheck = false;
			}
		}
	}



	if (_targetImage != nullptr && INPUT->GetKeyDown(VK_SPACE))
	{
		Grid* grid = _mapTool->mouseCollisionCheck();
		if (grid)
		{
			grid->_img = nullptr;
		}
	}

	AddMapLine();
	saveData();
	loadData();
}

void mapScene::render()
{
	_uiBrushTool->render();
	_mapTool->render();

	if (_targetImage) _targetImage->alphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, 128);
}

void mapScene::saveData()
{
	if (INPUT->GetKeyDown('S'))
	{
		_mapTool->SaveData();
	}
}

void mapScene::AddMapLine()
{
	if (INPUT->GetKeyDown('T'))
	{
		_mapTool->MapLineAddCol();
	}

	if (INPUT->GetKeyDown('Y'))
	{
		_mapTool->MapLineAddRow();
	}

	if (INPUT->GetKeyDown('G'))
	{
		_mapTool->MapLineRemoveCol();
	}

	if (INPUT->GetKeyDown('H'))
	{
		_mapTool->MapLineRemoveRow();
	}
}

void mapScene::loadData()
{
	if (INPUT->GetKeyDown('L'))
	{
		_mapTool->LoadData();
	}
}