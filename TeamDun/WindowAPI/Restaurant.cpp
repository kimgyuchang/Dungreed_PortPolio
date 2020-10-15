#include "stdafx.h"
#include "Restaurant.h"

HRESULT Restaurant::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_exitRect = RectMake(WINSIZEX - 120, 30, 66 * 1.4, 57 * 1.4);

	_npcName = "호레리카";
	_vConvTexts = vector<string>
	{
		"오늘은 어떤 요리를 드시러 오셨나요?"
	};
	_vSelectTexts = vector<string>
	{
		"음식점",
		"아무것도"
	};

	_useConv = true;
	_useSelect = true;

	return S_OK;
}

void Restaurant::update()
{
	NPC::update();

	if (_selectFrame->GetIsViewing())
	{
		Conversation();
	}
}

void Restaurant::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);

			this->Activate();
		}
	}
	else _selectFrame->GetChild("selected1")->SetImage(nullptr);

	if (PtInRect(&_selectFrame->GetChild("selected2")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected2")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
		}
	}
	else _selectFrame->GetChild("selected2")->SetImage(nullptr);
}

void Restaurant::release()
{
	NPC::release();
}

void Restaurant::render(HDC hdc)
{
	NPC::render(hdc);
	CAMERAMANAGER->Rectangle(hdc, _exitRect);
}

void Restaurant::Activate()
{
	NPC::Activate();
	ReNewUI();
}

void Restaurant::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	//_restaurantBase = UIMANAGER->GetGameFrame()->GetChild("ScreenCover");
	//_restaurantLabel = UIMANAGER->GetGameFrame()->GetChild("Label");
	//_restaurantFoodBase = UIMANAGER->GetGameFrame()->GetChild("RestaurantTable");
	//_wholeFoodFrame = UIMANAGER->GetGameFrame()->GetChild("Base_0");
	//_foodFrameSelected = UIMANAGER->GetGameFrame()->GetChild("RestaurantMenu_Withoutmoney_Selected");
	//_exit = UIMANAGER->GetGameFrame()->GetChild("Xbutton");
	//_satiation = UIMANAGER->GetGameFrame()->GetChild("restaurantSatiation");
}

void Restaurant::SetRestaurantFood()
{
	//_vFoodName = vector<string>{ "계란 프라이", "구운 버섯", "디럭스 버거", "매운 소스 미트볼", "매운 치킨 스튜", "빵", "야채 살사 수프", "양념된 작은 새",
	//	"양파 수프", "완두콩 수프", "토마토수프", "그리핀 알 오믈렛", "딸기 파이", "라즈베리 쿠키", "레몬에이드", "맥주", "미노타우루스 스테이크", "비빔밥", 
	//	"새우 튀김" "시나몬 롤", "양파 소스 미트볼", "장어 구이", "초콜릿 쿠키", "콤비네이션 피자", "특제 고기 요리", "훈제 연어", "탄산수" };

	//_vFoodFirstStat = vector<string>{ "▶ +7 위력","▶ +12 크리티컬 데미지","▶ +15 위력","▶ +27 위력","▶ +11 위력","▶ +8 위력","▶ +12 위력","",
	//	"▶ +7 위력","▶ +8 위력", "▶ +10 위력","▶ +13 위력","▶ +1 대쉬 횟수", "▶ +3 고정 데미지", "▶ +33% 공격 속도", "▶ +33% 재장전 속도",
	//	"▶ 무기 스왑 시 10s 동안 위력 50 증가 (재사용 대기시간 35s)", "▶ 쓰러지면 절반의 HP로 부활", "▶ 액세서리 슬롯 1개 추가", "▶ +7 방어력",
	//	"▶ +20% 이동 속도", "▶ +20 위력", "▶ +30 최대 체력", "▶ 골드 획득 시마다 추가로 4 골드를 더 획득", "▶ +45% 크리티컬 데미지",
	//	"▶ +3 강인함", "▶ 새로운 방으로 이동할 때마다 줄어드는 포만감 +1", "▶ -20 포만감 감소" };

	//_vFoodSecondStat = vector<string>{ "▶ +11 최대 체력","▶ +10 크리티컬 데미지","▶ +12 최대 체력", " ","▶ +13 방어력","▶ +10 방어력","▶ +12 최대 체력",
	//	"▶ +12 방어력", "▶ +9% 최대 체력","▶ +7 회피","▶ +9 크리티컬"," ", "▶ +7 위력", " ", " ", "▶ +7 위력", " ", "▶ +7 위력", "▶ +11 크리티컬", 
	//	"▶ +12% 공격 속도", "▶ +5 방어력" , " ", "▶ +7 위력" , " ", " ", " ", " " };

	//_vFoodThirdStat = vector<string>{ " ","▶ +8 크리티컬","▶ +6 방어력"," ","▶ +7 회피"," ","▶ +12 크리티컬","▶ +12 크리티컬", " "," "," "," ", " "," ",
	//	" "," "," ","▶ +7 최대 체력", "▶ +2 강인함, +2 고정 데미지" , "▶ +12% 재장전 속도", "▶ +5 크리티컬, +5 회피", " ", " ", " ", " ", " ", " " };

	_vFoodName = vector<string>{ "완두콩 수프", "매운 치킨 스튜", "디럭스 버거" };
	_vFoodFirstStat = vector<string>{ "▶ +12 위력", "▶ +10 위력", "▶ +15 위력" };
	_vFoodSecondStat = vector<string>{ "▶ +5 회피", "▶ +3 방어력", "▶ +7 최대 체력" };
	_vFoodThirdStat = vector<string>{ "", "▶ +5 회피", "▶ +5 방어력" };

	_vFoodHeal = vector<string>{ "12%", "12%", "12%" };
	_vFoodSatiation = vector<string>{ "59", "58", "64" };
	_vFoodPrice = vector<string>{ "550", "610", "610" };
}

