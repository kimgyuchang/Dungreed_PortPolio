#include "stdafx.h"
#include "MapTool.h"
#include "mapScene.h"

HRESULT MapTool::init()
{
	for (int i = 0; i < 12; i++)
	{
		vector<Grid*> gridLine;
		for (int j = 0; j < 12; j++)
		{
			Grid* grid = new Grid();
			grid->SetImage(nullptr);
			grid->SetX(i * 50 + 0);
			grid->SetY(j * 50 + 0);
			grid->SetRect(RectMake(grid->GetX(), grid->GetY(), 50, 50));
			grid->SetIgKey("");
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
			_vMapData[i][j]->render(getMemDC());
		}
	}
}


Grid* MapTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (PtInRect(&_vMapData[i][j]->GetRect(), _ptMouse))
			{
				return _vMapData[i][j];
			}
		}
	}

	return nullptr;
}

void MapTool::SaveData()
{
	vector<vector<string>> saveData;
	for (int i = 0; i < _vMapData.size(); i++)
	{
		vector<string> vStr;
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (!_vMapData[i][j]->GetImage()) vStr.push_back("-1");
			else	vStr.push_back(_vMapData[i][j]->GetIgKey());
		}
		saveData.push_back(vStr);
	}

	saveData.insert(saveData.begin(), vector<string>{});
	for (int i = 0; i < saveData[1].size(); i++)
	{
		saveData[0].push_back("0");
	}

	CSVMANAGER->csvSave("mapData.csv", saveData);
}

void MapTool::LoadData()
{
	vector<vector<string>> loadData = CSVMANAGER->csvLoad("mapData.csv");
	if (loadData.size() > 0)
	{
		_vMapData.clear();
		for (int i = 0; i < loadData.size(); i++)
		{
			vector<Grid*> gridLine;

			for (int j = 0; j < loadData[i].size(); j++)
			{
				Grid* grid = new Grid();
				grid->SetImage(IMAGEMANAGER->findImage(loadData[i][j]));
				grid->SetIgKey(loadData[i][j]);
				grid->SetX(i * 50 + 0);
				grid->SetY(j * 50 + 0);
				grid->SetRect(RectMake(grid->GetX(), grid->GetY(), 50, 50));

				gridLine.push_back(grid);
			}
			_vMapData.push_back(gridLine);

		}
	}

	else
	{
		cout << "CANNOT LOAD DATA" << endl;
	}
}