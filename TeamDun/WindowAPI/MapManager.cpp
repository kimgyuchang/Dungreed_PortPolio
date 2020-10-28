#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	_uidCount = 1;
	_vOriginMaps.clear();
	_stage = new Stage();

	_mapData = CSVMANAGER->csvLoad("Data/Maps.csv");

	MoveStage(0);

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
	_prevMapIndex = -1;
	_prevMapType = FIELDMAPTYPE::FMT_NULL;
	return S_OK;
}

void MapManager::update()
{
	_stageChanger->update();
	_stage->GetMaps()[_currentMap]->update();

	MapRandomChanger();
	GameResetter();
	DungeonMapUIMover();
	SetMapUIOnOff();
	UsePortalMap();
	MoveStageText();
}

/// <summary>
/// F6을 통해 초기부터 다시 시작 (스탯 재조정 X)
/// </summary>
void MapManager::GameResetter()
{
	if (INPUT->GetKeyDown(VK_F6)) 
	{
		MAPMANAGER->init();
	}
}


/// <summary>
/// F2를 통해 맵 랜덤 이동
/// </summary>
void MapManager::MapRandomChanger()
{
	if (INPUT->GetKeyDown(VK_F2))
	{
		ChangeMap(RANDOM->range((int)_stage->GetMaps().size()));
		GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}
}

/// <summary>
/// 스테이지 정보를 초기화한다.
/// </summary>
/// <param name="cntStage">초기화 할 스테이지 번호</param>
void MapManager::ClearStage(int cntStage)
{
	_vOriginMaps.clear();

	// 맵을 하나하나 추가한다.
	for (int i = 0; i < _mapData.size(); i++)
	{
		if (stoi(_mapData[i][1]) == cntStage)
		{
			FieldMap* map = new FieldMap();
			map->init(_mapData[i][0]);
			map->SetStage(stoi(_mapData[i][1]));
			map->LoadMap();

			// maps.csv의 데이터에 따른 Type 설정
			if (_mapData[i][2] == "NORMAL") map->SetFieldMapType(FIELDMAPTYPE::FMT_NORMAL);
			else if (_mapData[i][2] == "ENTER") map->SetFieldMapType(FIELDMAPTYPE::FMT_ENTER);
			else if (_mapData[i][2] == "END") map->SetFieldMapType(FIELDMAPTYPE::FMT_END);
			else if (_mapData[i][2] == "SHOP") map->SetFieldMapType(FIELDMAPTYPE::FMT_SHOP);
			else if (_mapData[i][2] == "RESTAURANT") map->SetFieldMapType(FIELDMAPTYPE::FMT_RESTAURANT);
			else if (_mapData[i][2] == "TEMPLE") map->SetFieldMapType(FIELDMAPTYPE::FMT_TEMPLE);
			else if (_mapData[i][2] == "STRAWBERRY") map->SetFieldMapType(FIELDMAPTYPE::FMT_STRAWBERRY);
			else if (_mapData[i][2] == "HUNGRY") map->SetFieldMapType(FIELDMAPTYPE::FMT_HUNGRY);
			else if (_mapData[i][2] == "TRAP") map->SetFieldMapType(FIELDMAPTYPE::FMT_TRAP);

			// 이 맵에 도착할 시의 위치 설정
			map->SetMovePos(DIRECTION::DIR_LEFT, POINT{ stoi(_mapData[i][3]), stoi(_mapData[i][4]) });
			map->SetMovePos(DIRECTION::DIR_RIGHT, POINT{ stoi(_mapData[i][5]), stoi(_mapData[i][6]) });
			map->SetMovePos(DIRECTION::DIR_UP, POINT{ stoi(_mapData[i][7]), stoi(_mapData[i][8]) });
			map->SetMovePos(DIRECTION::DIR_DOWN, POINT{ stoi(_mapData[i][9]), stoi(_mapData[i][10]) });

			_vOriginMaps.push_back(map);
		}
	}
}

