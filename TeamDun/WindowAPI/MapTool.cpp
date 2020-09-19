#include "stdafx.h"
#include "MapTool.h"
#include "mapScene.h"

HRESULT MapTool::init()
{
	return S_OK;
}

HRESULT MapTool::init(int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		vector<Grid*> gridLine;
		for (int j = 0; j < height; j++)
		{
			Grid* grid = new Grid();
			grid->_img = nullptr;
			grid->_x = j * 50 + 0;
			grid->_y = i * 50 + 0;
			grid->_xIndex = j;
			grid->_yIndex = i;
			grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);
			gridLine.push_back(grid);
		}
		_vMapData.push_back(gridLine);
	}

	return S_OK;
}

void MapTool::release()
{
}

void MapTool::update()
{
}

void MapTool::render()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			Rectangle(getMemDC(), _vMapData[i][j]->_rc);
			if (_vMapData[i][j]->_img) _vMapData[i][j]->_img->render(getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y);
		}
	}
}

Grid* MapTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (PtInRect(&_vMapData[i][j]->_rc, _ptMouse))
			{
				return _vMapData[i][j];
			}
		}
	}

	return nullptr;
}

void MapTool::SaveData()
{
	vector<vector<string>> stringData;

	stringData.push_back(vector<string>());
	for (int i = 0; i < _vMapData[0].size(); i++) stringData[0].push_back("-1");

	for (int i = 0; i < _vMapData.size(); i++)
	{
		stringData.push_back(vector<string>());
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img) stringData[i + 1].push_back(_vMapData[i][j]->_img->getKey());
			else stringData[i + 1].push_back("-1");
		}
	}

	CSVMANAGER->csvSave("Data/MapData/gridSaveData.csv", stringData);
}

void MapTool::LoadData()
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/gridSaveData.csv");

	_vMapData.clear();

	for (int i = 0; i < stringData.size(); i++)
	{
		vector<Grid*> gridLine;
		for (int j = 0; j < stringData[i].size(); j++)
		{
			Grid* grid = new Grid();
			if (stringData[i][j] == "-1") grid->_img = nullptr;
			else grid->_img = IMAGEMANAGER->findImage(stringData[i][j]);
			grid->_x = j * 50 + 0;
			grid->_y = i * 50 + 0;
			grid->_xIndex = j;
			grid->_yIndex = i;
			grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);
			gridLine.push_back(grid);
		}
		_vMapData.push_back(gridLine);
	}
}

void MapTool::MapLineAddRow()
{
	vector<Grid*> gridLine;
	for (int j = 0; j < _vMapData[0].size(); j++)
	{
		Grid* grid = new Grid();
		grid->_img = nullptr;
		grid->_x = j * 50 + 0;
		grid->_y = _vMapData.size() * 50 + 0;
		grid->_xIndex = j;
		grid->_yIndex = _vMapData.size();
		grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);
		gridLine.push_back(grid);
	}

	_vMapData.push_back(gridLine);
}

void MapTool::MapLineAddCol()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		Grid* grid = new Grid();
		grid->_img = nullptr;
		grid->_x = _vMapData[i].size() * 50 + 0;
		grid->_y = i * 50 + 0;
		grid->_xIndex = _vMapData[i].size();
		grid->_yIndex = i;
		grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);
		_vMapData[i].push_back(grid);
	}
}

void MapTool::MapLineRemoveCol()
{
	if (_vMapData[0].size() > 1)
	{
		for (int i = 0; i < _vMapData.size(); i++)
		{
			_vMapData[i].erase(_vMapData[i].end() - 1);
		}
	}
}

void MapTool::MapLineRemoveRow()
{
	if (_vMapData.size() > 1)
	{
		_vMapData.erase(_vMapData.end() - 1);
	}
}

void MapTool::fillAll(image* img)
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			_vMapData[i][j]->_img = _mapScene->GetTargetImage();
		}
	}
}

void MapTool::fill(image* targetImage, int indexX, int indexY)
{
	_vMapData[indexY][indexX]->_img = _mapScene->GetTargetImage();
	if (indexX + 1 < _vMapData[0].size() && targetImage == _vMapData[indexY][indexX + 1]->_img)
	{
		fill(targetImage, indexX + 1, indexY);
	}
	if (indexX - 1 >= 0 && targetImage == _vMapData[indexY][indexX - 1]->_img)
	{
		fill(targetImage, indexX - 1, indexY);
	}
	if (indexY + 1 < _vMapData.size() && targetImage == _vMapData[indexY + 1][indexX]->_img)
	{
		fill(targetImage, indexX, indexY + 1);
	}
	if (indexY - 1 >= 0 && targetImage == _vMapData[indexY - 1][indexX]->_img)
	{
		fill(targetImage, indexX, indexY - 1);
	}

	return;
}

void MapTool::GridRange(float x, float y, float x1, float y1)
{
	int temp;
	if (x1 < x)
	{
		temp = x;
		x = x1;
		x1 = temp;
	}

	if (y1 < y)
	{
		temp = y;
		y = y1;
		y1 = temp;
	}

	for (int i = x; i <= x1; i++)
	{
		for (int j = y; j <= y1; j++)
		{
			_vMapData[j][i]->_img = _mapScene->GetTargetImage();
		}
	}
}