void Restaurant::BuyFood()
{
	ENTITYMANAGER->getPlayer()->GetMoney();

	switch (_food)
	{
	case F_SOUP:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 550);
		break;
	case F_STEW:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 610);
		break;
	case F_BURGER:
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - 610);
		break;
	default:
		break;
	}
}

void Restaurant::ReNewUI()
{
	UIImage* _restaurantBase = new UIImage();
	_restaurantBase->init("restaurantBase", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", true, 0, 0, 10.0f, 10.0f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantBase);

	UIImage* _restaurantLabel = new UIImage();
	_restaurantLabel->init("restaurantLabel", 0, 0, 960, 96, "Label", true, 0, 0, 1.5f, 1.5f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantLabel);

	UIImage* _restaurantFoodBase = new UIImage();
	_restaurantFoodBase->init("restaurantFoodBase", WINSIZEX / 2 - 100, 150, 1719, 390, "RestaurantTable", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_restaurantFoodBase);

	UIImage* _wholeFoodFrame = new UIImage();
	_wholeFoodFrame->init("wholeFoodFrame", 50, 150, 333, 396, "Base_0", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_wholeFoodFrame);

	UIImage* _exit = new UIImage();
	_exit->init("wholeFoodFrame", WINSIZEX - 120, 30, 66, 57, "Xbutton", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_exit);

	UIImage* _satiation = new UIImage();
	_satiation->init("satiation", 50, WINSIZEY - 85, 333, 51, "restaurantSatiation", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_satiation);

	UIImage* _foodIcon = new UIImage();
	_foodIcon->init("foodIcon", 75, WINSIZEY - 77, 51, 42, "FoodIcon", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_foodIcon);

	UIImage* _money = new UIImage();
	_money->init("money", WINSIZEX - 300, WINSIZEY - 90, 200, 51, "restaurantMoney", true, 0, 0, 1.4f, 1.4f);
	UIMANAGER->GetGameFrame()->AddFrame(_money);

	UIText* moneyText = new UIText();
	moneyText->init("moneyText", WINSIZEX - 220, WINSIZEY - 72, 120, 30, "10000", FONT::PIX, WORDSIZE::WS_BIG);
	UIMANAGER->GetGameFrame()->AddFrame(moneyText);

	UIText* satiationText = new UIText();
	satiationText->init("satiationText", 250, WINSIZEY - 68, 500, 30, " 0 / 150 ", FONT::PIX, WORDSIZE::WS_BIG);
	UIMANAGER->GetGameFrame()->AddFrame(satiationText);

	for (int i = 0; i < 3; i++)
	{
		UIImage* _foodFrame = new UIImage();
		_foodFrame->init("foodFrame", 68, 170 + i * 165, 297, 114, "RestaurantMenu_Withoutmoney", true, 0, 0, 1.45f, 1.4f);
		UIMANAGER->GetGameFrame()->AddFrame(_foodFrame);
	}
}