/// <summary>
/// 스테이지 이동
/// </summary>
void MapManager::MoveStage(int stageNum)
{
	// 스테이지에 따른 BGM 설정
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

	bool mapAllCleared; // 맵이 제대로 만들어졌는지 여부
	_curStageNum = stageNum;

	while (true)
	{
		ClearStage(_curStageNum);
		mapAllCleared = true;

		// 스테이지를 새롭게 만든다
		_stage = new Stage();
		_stage->init(stageNum);
		if (!_stage->SettingMap()) mapAllCleared = false; // 스테이지를 만들고, 제대로 만들어지지 않았다면 다시 만들도록 한다.
		_stage->SetFieldMapNumber(); // 맵 별 index 설정

		if (mapAllCleared) break; // 맵이 제대로 만들어졌다면 break
	}

	if (stageNum == 2) SOUNDMANAGER->play("보스방입장문"); // 보스룸에 도착하면 사운드를 재생한다.

	_stageTextMoving = true; // 스테이지 글자를 움직이게 함
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
	// 스테이지 1 or 2의 경우
	if (_curStageNum == 1 || _curStageNum == 2)
	{
		// Square가 맵 전체에 추가됨
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

/// <summary>
/// 스테이지에 따른 카메라 제한 설정
/// </summary>
void MapManager::CameraLimitChecker()
{
	switch (_curStageNum)
	{
	case 0:
		CAMERAMANAGER->init(0, 0, 6720, 15000, 0, 0, WINSIZEX / 2, WINSIZEY / 2);
		break;
	case 1 : case 2: 
		CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
		break;
	}
}

/// <summary>
/// 던전 맵의 UI를 움직이게 한다.
/// </summary>
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
					_recentMousePos = _ptMouse; // 2프레임동안 누르고 있었다면 이 위치 저장
				}

				else if (_moveClickTimer >= 2) // 그 이후에는
				{
					for (int i = 0; i < mapFrame->GetVChildFrames().size(); i++)
					{
						mapFrame->GetVChildFrames()[i]->MoveFrameChild(_ptMouse.x - _recentMousePos.x, _ptMouse.y - _recentMousePos.y);
					} // 맵 UI를 움직여줌

					_recentMousePos = _ptMouse;
				}
			}
		}
	}

	// 버튼을 떼면 타이머를 초기화하여 더이상 따라오지 않게 함
	if (INPUT->GetIsLButtonUp())
	{
		_moveClickTimer = 0;
	}
}

