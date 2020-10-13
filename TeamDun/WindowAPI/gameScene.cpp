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
	_scrollTimer = 0;
	_mouseLocation = 0;

	InitWardrobeString();
	CAMERAMANAGER->init(0, 0, 15000, 15000, -300, -300, WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void gameScene::InitWardrobeString()
{
	_vCharName = vector<string>{ "모험가", "판금의 용사", "석양의 총잡이", "앨리스", "홍련", "이키나곰",
								 "라이더 H", "범죄자 실루엣", "곡괭이의 왕", "뚱뚱보", "마검사", "인간 라슬리", "마스터 셰프" };
	_CharExplanation = vector<string>{ "던전은 탐사하기 위해 온 초보 모험가","판금 갑옷을 두른, 든든한 용사","황야를 가로지르는 외로운 총잡이",
									   "토끼는 보이지 않고, 멋진 표적이 가득해!","저 너머로...개화하고 싶지 않은가, 그대?","시..시..시니컬이라구! 흥!",
									   "뼈를 깎더라도,\n어디에서든 달리고 싶다.","범행 동기도 가지각색.\n범행 물품도 천차만별.","세상을 지배할 뻔한 살아있는 전설",
									   "잘 달리지는 못하지만,\n 휘두르는 건 무척 잘할거에요.","부활이 꼭 재생을 의미하는 것은 아니듯이.",
									   "마검에 사로잡히기 전 그의 모습이다.","우주 어딘가 유명한 레스토랑의 주방장. 총 쏘는 솜씨도 일품이라고 한다." };
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
	_CharFirstStat = vector<string>{ "","▶ +10 방어력","▶ -15 최대 체력","▶ -30 최대 체력","▶ -15 최대 체력","▶ -20 위력","▶ +22% 이동속도","","▶ +1 대쉬 횟수","▶ -20% 이동속도","","","▶ 조준 정확도 +33" };
	_CharSecondStat = vector<string>{ "","▶ -10 최대 체력","▶ -15 방어력","▶ +40 위력","▶ -5 회피","▶ -5 방어력","▶ -2 강인함","▶ -12 회피","▶ -25 크리티컬","▶ -10% 공격속도","","","▶ +33 최대 체력" };

}

void gameScene::initUI()
{
	DungeonMapUIInit();
	WardrobeUIInit();
	InventoryUIInit();
	CharUIInit();
	ShopUIInit();
}

void gameScene::WardrobeUIInit()
{
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
	fasto->init("fasto", 75, 185, IMAGEMANAGER->findImage("fasto")->getWidth(), IMAGEMANAGER->findImage("fasto")->getHeight(), "fasto");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(9))->AddFrame(fasto);

	UIFrame* horseman = new UIFrame();
	horseman->init("horseman", 75, 175, IMAGEMANAGER->findImage("horseman")->getWidth(), IMAGEMANAGER->findImage("horseman")->getHeight(), "horseman");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(10))->AddFrame(horseman);

	UIFrame* humanlasley = new UIFrame();
	humanlasley->init("humanlasley", 75, 180, IMAGEMANAGER->findImage("humanlasley")->getWidth(), IMAGEMANAGER->findImage("humanlasley")->getHeight(), "humanlasley");
	warDrobeFrame->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(11))->AddFrame(humanlasley);

	UIFrame* masterchef = new UIFrame();
	masterchef->init("masterchef", 70, 170, IMAGEMANAGER->findImage("masterchef")->getWidth(), IMAGEMANAGER->findImage("masterchef")->getHeight(), "masterchef");
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

	UIText* CharFirstStat = new UIText();
	CharFirstStat->init("CharFirstStat", 550, 200, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharFirstStat);

	UIText* CharSecondStat = new UIText();
	CharSecondStat->init("CharSecondStat", 550, 250, 1000, 50, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	costumeExplanationFrame->AddFrame(CharSecondStat);

}

