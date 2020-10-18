#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	_vOriginMaps.clear();
	_stage = new Stage();

	_mapData = CSVMANAGER->csvLoad("Data/Maps.csv");
	
	AddStage(1);
	_mapFrame = UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetChild("mapFrame");
	_pixelGetter = new PixelGetter();
	ChangeMap(0);
	MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_DOWN);
	_portalAnimOn = false;
	_stageChanger = new StageChanger();
	_stageChanger->init();
	return S_OK;
}

void MapManager::ClearStage(int cntStage)
{
	_vOriginMaps.clear();

	for (int i = 0; i < _mapData.size(); i++)
	{
		if (stoi(_mapData[i][1]) == cntStage) 
		{
			FieldMap* map = new FieldMap();
			map->init(_mapData[i][0]);
			map->SetStage(stoi(_mapData[i][1]));
			map->LoadMap();

			if (_mapData[i][2] == "NORMAL") map->SetFieldType(FIELDMAPTYPE::FMT_NORMAL);
			else if (_mapData[i][2] == "ENTER") map->SetFieldType(FIELDMAPTYPE::FMT_ENTER);
			else if (_mapData[i][2] == "END") map->SetFieldType(FIELDMAPTYPE::FMT_END);
			else if (_mapData[i][2] == "SHOP") map->SetFieldType(FIELDMAPTYPE::FMT_SHOP);
			else if (_mapData[i][2] == "RESTAURANT") map->SetFieldType(FIELDMAPTYPE::FMT_RESTAURANT);
			else if (_mapData[i][2] == "TEMPLE") map->SetFieldType(FIELDMAPTYPE::FMT_TEMPLE);

			map->SetMovePos(DIRECTION::DIR_LEFT, POINT{ stoi(_mapData[i][3]), stoi(_mapData[i][4]) });
			map->SetMovePos(DIRECTION::DIR_RIGHT, POINT{ stoi(_mapData[i][5]), stoi(_mapData[i][6]) });
			map->SetMovePos(DIRECTION::DIR_UP, POINT{ stoi(_mapData[i][7]), stoi(_mapData[i][8]) });
			map->SetMovePos(DIRECTION::DIR_DOWN, POINT{ stoi(_mapData[i][9]), stoi(_mapData[i][10]) });

			_vOriginMaps.push_back(map);
		}
	}
}

void MapManager::AddStage(int stageNum)
{
	switch (stageNum)
	{
		case 0: 
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("0.Town"); 
			SOUNDMANAGER->play("ambience_town"); 
			break;
		}

		case 1: 
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("1.JailField"); 
			SOUNDMANAGER->play("ambience_prison"); 
			break;
		}

		case 2: 
			SOUNDMANAGER->StopAllBGM(); 
			SOUNDMANAGER->play("ambience_prison");
			break; // 보스방에서는 잠시 BGM을 멈춰줌 (이후 스폰시 1.JailBoss 재생)
	}

	bool mapAllCleared;
	_curStageNum = stageNum;
	while (true)
	{
		ClearStage(_curStageNum);
		mapAllCleared = true;
		_stage = new Stage();
		_stage->init(stageNum);
		if (!_stage->SettingMap()) mapAllCleared = false;
		if (mapAllCleared) break;
	}
}
void MapManager::update()
{
	if (INPUT->GetKeyDown(VK_F2))
	{
		ChangeMap(RANDOM->range((int)_stage->GetMaps().size()));
		GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}

	if (INPUT->GetKeyDown(VK_F6))
	{
		MAPMANAGER->init();
	}

	_stageChanger->update();
	_stage->GetMaps()[_currentMap]->update();
	DungeonMapUIMover();
	SetMapUIOnOff();
	UsePortalMap();
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
	if (_curStageNum == 1 || _curStageNum == 2)
	{
		CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
		ParticleGenerator* mapSquareGen = new ParticleGenerator();
		mapSquareGen->initGenerator(REGULARGEN, 100000, 3, 0, 1, vector<string>{ "SqaureParticle" });
		mapSquareGen->initPos(GetPlayMap()->GetMapSizeX() * 24, GetPlayMap()->GetMapSizeY() * 24, GetPlayMap()->GetMapSizeX() * 44, GetPlayMap()->GetMapSizeY() * 44);
		mapSquareGen->initAlpha(150, 50, 1);
		mapSquareGen->initTime(150, 10);
		mapSquareGen->initScale(0.5f, 1.0f, 0);
		mapSquareGen->initSpeed(0.5f, 0.5f, 0.3f, 0.3f, 0, 0);
		PARTICLEMANAGER->AddGenerator(mapSquareGen);
	}
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

void MapManager::UsePortalMap()
{
	image* hoverImg = IMAGEMANAGER->findImage("Room_MouseHovered");

	if (_mapFrame->GetIsViewing() && _portalOn)
	{
		for (int i = 0; i < _stage->GetMaps().size(); i++)
		{
			UIFrame* mapSquare = _mapFrame->GetChild("map_" + to_string(i));
			if (i != _currentMap && mapSquare != nullptr && _stage->GetMapIndex(i)->GetPortal() != nullptr)
			{
				if (PtInRect(&mapSquare->GetRect(), _ptMouse))
				{
					mapSquare->SetImage(hoverImg);
					if (INPUT->GetIsLButtonClicked())
					{
						_currentPortal->MoveMap(i);
						UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->SetIsViewing(false);
						_portalOn = false;
						_portalAnimOn = true;
					}
				}

				else if (mapSquare->GetImage() == hoverImg)
				{
					mapSquare->SetImage(IMAGEMANAGER->findImage("Room"));
				}
			}
		}
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

	for (int i = 0; i < _stage->GetMaps().size(); i++)
	{
		FieldMap* map = _stage->GetMaps()[i];

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

	for (int i = 0; i < _stage->GetMaps().size(); i++)
	{
		FieldMap* map = _stage->GetMaps()[i];

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
	_stage->GetMaps()[_currentMap]->render(hdc);
}

/// <summary>
/// 맵을 이동하는데에 사용
/// </summary>
void MapManager::ChangeMap(int index)
{
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
