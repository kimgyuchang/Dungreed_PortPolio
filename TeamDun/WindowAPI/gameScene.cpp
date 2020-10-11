#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{

	_scrollTimer = 0;
	_mouseLocation = 0;

	UIMANAGER->init();
	initUI();

	MAPMANAGER->init();
	_p = new Player();
	_p->init();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);

	PARTICLEMANAGER->init();
	EFFECTMANAGER->init();

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	_vCharName = vector<string>{ "모험가", "판금의 용사", "석양의 총잡이", "앨리스", "홍련", "이키나곰", 
							     "라이더 H", "범죄자 실루엣", "곡괭이의 왕", "뚱뚱보", "마검사", "인간 라슬리", "마스터 셰프" };
	_CharExplanation = vector<string>{ "던전은 탐사하기 위해 온 초보 모험가","판금 갑옷을 두른, 든든한 용사","황야를 가로지르는 외로운 총잡이",
									   "토끼는 보이지 않고, 멋진 표적이 가득해!","저 너머로...개화하고 싶지 않은가, 그대?","시..시..시니컬이라구! 흥!",
									   "뼈를 깎더라도,\n어디에서든 달리고 싶다.","범행 동기도 가지각색.\n범행 물품도 천차만별.","세상을 지배할 뻔한 살아있는 전설",
									   "잘 달리지는 못하지만,\n 휘두르는 건 무척 잘할거에요.","부활이 꼭 재생을 의미하는 것은 아니듯이.",
									   "마검에 사로잡히기 전 그의 모습이다.","우주 어딘가 유명한 레스토랑의 주방장. 총 쏘는 솜씨도 일품이라고 한다."};
	_CharAbility = vector<string>{ "","","▶ 권총 전문가: 권총 태그가 붙은 무기를 사용하면 위력이 50 상승합니다",
									  "▶ 원시: 일정 반경 안에 적이 있다면 위력이 -20 감소합니다.",
									  "▶ 표식: 적을 공격하면 위력을 6올려주는 표식을 남깁니다.(최대 10개)",
									  "▶ 격노: 적을 때리거나 처치하면 격노를 획득합니다. 격노 수치가 다 차면 일정\n시간 동안 공격속도가 100% 상승합니다.",
									  "▶ 속도광: 현재 속도에 비례해 위력을 최대 +50까지 획득합니다.",
									  "▶ 범행도구: 가지고 있는 아이템 1개당 위력 +4, 방어력 -2, 체력-1을\n획득합니다. (장착 중인 아이템 포함)","",
									  "▶ 풀스윙: 근접 무기를 사용하면 위력이 30 상승합니다.",
									  "▶ 부활의 저주: 체력이 40으로 고정됩니다. 쓰러지면 2회 부활할 수 있습니다.",
									  "▶ 흡수: 보스를 처지할 때마다 최대 체력 증가, 최대 체력 -45 감소합니다.",
									  "▶ 보호막 생성" };
	_CharFirstStat = vector<string>{ "","▶ +10 방어력","▶ -15 최대 체력","▶ -30 최대 체력","▶ -15 최대 체력","▶ -20 위력","▶ +22% 이동속도","","▶ +1 대쉬 횟수","▶ -20% 이동속도","","","▶ 조준 정확도 +33"};
	_CharSecondStat = vector<string>{"","▶ -10 최대 체력","▶ -15 방어력","▶ +40 위력","▶ -5 회피","▶ -5 방어력","▶ -2 강인함","▶ -12 회피","▶ -25 크리티컬","▶ -10% 공격속도","","","▶ +33 최대 체력"};

	CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void gameScene::initUI()
{
	// UIFrame

	UIImage* allMapFrame = new UIImage();
	allMapFrame->init("allMapFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 1, 1, 80);
	UIMANAGER->GetGameFrame()->AddFrame(allMapFrame);

	UIFrame* mapUpperImg = new UIFrame();
	mapUpperImg->init("mapUpperImg", 0, 0, IMAGEMANAGER->findImage("MapBase_1_0")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_0")->getHeight(), "MapBase_1_0", 1.0f, 1.0f);
	allMapFrame->AddFrame(mapUpperImg);

	UIFrame* mapFrame = new UIFrame();
	mapFrame->init("mapFrame", 130, 180, IMAGEMANAGER->findImage("MapBase_1_1")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_1")->getHeight(), "MapBase_1_1", 1.5f, 1.4f);
	mapFrame->SetUseOutsideLimit(true);
	allMapFrame->AddFrame(mapFrame);

	UIFrame* warDrobeFrame = new UIFrame();
	warDrobeFrame->init("warDrobeFrame", 0, 0, IMAGEMANAGER->findImage("ScreenCover")->getWidth(), IMAGEMANAGER->findImage("ScreenCover")->getHeight(), "ScreenCover");
	UIMANAGER->GetGameFrame()->AddFrame(warDrobeFrame);
	warDrobeFrame->SetIsViewing(false);

	UIFrame* warDrobetitle = new UIFrame();
	warDrobetitle->init("CostumeBase_0", 250, 0, IMAGEMANAGER->findImage("CostumeBase_0")->getWidth(), IMAGEMANAGER->findImage("CostumeBase_0")->getHeight(), "CostumeBase_0");
	warDrobeFrame->AddFrame(warDrobetitle);

	UIFrame* baseFrame = new UIFrame();
	baseFrame->init("Base", -50, 87, IMAGEMANAGER->findImage("Base")->getWidth(), IMAGEMANAGER->findImage("Base")->getHeight(), "Base", 7, 1.63);
	warDrobeFrame->AddFrame(baseFrame);

	UIFrame* costumeExplanationFrame = new UIFrame();
	costumeExplanationFrame->init("CostumeBase_1", 0, 400, IMAGEMANAGER->findImage("CostumeBase_1")->getWidth(), IMAGEMANAGER->findImage("CostumeBase_1")->getHeight(), "CostumeBase_1", 1.5, 2.5);
	warDrobeFrame->AddFrame(costumeExplanationFrame);

	UIFrame* costumeExplanationBox = new UIFrame();
	costumeExplanationBox->init("SlotDeleteButton_Rev", 500, 180, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 0.6, 0.7);
	costumeExplanationFrame->AddFrame(costumeExplanationBox);

	UIFrame* costumeExplanationSecondBox = new UIFrame();
	costumeExplanationSecondBox->init("SlotDeleteButton_Rev", 1375, 80, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 0.6, 1.2);
	costumeExplanationFrame->AddFrame(costumeExplanationSecondBox);

	for (int i = 0; i < 13; i++)
	{
		UIFrame* warDrobeBox = new UIFrame();
		warDrobeBox->init("CostumeBack" + to_string(i), 220 * i, 5, IMAGEMANAGER->findImage("CostumeBack")->getWidth(), IMAGEMANAGER->findImage("CostumeBack")->getHeight(), "CostumeBack", 1, 1);
		baseFrame->AddFrame(warDrobeBox);
	}

	for (int i = 0; i < 13; i++)
	{
		UIFrame* warDrobeCharFrame = new UIFrame();
		warDrobeCharFrame->init("CostumeUnlocked" + to_string(i), 220 * i + 10, 15, IMAGEMANAGER->findImage("CostumeUnlocked")->getWidth(), IMAGEMANAGER->findImage("CostumeUnlocked")->getHeight(), "CostumeUnlocked");
		baseFrame->AddFrame(warDrobeCharFrame);

		UIImage* warDrobeCharBoxIg = new UIImage();
		warDrobeCharBoxIg->init("char", 77, 180, 51, 63, "", false, 0, 0);
		warDrobeCharFrame->AddFrame(warDrobeCharBoxIg);
	}

	for (int i = 0; i < 13; i++)
	{
		UIFrame* costumeFrame = new UIFrame();
		costumeFrame->init("CostumeOver" + to_string(i), 220 * i + 10, 15, IMAGEMANAGER->findImage("CostumeOver")->getWidth(), IMAGEMANAGER->findImage("CostumeOver")->getHeight(), "CostumeOver");
		baseFrame->AddFrame(costumeFrame);
	}

	UIFrame* adventurer = new UIFrame();
	adventurer->init("adventurer", 75, 180, IMAGEMANAGER->findImage("adventurer")->getWidth(), IMAGEMANAGER->findImage("adventurer")->getHeight(), "adventurer");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(0))->AddFrame(adventurer);

	UIFrame* sheeting = new UIFrame();
	sheeting->init("sheeting", 75, 178, IMAGEMANAGER->findImage("sheeting")->getWidth(), IMAGEMANAGER->findImage("sheeting")->getHeight(), "sheeting");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(1))->AddFrame(sheeting);

	UIFrame* gunman = new UIFrame();
	gunman->init("gunman", 70, 175, IMAGEMANAGER->findImage("gunman")->getWidth(), IMAGEMANAGER->findImage("gunman")->getHeight(), "gunman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(2))->AddFrame(gunman);

	UIFrame* alice = new UIFrame();
	alice->init("alice", 75, 180, IMAGEMANAGER->findImage("alice")->getWidth(), IMAGEMANAGER->findImage("alice")->getHeight(), "alice");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(3))->AddFrame(alice);

	UIFrame* redlotus = new UIFrame();
	redlotus->init("redlotus", 75, 180, IMAGEMANAGER->findImage("redlotus")->getWidth(), IMAGEMANAGER->findImage("redlotus")->getHeight(), "redlotus");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(4))->AddFrame(redlotus);

	UIFrame* lkinabear = new UIFrame();
	lkinabear->init("lkinabear", 75, 180, IMAGEMANAGER->findImage("lkinabear")->getWidth(), IMAGEMANAGER->findImage("lkinabear")->getHeight(), "lkinabear");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(5))->AddFrame(lkinabear);

	UIFrame* riderH = new UIFrame();
	riderH->init("riderH", 55, 180, IMAGEMANAGER->findImage("riderH")->getWidth(), IMAGEMANAGER->findImage("riderH")->getHeight(), "riderH");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(6))->AddFrame(riderH);

	UIFrame* criminal = new UIFrame();
	criminal->init("criminal", 75, 180, IMAGEMANAGER->findImage("criminal")->getWidth(), IMAGEMANAGER->findImage("criminal")->getHeight(), "criminal");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(7))->AddFrame(criminal);

	UIFrame* pick = new UIFrame();
	pick->init("pick", 75, 180, IMAGEMANAGER->findImage("pick")->getWidth(), IMAGEMANAGER->findImage("pick")->getHeight(), "pick");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(8))->AddFrame(pick);

	UIFrame* fasto = new UIFrame();
	fasto->init("fasto",75,180, IMAGEMANAGER->findImage("fasto")->getWidth(), IMAGEMANAGER->findImage("fasto")->getHeight(), "fasto");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(9))->AddFrame(fasto);

	UIFrame* horseman = new UIFrame();
	horseman->init("horseman", 75, 180, IMAGEMANAGER->findImage("horseman")->getWidth(), IMAGEMANAGER->findImage("horseman")->getHeight(), "horseman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(10))->AddFrame(horseman);

	UIFrame* humanlasley = new UIFrame();
	humanlasley->init("humanlasley", 75, 180, IMAGEMANAGER->findImage("humanlasley")->getWidth(), IMAGEMANAGER->findImage("humanlasley")->getHeight(), "humanlasley");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(11))->AddFrame(humanlasley);

	UIFrame* masterchef = new UIFrame();
	masterchef->init("masterchef", 75, 180, IMAGEMANAGER->findImage("masterchef")->getWidth(), IMAGEMANAGER->findImage("masterchef")->getHeight(), "masterchef");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(12))->AddFrame(masterchef);

	
	UIText* charNameText = new UIText();
	charNameText->init("charNameText", 50, 100, 400, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 204, 0));
	costumeExplanationFrame->AddFrame(charNameText);

	UIText* CharExplanationText = new UIText();
	CharExplanationText->init("CharExplanationText", 50, 200, 400, 50, "", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharExplanationText);

	UIText* CharAbilityText = new UIText();
	CharAbilityText->init("CharAbilityText", 550, 150, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(0, 255, 0));
	costumeExplanationFrame->AddFrame(CharAbilityText);

	UIText* _CharFirstStat = new UIText();
	_CharFirstStat->init("CharFirstStat", 550, 200, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255,255));
	costumeExplanationFrame->AddFrame(_CharFirstStat);

	UIText* _CharSecondStat = new UIText();
	_CharSecondStat->init("CharSecondStat", 550, 250, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(_CharSecondStat);


	allMapFrame->SetIsViewing(false);
}

