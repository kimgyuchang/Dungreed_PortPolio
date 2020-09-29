#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	UIMANAGER->init();
	_p = new Player();
	_p->init();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	CAMERAMANAGER->init(0,0,15000,15000,-500,-500,WINSIZEX/2, WINSIZEY/2);

	_fillTesterInit = 100;
	_fillTesterPros = 0;
	LoadMap("Stage1_Boss");

	/*
	UIProgressBar* bar = new UIProgressBar();
	bar->init("bar", 0, 0, 300, 100, "ExplorationFailure.korean", "ExplorationSuccess.korean");
	UIMANAGER->GetGameFrame()->AddFrame(bar);
	*/
	// PROGRESSBAR TEST

	return S_OK;
}

void gameScene::LoadMap(string fileName)
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + fileName + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + fileName + "2.mapData");
	if (stringData.size() == 0 && stringData2.size() == 0) return;
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
				tile->_collisionImage->render(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(),tile->_x,tile->_y);
			}
			else tile->_collisionImage = nullptr;
			tileLine.push_back(tile);


		}
		_vMapData.push_back(tileLine);
	}


	_vObjs.clear();
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/MapData/" + fileName + "_Objs.mapData");
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

void gameScene::release()
{
	ENTITYMANAGER->release();
}

void gameScene::update()
{
	/*
	_fillTesterPros += 0.2f;
	if (_fillTesterPros > _fillTesterInit) _fillTesterPros = _fillTesterInit;
	dynamic_cast<UIProgressBar*>(UIMANAGER->GetGameFrame()->GetChild("bar"))->FillCheck(_fillTesterInit, _fillTesterPros);
	*/
	// PROGRESSBAR TEST

	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("시작화면");
		
	}

	if (INPUT->GetKey(VK_LEFT))
	{
		_pivX -= 5;
	}

	if (INPUT->GetKey(VK_RIGHT))
	{
		_pivX += 5;
	}

	if (INPUT->GetKey(VK_UP))
	{
		_pivY -= 5;
	}

	if (INPUT->GetKey(VK_DOWN))
	{
		_pivY += 5;
	}

	CAMERAMANAGER->MovePivotLerp(_pivX, _pivY, 5.f);
	ENTITYMANAGER->update();
}

void gameScene::render()
{
	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));

	for (int i = ((CAMERAMANAGER->GetPivotY() - (WINSIZEY / 2)) / 48); i < ((CAMERAMANAGER->GetPivotY() + (WINSIZEY / 2)) / 48); i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = ((CAMERAMANAGER->GetPivotX() - (WINSIZEX / 2)) / 48); j < ((CAMERAMANAGER->GetPivotX() + (WINSIZEX / 2)) / 48); j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;
			if (_vMapData[i][j]->_img2) CAMERAMANAGER->Render(getMemDC(), _vMapData[i][j]->_img2, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
			if (_vMapData[i][j]->_img) CAMERAMANAGER->Render(getMemDC(), _vMapData[i][j]->_img, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
			if (INPUT->GetKey(VK_F1) && _vMapData[i][j]->_collisionImage != nullptr) CAMERAMANAGER->Render(getMemDC(), _vMapData[i][j]->_collisionImage, _vMapData[i][j]->_x, _vMapData[i][j]->_y);
		}
	}

	for (int i = 0; i < _vMiniRc.size(); i++)
	{
		IMAGEMANAGER->findImage("MiniMapPixel")->render(getMemDC(), _vMiniRc[i].left, _vMiniRc[i].top);
	}
	
	CAMERAMANAGER->Render(getMemDC(), IMAGEMANAGER->findImage("PixelMapIg"),0,0);

	ENTITYMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());
}

void gameScene::setMiniMap()
{
}
