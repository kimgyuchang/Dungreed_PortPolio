#include "stdafx.h"
#include "DataManager.h"

/// <summary>
/// UIBrushTool에 배치하기 위한 GridData들을 불러온다.
/// </summary>
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
		grid->_colImage = IMAGEMANAGER->findImage(gridData[i][5]);
		_mGridData[stoi(gridData[i][0])] = grid;
		_mGridDataByName[grid->_name] = grid;
	}
}

/// <summary>
/// Object들의 데이터를 불러온다.
/// </summary>
void DataManager::GetObjectData()
{
	// Object 데이터 파트
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

		Object* obj;
		switch (stoi(objData[i][0]))
		{
		case 1500:// 큰 해골
			obj = new BigWhiteSkel();
			break;

		case 1501:// 미노타우르스
			obj = new Minotaurs();
			break;

		case 1505:// 작은 유령
			obj = new LittleGhost();
			break;

		case 1507:// 해골
			obj = new Skel();
			break;

		case 701: // 아비스 밴시
			obj = new LittleGhost();
			break;

		case 702: // 붉은 박쥐
			obj = new RedBat();
			break;

		case 2000 : // 벨리알
			obj = new Belial();
			break;

		case 514: // 문 왼쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_LEFT);
			break;

		case 515: // 문 오른쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_RIGHT);
			break;

		case 516: // 문 위쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_UP);
			break;

		case 517: // 문 아래쪽
			obj = new Door();
			dynamic_cast<Door*>(obj)->SetDirection(DIRECTION::DIR_DOWN);
			break;

		case 2500: // 몬스터 스포너
			obj = new MonsterSpawner();
			break;

		default:
			obj = new Object();
			break;
		}

		obj->init(
			stoi(objData[i][0]),
			objData[i][1],
			type,
			vector<string>{objData[i][3], objData[i][4], objData[i][5] }
		);

		_mObjectData[stoi(objData[i][0])] = obj;
	}

	// UIBrushTool에 배치하기 위한 mapObject 데이터 파트
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