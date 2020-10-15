#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	while (true)
	{
		bool mapAllCleared = true;
		_vOriginMaps.clear();
		_vStage.clear();

		vector<vector<string>> mapData = CSVMANAGER->csvLoad("Data/Maps.csv");
		for (int i = 0; i < mapData.size(); i++)
		{
			FieldMap* map = new FieldMap();
			map->init(mapData[i][0]);
			map->SetStage(stoi(mapData[i][1]));
			map->LoadMap();

			if (mapData[i][2] == "NORMAL") map->SetFieldType(FIELDMAPTYPE::FMT_NORMAL);
			else if (mapData[i][2] == "ENTER") map->SetFieldType(FIELDMAPTYPE::FMT_ENTER);
			else if (mapData[i][2] == "END") map->SetFieldType(FIELDMAPTYPE::FMT_END);
			else if (mapData[i][2] == "SHOP") map->SetFieldType(FIELDMAPTYPE::FMT_SHOP);
			else if (mapData[i][2] == "RESTAURANT") map->SetFieldType(FIELDMAPTYPE::FMT_RESTAURANT);
			else if (mapData[i][2] == "TEMPLE") map->SetFieldType(FIELDMAPTYPE::FMT_TEMPLE);

			map->SetMovePos(DIRECTION::DIR_LEFT, POINT{ stoi(mapData[i][3]), stoi(mapData[i][4]) });
			map->SetMovePos(DIRECTION::DIR_RIGHT, POINT{ stoi(mapData[i][5]), stoi(mapData[i][6]) });
			map->SetMovePos(DIRECTION::DIR_UP, POINT{ stoi(mapData[i][7]), stoi(mapData[i][8]) });
			map->SetMovePos(DIRECTION::DIR_DOWN, POINT{ stoi(mapData[i][9]), stoi(mapData[i][10]) });

			_vOriginMaps.push_back(map);
		}

		for (int i = 0; i < 3; i++)
		{
			Stage* stage;
			stage = new Stage();
			stage->init(i);
			if (!stage->SettingMap()) mapAllCleared = false;
			_vStage.push_back(stage);
		}

		if (mapAllCleared) break;
	}

	_pixelGetter = new PixelGetter();
	ChangeMap(1, 0);

	return S_OK;
}

void MapManager::update()
{
	if (INPUT->GetKeyDown(VK_F2))
	{
		ChangeMap(_currentStage, RANDOM->range((int)_vStage[_currentStage]->GetMaps().size()));
		GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}

	if (INPUT->GetKeyDown(VK_F6))
	{
		MAPMANAGER->init();
	}

	_vStage[_currentStage]->GetMaps()[_currentMap]->update();
	DungeonMapUIMover();
	SetMapUIOnOff();
}

/// <summary>
/// 던전 지도 UI를 OnOff
/// </summary>
void MapManager::SetMapUIOnOff()
{
	if (INPUT->GetKeyDown(VK_TAB))
	{
		UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->ToggleIsViewing();
	}
}

/// <summary>
/// 맵 전체에 생성되는 파티클을 추가
/// </summary>
void MapManager::GenerateMapParticle()
{
	ParticleGenerator* mapSquareGen = new ParticleGenerator();
	mapSquareGen->initGenerator(REGULARGEN, 100000, 3, 0, 1, vector<string>{ "SqaureParticle" });
	mapSquareGen->initPos(GetPlayMap()->GetMapSizeX() * 24, GetPlayMap()->GetMapSizeY() * 24, GetPlayMap()->GetMapSizeX() * 44, GetPlayMap()->GetMapSizeY() * 44);
	mapSquareGen->initAlpha(150, 50, 1);
	mapSquareGen->initTime(150, 10);
	mapSquareGen->initScale(0.5f, 1.0f, 0);
	mapSquareGen->initSpeed(0.5f, 0.5f, 0.3f, 0.3f, 0, 0);
	PARTICLEMANAGER->AddGenerator(mapSquareGen);
}

