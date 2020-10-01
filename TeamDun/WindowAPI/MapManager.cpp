#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	vector<vector<string>> mapData = CSVMANAGER->csvLoad("Data/Maps.csv");
	for (int i = 0; i < mapData.size(); i++)
	{
		FieldMap* map = new FieldMap();
		map->init(mapData[i][0]);
		map->SetStage(stoi(mapData[i][1]));
		_vMaps.push_back(map);
	}
	
	return S_OK;
}

void MapManager::update()
{
}

void MapManager::release()
{
}

void MapManager::render(HDC hdc)
{
}

void MapManager::ChangeMap(int index)
{
	_currentMap = index;
	MAPMANAGER->GetMaps()[_currentMap]->PixelCollisionMapGenerate();
	MAPMANAGER->GetMaps()[_currentMap]->GridMapGenerate();
	EFFECTMANAGER->GetVEffect().clear();
}
