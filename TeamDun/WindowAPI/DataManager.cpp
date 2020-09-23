#include "stdafx.h"
#include "DataManager.h"

void DataManager::GetUIBrushToolGridData()
{
	vector<vector<string>> gridData = CSVMANAGER->csvLoad("Data/UIBrushToolGrid.csv");

	for (int i = 0; i < gridData.size(); i++)
	{
		GridData* grid = new GridData();

		grid->_x = stoi(gridData[i][1]);
		grid->_y = stoi(gridData[i][2]);
		grid->_page = stoi(gridData[i][3]);
		grid->_image = IMAGEMANAGER->findImage(gridData[i][4]);
		grid->_name = gridData[i][4];

		_mGridData[stoi(gridData[i][0])] = grid;
	}
}


void DataManager::GetObjectData()
{
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/ObjectData.csv");

	for (int i = 0; i < objData.size(); i++)
	{
		OBJECTTYPE type;
		if (objData[i][2] == "Breakable")
			type = OBJECTTYPE::OT_BREAKABLE;
		else if (objData[i][2] == "Etc")
			type = OBJECTTYPE::OT_ETC;
		else if (objData[i][2] == "Obstacle")
			type = OBJECTTYPE::OT_OBSTACLE;
		else if (objData[i][2] == "NPC")
			type = OBJECTTYPE::OT_NPC;
		else if (objData[i][2] == "Monster")
			type = OBJECTTYPE::OT_MONSTER;

		Object* obj = new Object();
		obj->init(
			stoi(objData[i][0]),
			objData[i][1],
			type,
			vector<string>{objData[i][3], objData[i][4], objData[i][5] }
		);

		_mObjs[stoi(objData[i][0])] = obj;
	}

	vector<vector<string>> mapObjData = CSVMANAGER->csvLoad("Data/MapObjectData.csv");
	for (int i = 0; i < mapObjData.size(); i++)
	{
		MapObject* obj = new MapObject();
		obj->init(stoi(mapObjData[i][0]),
			stof(mapObjData[i][1]),
			stof(mapObjData[i][2]),
			stoi(mapObjData[i][3])
		);

		_mMapObjectData[stoi(mapObjData[i][0])] = obj;
	}
}