void gameScene::release()
{
	ENTITYMANAGER->release();
	ENTITYMANAGER->releaseSingleton();
	MAPMANAGER->release();
	MAPMANAGER->releaseSingleton();
	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();
	PARTICLEMANAGER->release();
	PARTICLEMANAGER->releaseSingleton();
}

void gameScene::update()
{
	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("시작화면");
	}

	MAPMANAGER->update();
	CAMERAMANAGER->MovePivotLerp(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 5.f);
	ENTITYMANAGER->update();
	EFFECTMANAGER->update();
	PARTICLEMANAGER->update();
	UIMANAGER->update();

	if (INPUT->GetKeyDown('P'))
	{
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->ToggleIsViewing();
		for (int i = 0; i < 13; i++)
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
		}
	}

	if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetRect(), _ptMouse) && INPUT->GetKey(VK_LBUTTON))
	{
		_scrollTimer++;
		if (_scrollTimer == 10)
		{
			_mouseLocation = _ptMouse.x;
		}
		
		else if(_scrollTimer > 10)
		{
			for (int i = 0; i < 13; i++)
			{
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeBack" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->MoveFrameChild(_ptMouse.x-_mouseLocation, 0);
			}
			_mouseLocation = _ptMouse.x;
		}
	}

	if (INPUT->GetKeyUp(VK_LBUTTON))
	{
		_scrollTimer = 0;
		_mouseLocation = 0;
	}

	for (int i = 0; i < 13; i++)
	{
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->GetRect(), _ptMouse))
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(true);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("charNameText"))->SetText(_vCharName[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharExplanationText"))->SetText(_CharExplanation[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharAbilityText"))->SetText(_CharAbility[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharFirstStat"))->SetText(_CharFirstStat[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharSecondStat"))->SetText(_CharSecondStat[i]);
		}
		else
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
	}
}

void gameScene::render()
{
	MAPMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());

	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));

	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	string n = to_string((int)CAMERAMANAGER->GetAbsoluteX(_ptMouse.x)) + " " + to_string((int)CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));

	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, n.c_str(), n.length());
}
