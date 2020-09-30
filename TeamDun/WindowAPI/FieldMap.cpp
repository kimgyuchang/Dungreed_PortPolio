#include "stdafx.h"
#include "FieldMap.h"
 
/// <summary>
/// 사전에 맵을 로드하여 타일과 오브젝트를 배치해넣는다.
/// </summary>
void FieldMap::LoadMap()
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + _fileName + "2.mapData");
	
	if (stringData.size() == 0 || stringData2.size() == 0)
	{
		cout << _fileName << " load Failed" << endl;
		return;
	} // 해당 맵 불러오기에 실패한 경우

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
				rc = RectMake(10 + j * 5, 10 + i * 5, 5, 5); // 한칸당 5픽셀이기 때문에 늘리고싶으면 이미지도 같이 바꿔야합니다
				_vMiniRc.push_back(rc);
			}
			if (stringData2[i][j] == "-1") tile->_img2 = nullptr;
			else tile->_img2 = IMAGEMANAGER->findImage(stringData2[i][j]);
			tile->_x = j * 48;
			tile->_y = i * 48;

			if (stringData[i][j] == "-1") tile->_collisionImage = nullptr;	// 타일이 없다면 충돌체도 없다.
			else tile->_collisionImage = DATAMANAGER->GetGridDataByName(stringData[i][j])->_colImage; // 충돌체를 적당한 이미지로 넣는다.

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

/// <summary>
/// 픽셀 콜리젼 이미지를 그려 픽셀충돌용 맵을 만드는 함수
/// </summary>
void FieldMap::PixelCollisionMapGenerate()
{
	Rectangle(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), -10, -10, 10000, 10000); // 픽셀충돌 이미지 도화지에 커다란 흰색 RECT를 끼얹는다
	
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_collisionImage != nullptr) 
			{
				_vMapData[i][j]->_collisionImage->render(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _vMapData[i][j]->_x, _vMapData[i][j]->_y); // 충돌용 배경에 충돌용 타일 배치
			}
		}
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
	for (int i = ((CAMERAMANAGER->GetPivotY() - (WINSIZEY / 2)) / 48) - 5; i < ((CAMERAMANAGER->GetPivotY() + (WINSIZEY / 2)) / 48) + 5; i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = ((CAMERAMANAGER->GetPivotX() - (WINSIZEX / 2)) / 48) - 5; j < ((CAMERAMANAGER->GetPivotX() + (WINSIZEX / 2)) / 48) + 5; j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;
			if (_vMapData[i][j]->_img2) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img2, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
			if (_vMapData[i][j]->_img) CAMERAMANAGER->Render(hdc, _vMapData[i][j]->_img, _vMapData[i][j]->_x, _vMapData[i][j]->_y);

		}
	} // 일정 범위만큼만 렌더해준다.

	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		IMAGEMANAGER->findImage("MiniMapPixel")->render(hdc, _vMiniRc[i].left, _vMiniRc[i].top);
	}

	if (INPUT->GetKey(VK_F1))
	{
		CAMERAMANAGER->Render(hdc, IMAGEMANAGER->findImage("PixelMapIg"), 0, 0);
	}
}