/// <summary>
/// Portal NPC를 통해 맵 UI를 열었을 때 상호작용
/// </summary>
void MapManager::UsePortalMap()
{
	image* hoverImg = IMAGEMANAGER->findImage("Room_MouseHovered");

	if (_mapFrame->GetIsViewing() && _portalOn) // 포탈이 사용중이며 맵프레임이 보인다면
	{
		for (int i = 0; i < _stage->GetMaps().size(); i++) // 스테이지의 맵 사이즈만큼 돌며
		{
			UIFrame* mapSquare = _mapFrame->GetChild("map_" + to_string(i)); // 해당 맵의 사각형 UI

			if (i != _currentMap && mapSquare != nullptr && _stage->GetMapIndex(i)->GetPortal() != nullptr)
			{
				if (PtInRect(&mapSquare->GetRect(), _ptMouse))
				{
					mapSquare->SetImage(hoverImg); // 현재 마우스가 위치한 곳을 HoverImg로 바꿈
					if (INPUT->GetIsLButtonClicked()) // 클릭시에는 이동
					{
						SOUNDMANAGER->play("던전이동");
						if(_currentPortal != nullptr) _currentPortal->MoveMap(i);
						UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->SetIsViewing(false);
						_portalOn = false;
						_portalAnimOn = true;
					}
				}

				else if (mapSquare->GetImage() == hoverImg) // 마우스가 위치한 곳이 아니면 사각형 UI 이미지를 원래대로 돌려놓는다
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

	// 현재 맵의 x, y 좌표
	int xIndex = GetPlayMap()->GetXIndex();
	int yIndex = GetPlayMap()->GetYIndex();

	// 통로 선 이미지 생성 우선
	for (int i = 0; i < _stage->GetMaps().size(); i++)
	{
		FieldMap* map = _stage->GetMaps()[i];

		if (map->GetVisited()) // 방문한 맵만 표시
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

	// 방 Square 프레임 및 아이콘 생성
	for (int i = 0; i < _stage->GetMaps().size(); i++)
	{
		FieldMap* map = _stage->GetMaps()[i];

		if (map->GetVisited()) // 방문한 맵만 표시
		{
			UIFrame* cntMap = new UIFrame();

			if (map->GetXIndex() == xIndex && map->GetYIndex() == yIndex) // 현재 방문해있는 곳이라면
			{
				cntMap->init("map_" + to_string(i), (map->GetXIndex() - xIndex) * 100 + 500, (map->GetYIndex() - yIndex) * 100 + 200, 72, 72, "Room_Selected");
			}

			else
			{
				cntMap->init("map_" + to_string(i), (map->GetXIndex() - xIndex) * 100 + 500, (map->GetYIndex() - yIndex) * 100 + 200, 72, 72, "Room");
			}

			cntMap->SetUseOutsideLimit(true); // 이 UI가 부모의 범위를 넘어서지 못하도록함
			frame->AddFrame(cntMap);

			vector<int> icons = vector<int>();

			map->CheckDungeonMapIcons();
			if (map->GetHasTreasure()) icons.push_back(0); // 상자 여부
			if (map->GetHasPixie()) icons.push_back(1);	// 픽시 여부
			if (map->GetPortal() != nullptr) icons.push_back(2); // 포탈 여부

			// 그외 맵 아이콘 여부 (맵 타입이 추가되면 이곳을 수정해준다.)
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_RESTAURANT) icons.push_back(3);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_SHOP) icons.push_back(4);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_ENTER) icons.push_back(5);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_END) icons.push_back(6);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_TEMPLE) icons.push_back(7);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_STRAWBERRY) icons.push_back(8);
			if (map->GetFieldMapType() == FIELDMAPTYPE::FMT_HUNGRY) icons.push_back(9);

			// 아이콘을 쭉 돌며 그린다.
			for (int i = 0; i < icons.size(); i++)
			{
				UIFrame* cntIcon = new UIFrame();
				string imgName = "";

				// 이미지 설정
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

/// <summary>
/// 맵 이동
/// </summary>
void MapManager::ChangeMap(int index)
{
	SetPrevMapVariables();						// 이전의 맵 타입 및 인덱스 저장
	_currentMap = index;						// 현재 맵의 변경
	ChangeMapBGM(_prevMapType);					// 맵 전용 BGM 출력
	GetPlayMap()->PixelCollisionMapGenerate();	// 픽셀충돌맵 생성
	GetPlayMap()->GridMapGenerate();			// 레이어 랜더용 이미지 생성
	AdjustFirstVisitMap();						// 처음 방문한 맵에 대한 처리
	ClearChangeMapVectors();					// 요소 초기화
	CameraLimitChecker();						// 스테이지에 따른 카메라 제한 설정
	GenerateMapParticle();						// 맵 전용 파티클 추가
	ReNewMapUI();								// 던전맵 UI 재조정
	GetPlayMap()->DoorParticleGenerate();		// 문 파티클 초기화

	// 무기의 맵변경용 알고리즘 처리
	if (ENTITYMANAGER->getPlayer()->GetWeapon(ENTITYMANAGER->getPlayer()->GetSelectedWeaponIdx()) != nullptr)
		ENTITYMANAGER->getPlayer()->GetWeapon(ENTITYMANAGER->getPlayer()->GetSelectedWeaponIdx())->ChangeMap();
}

/// <summary>
/// 이전의 맵 타입 및 인덱스 저장
/// </summary>
void MapManager::SetPrevMapVariables()
{
	if (_currentMap >= 0 && _currentMap < _stage->GetMaps().size()) // 이전 맵 존재시
	{
		_prevMapType = GetPlayMap()->GetFieldMapType();
		_prevMapIndex = MAPMANAGER->GetPlayMap()->GetMapIndex();
	}

	else // 이전 맵 없을시
	{
		_prevMapType = FIELDMAPTYPE::FMT_NULL;
		_prevMapIndex = -1;
	}
}

/// <summary>
/// 맵 바뀔시의 여러 요소 초기화
/// </summary>
void MapManager::ClearChangeMapVectors()
{
	EFFECTMANAGER->GetVEffect().clear();
	PARTICLEMANAGER->GetParticles().clear();
	PARTICLEMANAGER->GetGenerators().clear();
	ENTITYMANAGER->getVBullets().clear();
}

/// <summary>
/// 첫 방문 맵에 대한 시스템
/// </summary>
void MapManager::AdjustFirstVisitMap()
{
	if (!GetPlayMap()->GetVisited()) // 방문하지 않았다면
	{
		int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() - 2 - ENTITYMANAGER->getPlayer()->GetRoomMoveSatiation();
		if (satiety < 0) satiety = 0;
		ENTITYMANAGER->getPlayer()->SetSatiety(satiety); // 포만감 감소
		GetPlayMap()->SetVisited(true); // 방문상태로
	}
}

/// <summary>
/// 맵의 타입에 따른 BGM 변경
/// </summary>
void MapManager::ChangeMapBGM(FIELDMAPTYPE prevMapType)
{
	if (prevMapType != FIELDMAPTYPE::FMT_NULL) // 이전의 맵이 존재한다면
	{
		if (GetPlayMap()->GetFieldMapType() == FIELDMAPTYPE::FMT_RESTAURANT) // 식당
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("Foodshop");
			SOUNDMANAGER->play("ambience_prison");
		}

		else if (GetPlayMap()->GetFieldMapType() == FIELDMAPTYPE::FMT_SHOP) // 상점
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("Shop");
			SOUNDMANAGER->play("ambience_prison");
		}

		else if (GetPlayMap()->GetFieldMapType() != FIELDMAPTYPE::FMT_SHOP && GetPlayMap()->GetFieldMapType() != FIELDMAPTYPE::FMT_RESTAURANT &&
			(prevMapType == FIELDMAPTYPE::FMT_SHOP || prevMapType == FIELDMAPTYPE::FMT_RESTAURANT)) // 그외 원래대로 돌림
		{
			SOUNDMANAGER->StopAllBGM();
			SOUNDMANAGER->play("1.JailField");
			SOUNDMANAGER->play("ambience_prison");
		}
	}
}

