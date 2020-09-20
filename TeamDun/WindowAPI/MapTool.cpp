#include "stdafx.h"
#include "MapTool.h"
#include "mapScene.h"

HRESULT MapTool::init()
{
	return S_OK;
}

/// <summary>
/// 사이즈에 맞추어 맵 툴의 맵을 초기화시킨다.
/// </summary>
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

/// <summary>
/// 맵툴 내 그리드와의 충돌을 검사한다.
/// </summary>
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

/// <summary>
/// 맵을 CSV 파일로 세이브한다.
/// </summary>
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

/// <summary>
/// 이전 작업때 사용한 맵 데이터를 저장한다 (실행취소용)
/// </summary>
void MapTool::EveSaveData()
{
	vector<vector<string>> stringData;

	stringData.push_back(vector<string>());
	for (int i = 0; i < _vMapData[0].size(); i++)
		stringData[0].push_back("-1");

	for (int i = 0; i < _vMapData.size(); i++)
	{
		stringData.push_back(vector<string>());
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img) stringData[i + 1].push_back(_vMapData[i][j]->_img->getKey());
			else stringData[i + 1].push_back("-1");
		}
	}

	CSVMANAGER->csvSave("Data/MapData/eveGridSaveData.csv", stringData);	// 로드데이터처럼 csv파일로 저장을 하고
	stringData = CSVMANAGER->csvLoad("Data/MapData/eveGridSaveData.csv");	// 정보를 다시 담아서 
	_vEveData.push_back(stringData);										// vector<vector<string>>을 담고있는 벡터 EveData에 받은 정보를 push_back해준다
}

/// <summary>
/// 맵을 CSV 파일로 로드한다.
/// </summary>
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

/// <summary>
/// 이전 작업때 사용한 맵 데이터를 가져온다. (실행취소용)
/// </summary>
void MapTool::EveLoadData()
{
	if (_vEveData.size() > 0)
	{
		vector<vector<string>> stringData = _vEveData[_vEveData.size() - 1];

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

		_vEveData.erase(_vEveData.end() - 1);
	}
}

/// <summary>
/// 맵 툴에 행 한 줄을 추가한다.
/// </summary>
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

/// <summary>
/// 맵 툴에 열 한 줄을 추가한다.
/// </summary>
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

/// <summary>
/// 맵 툴에 행 한 줄을 삭제한다.
/// </summary>
void MapTool::MapLineRemoveRow()
{
	if (_vMapData.size() > 1)
	{
		_vMapData.erase(_vMapData.end() - 1);
	}
}

/// <summary>
/// 맵 툴에 열 한 줄을 삭제한다.
/// </summary>
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

/// <summary>
/// 처음부터 끝까지 전체를 타겟 이미지로 덮어씌운다.
/// </summary>
void MapTool::FillAll()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			_vMapData[i][j]->_img = _mapScene->GetTargetImage();
		}
	}
}

/// <summary>
/// FloodFill을 통해 범위를 채운다.
/// </summary>
/// <param name="targetImage">채울 이미지</param>
/// <param name="indexX">현재 검사대상인 X Index</param>
/// <param name="indexY">현재 검사대상인 Y Index</param>
void MapTool::FloodFill(image* targetImage, int indexX, int indexY)
{
	_vMapData[indexY][indexX]->_img = _mapScene->GetTargetImage();
	if (indexX + 1 < _vMapData[0].size() && targetImage == _vMapData[indexY][indexX + 1]->_img)
	{
		FloodFill(targetImage, indexX + 1, indexY);
	}
	if (indexX - 1 >= 0 && targetImage == _vMapData[indexY][indexX - 1]->_img)
	{
		FloodFill(targetImage, indexX - 1, indexY);
	}
	if (indexY + 1 < _vMapData.size() && targetImage == _vMapData[indexY + 1][indexX]->_img)
	{
		FloodFill(targetImage, indexX, indexY + 1);
	}
	if (indexY - 1 >= 0 && targetImage == _vMapData[indexY - 1][indexX]->_img)
	{
		FloodFill(targetImage, indexX, indexY - 1);
	}

	return;
}

/// <summary>
/// x부터 x1, y부터 y1까지의 범위를 채운다.
/// </summary>
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