#include "stdafx.h"
#include "FieldMap.h"
 
void FieldMap::LoadMap()
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "2.mapData");
	
	if (stringData.size() == 0 || stringData2.size() == 0)
	{
		cout << _fileName << " load Failed" << endl;
		return;
	}

	_vMapData.clear();

	for (int i = 0; i < stringData.size(); i++)
	{
		vector<Tile*> tileLine;
		for (int j = 0; j < stringData[i].size(); j++)
		{
			Tile* tile = new Tile();
			if (stringData[i][j] == "-1") tile->_img = nullptr;
			else
			{
				tile->_img = IMAGEMANAGER->findImage(stringData[i][j]);
				RECT rc;
				rc = RectMake(10 + j * 5, 10 + i * 5, 5, 5); // 한칸당 5픽셀 이기때문에 늘리고싶으면 이미지도 같이 바까야합니다
				_vMiniRc.push_back(rc);
			}
			if (stringData2[i][j] == "-1") tile->_img2 = nullptr;
			else tile->_img2 = IMAGEMANAGER->findImage(stringData2[i][j]);
			tile->_x = j * 48;
			tile->_y = i * 48;
			if (stringData[i][j] != "-1")
			{
				tile->_collisionImage = DATAMANAGER->GetGridDataByName(stringData[i][j])->_colImage;
				tile->_collisionImage->render(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), tile->_x, tile->_y); // 충돌용 배경에 충돌용 타일 배치
			}
			else tile->_collisionImage = nullptr;
			tileLine.push_back(tile);
		}
		_vMapData.push_back(tileLine);
	}

	_vObjs.clear();
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "_Objs.mapData");
	for (int i = 0; i < objData.size(); i++)
	{
		Object* obj;
		switch (stoi(objData[i][0]))
		{
		case 1500:// 큰 해골
			obj = new BigWhiteSkel(*dynamic_cast<BigWhiteSkel*>(DATAMANAGER->GetObjectById(stoi(objData[i][0]))));
			break;
		default:
			obj = new Object(*DATAMANAGER->GetObjectById(stoi(objData[i][0])));
			break;
		}
		obj->SetX(stof(objData[i][1]) * 48);
		obj->SetY(stof(objData[i][2]) * 48);
		obj->SetSpawnTime(stoi(objData[i][3]));

		ENTITYMANAGER->getVObjs().push_back(obj);
	}
}

HRESULT FieldMap::init(string fileName)
{
	_fileName = fileName;
	LoadMap();
	return S_OK;
}

void FieldMap::update()
{
}

void FieldMap::release()
{
}

void FieldMap::render(HDC hdc)
{
	for (int i = ((CAMERAMANAGER->GetPivotY() - (WINSIZEY / 2)) / 48); i < ((CAMERAMANAGER->GetPivotY() + (WINSIZEY / 2)) / 48); i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = ((CAMERAMANAGER->GetPivotX() - (WINSIZEX / 2)) / 48); j < ((CAMERAMANAGER->GetPivotX() + (WINSIZEX / 2)) / 48); j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;
			if (_vMapData[i][j]->_img2) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img2, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
			if (_vMapData[i][j]->_img) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img, _vMapData[i][j]->_x, _vMapData[i][j]->_y);

		}
	}

	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		IMAGEMANAGER->findImage("MiniMapPixel")->render(hdc, _vMiniRc[i].left, _vMiniRc[i].top);
	}

	if (INPUT->GetKey(VK_F1))
	{
		CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("PixelMapIg"), 0, 0);
	}
}
