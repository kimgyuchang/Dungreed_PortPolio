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
			grid->SetImage(IMAGEMANAGER->findImage("Tile" + to_string(i*5 +j)));
			grid->SetIgKey("Tile" + to_string(i * 5 + j));
			cout << grid->GetIgKey() << endl;
			grid->SetX(i * 50 + WINSIZEX / 2 + 200);
			grid->SetY(j * 50 + 300);
			grid->SetRect(RectMake(grid->GetX(), grid->GetY(), 50, 50));

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
		grid->render(getMemDC());
	}
}

void uibrushTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vUiBrushGrid.size(); i++)
	{
		if (PtInRect(&_vUiBrushGrid[i]->GetRect(), _ptMouse))
		{
			_mapScene->SetTargetImage(_vUiBrushGrid[i]->GetImage());
			_mapScene->SetTargetKey(_vUiBrushGrid[i]->GetIgKey());
			return;
		}
	}
}