void MapManager::DungeonMapUIMover()
{
	UIFrame* mapFrame = UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetChild("mapFrame");

	if (mapFrame->GetIsViewing())
	{
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (PtInRect(&mapFrame->GetRect(), _ptMouse))
			{
				_moveClickTimer++;
				if (_moveClickTimer == 2)
				{
					_recentMousePos = _ptMouse;
				}

				else if (_moveClickTimer >= 2)
				{
					for (int i = 0; i < mapFrame->GetVChildFrames().size(); i++)
					{
						mapFrame->GetVChildFrames()[i]->MoveFrameChild(_ptMouse.x - _recentMousePos.x, _ptMouse.y - _recentMousePos.y);
					}
					_recentMousePos = _ptMouse;
				}
			}
		}
	}

	if (INPUT->GetIsLButtonUp())
	{
		_moveClickTimer = 0;
	}
}

/// <summary>
/// 던전 지도 UI 재생성
/// </summary>
void MapManager::ReNewMapUI()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetChild("mapFrame");
	frame->GetVChildFrames().clear();

	int xIndex = GetPlayMap()->GetXIndex();
	int yIndex = GetPlayMap()->GetYIndex();

	for (int i = 0; i < _vStage[_currentStage]->GetMaps().size(); i++)
	{
		FieldMap* map = _vStage[_currentStage]->GetMaps()[i];
		
		if (map->GetVisited())
		{
			if (map->GetNextMapIndex(DIRECTION::DIR_LEFT) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineLeft", (map->GetXIndex() - xIndex) * 100 + 500 - 42, (map->GetYIndex() - yIndex) * 100 + 200 + 36, 42, 8, "Room_Line_LR", false, 0, 0, 1.0f, 1.0f, 125);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_RIGHT) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineRight", (map->GetXIndex() - xIndex) * 100 + 500 + 72, (map->GetYIndex() - yIndex) * 100 + 200 + 36, 42, 8, "Room_Line_LR", false, 0, 0, 1.0f, 1.0f, 125);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_UP) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineUp", (map->GetXIndex() - xIndex) * 100 + 500 + 36, (map->GetYIndex() - yIndex) * 100 + 200 - 42, 8, 42, "Room_Line_UD", false, 0, 0, 1.0f, 1.0f, 125);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_DOWN) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineDown", (map->GetXIndex() - xIndex) * 100 + 500 + 36, (map->GetYIndex() - yIndex) * 100 + 200 + 72, 8, 42, "Room_Line_UD", false, 0, 0, 1.0f, 1.0f, 125);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}
		}
	}

	for (int i = 0; i < _vStage[_currentStage]->GetMaps().size(); i++)
	{
		FieldMap* map = _vStage[_currentStage]->GetMaps()[i];
		
		if (map->GetVisited())
		{
			UIFrame* cntMap = new UIFrame();

			if (map->GetXIndex() == xIndex && map->GetYIndex() == yIndex)
			{
				cntMap->init("map_" + to_string(i), (map->GetXIndex() - xIndex) * 100 + 500, (map->GetYIndex() - yIndex) * 100 + 200, 72, 72, "Room_Selected");
			}

			else
			{
				cntMap->init("map_" + to_string(i), (map->GetXIndex() - xIndex) * 100 + 500, (map->GetYIndex() - yIndex) * 100 + 200, 72, 72, "Room");
			}

			cntMap->SetUseOutsideLimit(true);
			frame->AddFrame(cntMap);
		}
	}
}

void MapManager::release()
{
}

void MapManager::render(HDC hdc)
{
	_vStage[_currentStage]->GetMaps()[_currentMap]->render(hdc);
}

/// <summary>
/// 맵을 이동하는데에 사용
/// </summary>
void MapManager::ChangeMap(int stage, int index)
{
	_currentStage = stage;
	_currentMap = index;
	GetPlayMap()->PixelCollisionMapGenerate();
	GetPlayMap()->GridMapGenerate();
	GetPlayMap()->SetVisited(true);
	EFFECTMANAGER->GetVEffect().clear();
	PARTICLEMANAGER->GetParticles().clear();
	PARTICLEMANAGER->GetGenerators().clear();
	GenerateMapParticle();
	ENTITYMANAGER->getVBullets().clear();
	ReNewMapUI();


	if (ENTITYMANAGER->getPlayer()->GetWeapon(ENTITYMANAGER->getPlayer()->GetSelectedWeaponIdx()) != nullptr)
		ENTITYMANAGER->getPlayer()->GetWeapon(ENTITYMANAGER->getPlayer()->GetSelectedWeaponIdx())->ChangeMap();

	GetPlayMap()->DoorParticleGenerate();
}
