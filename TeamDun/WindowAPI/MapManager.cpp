#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	_uidCount = 1;
	_vOriginMaps.clear();
	_stage = new Stage();

	_mapData = CSVMANAGER->csvLoad("Data/Maps.csv");
	

	AddStage(0);

	_mapFrame = UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetChild("mapFrame");
	_pixelGetter = new PixelGetter();
	ChangeMap(0);
	MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_DOWN);
	
	_portalAnimOn = false;
	_stageChanger = new StageChanger();
	_stageChanger->init();
	
	_stageTextMoving = false;
	_stageNameGravity = 0.56f;
	_stageNameSpeedX = -34;
	_textMovingMoveTimer = 0;
	_textMovingStartTimer = 0;
	_stageNameText = dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("stageName"));
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

			if (_mapData[i][2] == "NORMAL") map->SetFieldMapType(FIELDMAPTYPE::FMT_NORMAL);
			else if (_mapData[i][2] == "ENTER") map->SetFieldMapType(FIELDMAPTYPE::FMT_ENTER);
			else if (_mapData[i][2] == "END") map->SetFieldMapType(FIELDMAPTYPE::FMT_END);
			else if (_mapData[i][2] == "SHOP") map->SetFieldMapType(FIELDMAPTYPE::FMT_SHOP);
			else if (_mapData[i][2] == "RESTAURANT") map->SetFieldMapType(FIELDMAPTYPE::FMT_RESTAURANT);
			else if (_mapData[i][2] == "TEMPLE") map->SetFieldMapType(FIELDMAPTYPE::FMT_TEMPLE);
			else if (_mapData[i][2] == "STRAWBERRY") map->SetFieldMapType(FIELDMAPTYPE::FMT_STRAWBERRY);
			else if (_mapData[i][2] == "HUNGRY") map->SetFieldMapType(FIELDMAPTYPE::FMT_HUNGRY);
			else if (_mapData[i][2] == "TRAP") map->SetFieldMapType(FIELDMAPTYPE::FMT_TRAP);

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
		_stage->SetFieldMapNumber();
		if (mapAllCleared) break;
	}

	if(stageNum == 2) SOUNDMANAGER->play("보스방입장문");

	_stageTextMoving = true;
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
	MoveStageText();
}

/// <summary>
/// 던전 지도 UI를 OnOff
/// </summary>
void MapManager::SetMapUIOnOff()
{
	if (INPUT->GetKeyDown(VK_TAB))
	{
		_portalOn = false;
		MAPMANAGER->ReNewMapUI();
		UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->ToggleIsViewing();
	}

	else if (INPUT->GetIsEscapeKeyPressed() && UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetIsViewing())
	{
		_portalOn = false;
		MAPMANAGER->ReNewMapUI();
		UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->SetIsViewing(false);
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

	else if(_curStageNum == 0)
	{
		CAMERAMANAGER->init(0, 0, 6720, 15000, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
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
						SOUNDMANAGER->play("던전이동");
						if(_currentPortal != nullptr) _currentPortal->MoveMap(i);
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
				line->init("map_" + to_string(i) + "_lineLeft", (map->GetXIndex() - xIndex) * 100 + 500 - 42, (map->GetYIndex() - yIndex) * 100 + 200 + 36, 42, 8, "Room_Line_LR", false, 0, 0);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_RIGHT) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineRight", (map->GetXIndex() - xIndex) * 100 + 500 + 72, (map->GetYIndex() - yIndex) * 100 + 200 + 36, 42, 8, "Room_Line_LR", false, 0, 0);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_UP) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineUp", (map->GetXIndex() - xIndex) * 100 + 500 + 36, (map->GetYIndex() - yIndex) * 100 + 200 - 42, 8, 42, "Room_Line_UD", false, 0, 0);
				frame->AddFrame(line);
				line->SetUseOutsideLimit(true);
			}

			if (map->GetNextMapIndex(DIRECTION::DIR_DOWN) != -1)
			{
				UIImage* line = new UIImage();
				line->init("map_" + to_string(i) + "_lineDown", (map->GetXIndex() - xIndex) * 100 + 500 + 36, (map->GetYIndex() - yIndex) * 100 + 200 + 72, 8, 42, "Room_Line_UD", false, 0, 0);
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

			vector<int> icons = vector<int>();

			map->CheckDungeonMapIcons();
			if (map->GetHasTreasure()) icons.push_back(0);
			if (map->GetHasPixie()) icons.push_back(1);
			if (map->GetPortal() != nullptr) icons.push_back(2);

			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_RESTAURANT) icons.push_back(3);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_SHOP) icons.push_back(4);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_ENTER) icons.push_back(5);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_END) icons.push_back(6);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_TEMPLE) icons.push_back(7);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_STRAWBERRY) icons.push_back(8);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_HUNGRY) icons.push_back(9);

			for (int i = 0; i < icons.size(); i++)
			{
				UIFrame* cntIcon = new UIFrame();
				string imgName = "";
				switch (icons[i])
				{
				case 0:	imgName = "Chest";	break;
				case 1:	imgName = "FairyMap";	break;
				case 2:	imgName = ((map->GetXIndex() == xIndex && map->GetYIndex() == yIndex) ? "Worm_Selected" : "Worm");	break;
				case 3:	imgName = "FoodMap";	break;
				case 4:	imgName = "ShopMap";	break;
				case 5:	imgName = "EnteranceMap";	break;
				case 6:	imgName = "ExitMap";	break;
				case 7:	imgName = "Altar";	break;
				case 8:	imgName = "Berry";	break;
				case 9:	imgName = "Hungry";	break;
				}

				int x = (icons.size() != 1 ? (icons.size() != 3 || i != 2 ? 12 : 24) : 24) + (i % 2) * 24; // 아이콘의 x위치를 중앙정렬 가능하면 중앙정렬하도록
				int y = (icons.size() > 2 ? 12 : 24) + (i / 2) * 24; // 아이콘의 y위치를 중앙정렬 가능하면 중앙정렬하도록

				cntIcon->init("icon" + to_string(i), x, y, 24, 24, imgName);
				cntMap->AddFrame(cntIcon);
			}
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
	FIELDMAPTYPE prevMapType;
	int prevMapIndex = -1;

	if (_currentMap >= 0 && _currentMap < _stage->GetMaps().size())
	{
		prevMapType = GetPlayMap()->GetFieldMapType();
		prevMapIndex = MAPMANAGER->GetPlayMap()->GetMapIndex();
	}

	else
	{
		prevMapType = FIELDMAPTYPE::FMT_NULL;
		prevMapIndex = -1;
	}

	_currentMap = index;
	
	ChangeMapBGM(prevMapType);

	GetPlayMap()->PixelCollisionMapGenerate();
	GetPlayMap()->GridMapGenerate();
	
	if (!GetPlayMap()->GetVisited())
	{
		int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() - 2 - ENTITYMANAGER->getPlayer()->GetRoomMoveSatiation();
		if (satiety < 0) satiety = 0;
		ENTITYMANAGER->getPlayer()->SetSatiety(satiety);
		GetPlayMap()->SetVisited(true);
	}

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