void gameScene::DungeonMapUIInit()
{
	// DungeonMap Frame //
	UIImage* allMapFrame = new UIImage();
	allMapFrame->init("allMapFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 6, 6, 80);
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
	InventoryFrame->SetUseOutsideLimit(false);
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
	moneyText->init("moneyText", 5, 505, 300, 100, "0", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_RIGHT, RGB(255, 255, 255));
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


	/////////// TOOLTIP /////////////

	UIImage* uiToolTip = new UIImage();
	uiToolTip->init("itemToolTip", 0, 0, 400, 500, "ToolTipCover", false, 0, 0, 4.0f, 5.0f, 130);
	uiToolTip->SetUseOutsideLimit(false);
	InventoryFrame->AddFrame(uiToolTip);

}

void gameScene::ShopUIInit()
{
	UIFrame* shopBase = new UIFrame();
	shopBase->init("DungeonShopBase", 0, 100, IMAGEMANAGER->findImage("DungeonShopBase")->getWidth(), IMAGEMANAGER->findImage("DungeonShopBase")->getHeight(), "DungeonShopBase");
	UIMANAGER->GetGameFrame()->AddFrame(shopBase);

	UIFrame* checkSell = new UIFrame();
	checkSell->init("CheckSell", WINSIZEX / 2 - IMAGEMANAGER->findImage("BaseType2")->getWidth() / 2 * 1.5f, WINSIZEY / 2 - IMAGEMANAGER->findImage("BaseType2")->getHeight() / 2, IMAGEMANAGER->findImage("BaseType2")->getWidth(), IMAGEMANAGER->findImage("BaseType2")->getHeight(), "BaseType2", 1.5f, 1.0f);
	UIMANAGER->GetGameFrame()->AddFrame(checkSell);

	UIText* checkText = new UIText();
	checkText->init("text", 20, 15, 300, 200, "", FONT::PIX, WORDSIZE::WS_MIDDLE);
	checkSell->AddFrame(checkText);

	UIFrame* checkOK = new UIFrame();
	checkOK->init("yes", 110, 138, 113, 45, "YesOrNo", 0.9f, 0.9f);
	checkSell->AddFrame(checkOK);

	UIText* YES = new UIText();
	YES->init("text", 0, 10, 113 * 0.9f, 30, "예", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE);
	checkOK->AddFrame(YES);

	UIFrame* checkNo = new UIFrame();
	checkNo->init("no", 215, 138, 113, 45, "YesOrNo", 0.9f, 0.9f);
	checkSell->AddFrame(checkNo);

	UIText* NO = new UIText();
	NO->init("text", 0, 10, 113 * 0.9f, 30, "아니오", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE);
	checkNo->AddFrame(NO);

	checkSell->SetIsViewing(false);
	shopBase->SetIsViewing(false);
}

void gameScene::CharUIInit()
{
	UIFrame* charFrame = new UIFrame();
	charFrame->init("charFrame", 50, 250, IMAGEMANAGER->findImage("Base")->getWidth() * 2.0f, IMAGEMANAGER->findImage("Base")->getHeight() * 2.0f, "Base", 2.0f, 2.0f);
	UIMANAGER->GetGameFrame()->AddFrame(charFrame);

	UIText* statusText = new UIText();
	statusText->init("statusText", 80, 20, 300, 100, "STATUS", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE);
	charFrame->AddFrame(statusText);

	UIFrame* powerImg = new UIFrame();
	powerImg->init("powerImg", 20, 60, 63, 63, "Stat_Power", 0.8f, 0.8f);
	charFrame->AddFrame(powerImg);

	UIText* powerText = new UIText();
	powerText->init("powerText", 80, 77, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(powerText);

	UIFrame* defImg = new UIFrame();
	defImg->init("defImg", 20, 120, 63, 63, "Stat_Def", 0.8f, 0.8f);
	charFrame->AddFrame(defImg);

	UIText* defText = new UIText();
	defText->init("defText", 80, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(defText);

	UIFrame* toughImg = new UIFrame();
	toughImg->init("toughImg", 125, 120, 63, 63, "Stat_Tough", 0.8f, 0.8f);
	charFrame->AddFrame(toughImg);

	UIText* toughText = new UIText();
	toughText->init("toughText", 185, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(toughText);

	UIFrame* blockImg = new UIFrame();
	blockImg->init("blockImg", 230, 120, 63, 63, "Stat_Block", 0.8f, 0.8f);
	charFrame->AddFrame(blockImg);

	UIText* blockText = new UIText();
	blockText->init("blockText", 290, 137, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(blockText);

	UIFrame* criImg = new UIFrame();
	criImg->init("criImg", 20, 180, 63, 63, "Stat_Critical", 0.8f, 0.8f);
	charFrame->AddFrame(criImg);

	UIText* criText = new UIText();
	criText->init("criText", 80, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(criText);

	UIFrame* criDmgImg = new UIFrame();
	criDmgImg->init("criDmgImg", 125, 180, 63, 63, "Stat_CriticalDmg", 0.8f, 0.8f);
	charFrame->AddFrame(criDmgImg);

	UIText* criDmgText = new UIText();
	criDmgText->init("criDmgText", 185, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(criDmgText);

	UIFrame* evadeImg = new UIFrame();
	evadeImg->init("evadeImg", 230, 180, 63, 63, "Stat_Evade", 0.8f, 0.8f);
	charFrame->AddFrame(evadeImg);

	UIText* evadeText = new UIText();
	evadeText->init("evadeText", 290, 197, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(evadeText);

	UIFrame* moveSpeedImg = new UIFrame();
	moveSpeedImg->init("moveSpeedImg", 20, 240, 63, 63, "Stat_MoveSpeed", 0.8f, 0.8f);
	charFrame->AddFrame(moveSpeedImg);

	UIText* moveSpeedText = new UIText();
	moveSpeedText->init("moveSpeedText", 80, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(moveSpeedText);

	UIFrame* atkSpeedImg = new UIFrame();
	atkSpeedImg->init("atkSpeedImg", 125, 240, 63, 63, "Stat_AtkSpeed", 0.8f, 0.8f);
	charFrame->AddFrame(atkSpeedImg);

	UIText* atkSpeedText = new UIText();
	atkSpeedText->init("atkSpeedText", 185, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(atkSpeedText);

	UIFrame* reloadImg = new UIFrame();
	reloadImg->init("reloadImg", 230, 240, 63, 63, "Stat_Reload", 0.8f, 0.8f);
	charFrame->AddFrame(reloadImg);

	UIText* reloadText = new UIText();
	reloadText->init("reloadText", 290, 257, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(reloadText);

	UIFrame* dashImg = new UIFrame();
	dashImg->init("dashImg", 20, 300, 63, 63, "Stat_Dash", 0.8f, 0.8f);
	charFrame->AddFrame(dashImg);

	UIText* dashText = new UIText();
	dashText->init("dashText", 80, 317, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(dashText);

	UIFrame* trueDamageImg = new UIFrame();
	trueDamageImg->init("trueDamageImg", 125, 300, 63, 63, "Stat_TrueDamage", 0.8f, 0.8f);
	charFrame->AddFrame(trueDamageImg);

	UIText* trueDamageText = new UIText();
	trueDamageText->init("trueDamageText", 185, 317, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(trueDamageText);

	UIFrame* burnImg = new UIFrame();
	burnImg->init("burnImg", 335, 120, 51, 51, "Stat_Burn", 0.8f, 0.8f);
	charFrame->AddFrame(burnImg);

	UIText* burnText = new UIText();
	burnText->init("burnText", 387, 132, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(burnText);

	UIFrame* poisonImg = new UIFrame();
	poisonImg->init("poisonImg", 335, 170, 51, 51, "Stat_Poison", 0.8f, 0.8f);
	charFrame->AddFrame(poisonImg);

	UIText* poisonText = new UIText();
	poisonText->init("poisonText", 387, 182, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(poisonText);

	UIFrame* coldImg = new UIFrame();
	coldImg->init("coldImg", 335, 220, 51, 51, "Stat_Cold", 0.8f, 0.8f);
	charFrame->AddFrame(coldImg);

	UIText* coldText = new UIText();
	coldText->init("coldText", 387, 232, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(coldText);

	UIFrame* elecImg = new UIFrame();
	elecImg->init("elecImg", 335, 270, 51, 51, "Stat_Shock", 0.8f, 0.8f);
	charFrame->AddFrame(elecImg);

	UIText* elecText = new UIText();
	elecText->init("elecText", 387, 282, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(elecText);

	UIFrame* stunImg = new UIFrame();
	stunImg->init("stunImg", 335, 320, 51, 51, "Stat_Stun", 0.8f, 0.8f);
	charFrame->AddFrame(stunImg);

	UIText* stunText = new UIText();
	stunText->init("stunText", 387, 332, 120, 50, "0", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT);
	charFrame->AddFrame(stunText);

	UIImage* tooltipFrame = new UIImage();
	tooltipFrame->init("toolTipFrame", 0, 0, 50, 50, "ToolTipCover", false, 0, 0, 1.0f, 1.0f, 80);
	charFrame->AddFrame(tooltipFrame);

	UIText* tooltipTitle = new UIText();
	tooltipTitle->init("title", 10, 10, 270, 120, "", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_LEFT, RGB(255, 238, 184));
	tooltipFrame->AddFrame(tooltipTitle);

	UIText* tooltipDiscript = new UIText();
	tooltipDiscript->init("discription", 10, 60, 270, 150, "", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
	tooltipFrame->AddFrame(tooltipDiscript);

	UIText* tooltipGray = new UIText();
	tooltipGray->init("additional", 10, 130, 270, 150, "", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(170, 170, 170));
	tooltipFrame->AddFrame(tooltipGray);

	charFrame->SetIsViewing(false);
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

void gameScene::UpdateWardrobeUI()
{

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
		if (_scrollTimer == 1)
		{
			_mouseLocation = _ptMouse.x;
		}

		else if (_scrollTimer > 1)
		{
			for (int i = 0; i < 13; i++)
			{
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeBack" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
				UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeUnlocked" + to_string(i))->MoveFrameChild(_ptMouse.x - _mouseLocation, 0);
			}
			_mouseLocation = _ptMouse.x;
		}
	}

	if (INPUT->GetIsLButtonUp())
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

	UpdateWardrobeUI();

	if (INPUT->GetKeyDown('V'))
	{
		UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->ToggleIsViewing();
	}

	if (INPUT->GetKeyDown('C'))
	{
		UIMANAGER->GetGameFrame()->GetChild("charFrame")->ToggleIsViewing();
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

