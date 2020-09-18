#include "stdafx.h"
#include "uibrushTool.h"
#include "mapScene.h"

HRESULT uibrushTool::init()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Grid* grid = new Grid();
			grid->_img = IMAGEMANAGER->findImage("Tile" + to_string(i*5 +j));
			grid->_x = i * 50 + WINSIZEX / 2 + 200;
			grid->_y = j * 50 + 300;
			grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);

			_vUiBrushGrid.push_back(grid);
		}
	}

	return S_OK;
}

void uibrushTool::release()
{
}

void uibrushTool::update() 
{
}


void uibrushTool::render()
{
	for (int i = 0; i < _vUiBrushGrid.size(); i++)
	{
		Grid* grid = _vUiBrushGrid[i];
		Rectangle(getMemDC(), grid->_rc);
		if(grid->_img) grid->_img->render(getMemDC(), grid->_x, grid->_y);
	}
}

void uibrushTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vUiBrushGrid.size(); i++)
	{
		if (PtInRect(&_vUiBrushGrid[i]->_rc, _ptMouse))
		{
			_mapScene->SetTargetImage(_vUiBrushGrid[i]->_img);
			return;
		}
	}
}