void MapManager::ChangeMapBGM(FIELDMAPTYPE prevMapType)
{
	if (prevMapType != FIELDMAPTYPE::FMT_NULL)
	{
		if (GetPlayMap()->GetFieldMapType() == FIELDMAPTYPE::FMT_RESTAURANT)
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("Foodshop");
			SOUNDMANAGER->play("ambience_prison");
		}

		else if (GetPlayMap()->GetFieldMapType() == FIELDMAPTYPE::FMT_SHOP)
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("Shop");
			SOUNDMANAGER->play("ambience_prison");
		}

		else if (GetPlayMap()->GetFieldMapType() != FIELDMAPTYPE::FMT_SHOP && GetPlayMap()->GetFieldMapType() != FIELDMAPTYPE::FMT_RESTAURANT &&
			(prevMapType == FIELDMAPTYPE::FMT_SHOP || prevMapType == FIELDMAPTYPE::FMT_RESTAURANT))
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("1.JailField");
			SOUNDMANAGER->play("ambience_prison");
		}
	}
}

void MapManager::MoveStageText()
{
	if (_stageTextMoving)
	{
		switch (_curStageNum)
		{
		case 0: _stageNameText->SetText("마을");  break;
		case 1: _stageNameText->SetText("1층 : 지하 감옥"); break;
		case 2: _stageNameText->SetText("2층 : 벨리알의 방"); break;
		}
		_stageNameText->SetIsViewing(true);

		if (_textMovingStartTimer > 60)
		{
			_textMovingMoveTimer++;
			if (_textMovingMoveTimer < 60)
			{
				_stageNameText->MoveFrameChild(_stageNameSpeedX, 0);
				_stageNameSpeedX += _stageNameGravity;
			}

			else if (_textMovingMoveTimer  < 120)
			{
				_stageNameSpeedX = 0;
				_stageNameGravity = -0.56f;
			}

			else if (_textMovingMoveTimer < 180)
			{
				_stageNameText->MoveFrameChild(_stageNameSpeedX, 0);
				_stageNameSpeedX += _stageNameGravity;
			}

			else
			{
				_stageTextMoving = false;
				_stageNameGravity = 0.56f;
				_stageNameSpeedX = -34;
				_textMovingMoveTimer = 0;
				_textMovingStartTimer = 0;
				_stageNameText->SetX(WINSIZEX + 100);
			}
		}

		else
		{
			_textMovingStartTimer++;
		}
	}
}