/// <summary>
/// 스테이지 텍스트의 이동
/// </summary>
void MapManager::MoveStageText()
{
	if (_stageTextMoving)
	{
		switch (_curStageNum) // 스테이지별 텍스트 설정
		{
		case 0: _stageNameText->SetText("마을");  break;
		case 1: _stageNameText->SetText("1층 : 지하 감옥"); break;
		case 2: _stageNameText->SetText("2층 : 벨리알의 방"); break;
		}
		_stageNameText->SetIsViewing(true);

		// 움직임 수치 세부 조정
		if (_textMovingStartTimer > 60)
		{
			_textMovingMoveTimer++;
			if (_textMovingMoveTimer < 60)
			{
				_stageNameText->MoveFrameChild(_stageNameSpeedX, 0); // 움직여줌
				_stageNameSpeedX += _stageNameGravity;
			}

			else if (_textMovingMoveTimer  < 120)
			{
				_stageNameSpeedX = 0; // 움직임 고정
				_stageNameGravity = -0.56f; 
			}

			else if (_textMovingMoveTimer < 180)
			{
				_stageNameText->MoveFrameChild(_stageNameSpeedX, 0); // 움직여줌
				_stageNameSpeedX += _stageNameGravity;
			}

			else // 다시 원상복귀
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

void MapManager::release()
{
}

void MapManager::render(HDC hdc)
{
	_stage->GetMaps()[_currentMap]->render(hdc); // 현재 플레이중인 맵 렌더
}