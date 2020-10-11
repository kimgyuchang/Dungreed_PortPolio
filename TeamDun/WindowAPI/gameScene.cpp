#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	INPUT->init();

	UIMANAGER->init();
	initUI();

	_p = new Player();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);
	_p->init();

	MAPMANAGER->init();

	
	PARTICLEMANAGER->init();
	EFFECTMANAGER->init();

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	_vCharName = vector<string>{ "모험가", "판금의 용사", "석양의 총잡이", "앨리스", "홍련", "이키나곰", "라이더 H", "범죄자 실루엣", "곡괭이의 왕", "뚱뚱보", "마검사", "인간 라슬리", "마스터 셰프" };
	_CharExplanation = vector<string>{ "던전은 탐사하기 위해 온 초보 모험가","판금 갑옷을 두른, 든든한 용사","황야를 가로지르는 외로운 총잡이",
	"토끼는 보이지 않고, 멋진 표적이 가득해!","저 너머로...개화하고 싶지 않은가, 그대?","시..시..시니컬이라구! 흥!",
	"뼈를 깎더라도,\n어디에서든 달리고 싶다.","범행 동기도 가지각색.\n범행 물품도 천차만별.","세상을 지배할 뻔한 살아있는 전설" };
	CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void gameScene::initUI()
{
	DungeonMapUIInit();

	// WarDrobe Frame //
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
	costumeExplanationBox->init("SlotDeleteButton_Rev", 500, 180, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 1, 0.7);
	costumeExplanationFrame->AddFrame(costumeExplanationBox);

	UIFrame* costumeExplanationSecondBox = new UIFrame();
	costumeExplanationSecondBox->init("SlotDeleteButton_Rev", 1350, 80, IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getWidth(), IMAGEMANAGER->findImage("SlotDeleteButton_Rev")->getHeight(), "SlotDeleteButton_Rev", 1, 1.2);
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

	UIText* charNameText = new UIText();
	charNameText->init("charNameText", 50, 100, 400, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(charNameText);

	UIText* CharExplanationText = new UIText();
	CharExplanationText->init("CharExplanationText", 50, 200, 400, 50, "", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharExplanationText);

	InventoryUIInit();
}

void gameScene::DungeonMapUIInit()
{
	// DungeonMap Frame //
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

	allMapFrame->SetIsViewing(false);
}

void gameScene::InventoryUIInit()
{
	// Inventory Frame //
	UIFrame* InventoryFrame = new UIFrame();
	InventoryFrame->init("InventoryFrame", 1000, 170, IMAGEMANAGER->findImage("InventoryBase_2")->getWidth(), IMAGEMANAGER->findImage("InventoryBase_2")->getHeight(), "InventoryBase_2");
	UIMANAGER->GetGameFrame()->AddFrame(InventoryFrame);

	UIFrame* weaponImageFrame = new UIFrame();
	weaponImageFrame->init("curWeapon_1", 48, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame);

	UIFrame* weaponImageSubFrame = new UIFrame();
	weaponImageSubFrame->init("curWeaponSub_1", 114, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageSubFrame);

	UIFrame* weaponImageFrame2 = new UIFrame();
	weaponImageFrame2->init("curWeapon_2", 210, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageFrame2);

	UIFrame* weaponImageSubFrame2 = new UIFrame();
	weaponImageSubFrame2->init("curWeaponSub_2", 276, 105, 57, 57, "");
	InventoryFrame->AddFrame(weaponImageSubFrame2);

	int accesorySize = 4;
	for (int i = 0; i < accesorySize; i++)
	{
		UIFrame* accesory = new UIFrame();
		accesory->init("accesoryFrame_" + to_string(i), (i * (IMAGEMANAGER->findImage("accessory")->getWidth() + 8)) + 65 - (accesorySize - 4) * (IMAGEMANAGER->findImage("accessory")->getWidth() / 2 + 4)
			, 190, IMAGEMANAGER->findImage("accessory")->getWidth(), IMAGEMANAGER->findImage("accessory")->getHeight(), "accessory");
		InventoryFrame->AddFrame(accesory);

		UIFrame* itemImageFrame = new UIFrame();
		itemImageFrame->init("itemImageFrame", 0, 0, 57, 57, "");
		accesory->AddFrame(itemImageFrame);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			UIFrame* itemFrame = new UIFrame();
			itemFrame->init("itemFrame_" + to_string(i * 5 + j), (j * (IMAGEMANAGER->findImage("IconGray")->getWidth() + 8) + 32), 280 + (i * (IMAGEMANAGER->findImage("IconGray")->getHeight() + 8)), IMAGEMANAGER->findImage("IconGray")->getWidth(), IMAGEMANAGER->findImage("IconGray")->getHeight(), "IconGray");
			InventoryFrame->AddFrame(itemFrame);

			UIFrame* itemImageFrame = new UIFrame();
			itemImageFrame->init("itemImageFrame", 0, 0, 57, 57, "");
			itemFrame->AddFrame(itemImageFrame);
		}
	}

	UIText* moneyText = new UIText();
	moneyText->init("moneyText", 10, 502, 300, 100, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT, RGB(255, 255, 255));
	InventoryFrame->AddFrame(moneyText);

	InventoryFrame->SetIsViewing(false);


	UIText* accessFullText = new UIText();
	accessFullText->init("isFullText", 350, 200, 800, 200, "인벤토리 기능을 실행할 수 없습니다.", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(200, 30, 30));
	UIMANAGER->GetGameFrame()->AddFrame(accessFullText);
	accessFullText->SetIsViewing(false);

	UIText* accessEqualText = new UIText();
	accessEqualText->init("isEqualText", 350, 200, 800, 200, "같은 아이템은 장착할 수 없습니다.", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(200, 30, 30));
	UIMANAGER->GetGameFrame()->AddFrame(accessEqualText);
	accessEqualText->SetIsViewing(false);
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
	INPUT->update();

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

	if (INPUT->GetKeyDown('V'))
	{
		UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->ToggleIsViewing();
	}

	for (int i = 0; i < 13; i++)
	{
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->GetRect(), _ptMouse))
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(true);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("charNameText"))->SetText(_vCharName[i]);
			dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("CostumeBase_1")->GetChild("CharExplanationText"))->SetText(_CharExplanation[i]);
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
