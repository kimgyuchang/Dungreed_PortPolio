#include "stdafx.h"
#include "Restaurant.h"

HRESULT Restaurant::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

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
	_isOpen = false;
	_isNoMoney = false;
	_isFull = false;
	_count = 0;
	_speed = 0.6f;
	_x = -15;
	_y = -15;

	_mouseLocation = 0;
	_scrollTimer = 0;

	_hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL | ES_RIGHT, WINSIZEX / 2 - 95, WINSIZEY / 2, 200, 25, _hWnd, (HMENU)100, _hInstance, NULL);
	ShowWindow(_hEdit, SW_HIDE);

	return S_OK;
}

void Restaurant::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing())
	{
		Conversation();
	}

	if (_restaurantBase->GetIsViewing())
	{
		// 나가기
		if (_restaurantBase->GetChild("_exit")->GetIsViewing() && PtInRect(&_restaurantBase->GetChild("_exit")->GetRect(), _ptMouse))
		{
			if (INPUT->GetIsLButtonClicked())
			{
				_restaurantBase->SetIsViewing(false);
				_isActivating = false;
				_isOpen = false;
			}
		}


		// 각 FOOD 구매
		if (!_foodAlphaAnimOn && !_foodMoveAnimOn) // FOOD 알파 애니메이션이 꺼졌을때
		{
			UIImage* foodImg = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("_foodImg"));
			bool checkAnyoneCollided = false;
			for (int i = 0; i < _vFoods.size(); i++)
			{
				if (PtInRect(&_restaurantBase->GetChild("_wholeFoodFrame")->GetChild("_foodFrame" + to_string(i))->GetRect(), _ptMouse))
				{
					_restaurantBase->GetChild("_wholeFoodFrame")->GetChild("_foodFrame" + to_string(i))->SetImage(IMAGEMANAGER->findImage("RestaurantMenu_Withoutmoney_Selected"));
					foodImg->SetImage(_vFoods[i]->_img);
					foodImg->SetIsViewing(true);
					checkAnyoneCollided = true; // 하나라도 충돌하면 ON

					if (INPUT->GetIsLButtonClicked())
					{
						Food* food = _vFoods[i];
						this->BuyFood(food, i);
						break;
					}
				}

				else
				{
					_restaurantBase->GetChild("_wholeFoodFrame")->GetChild("_foodFrame" + to_string(i))->SetImage(IMAGEMANAGER->findImage("RestaurantMenu_Withoutmoney"));
				}
			}

			if (!checkAnyoneCollided)
			{
				foodImg->SetImage(nullptr);
				foodImg->SetIsViewing(false);
			}
		}

		else
		{
			if (_foodAlphaAnimOn) FoodAlphaAnim();
			if (_foodMoveAnimOn) MoveFood();
		}

		MoveUI();
	}
}

void Restaurant::MoveFood()
{
	UIImage* foodImg = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("_foodImg"));

	_x += _speed; // -15 
	_y += _speed; // -15 	
	foodImg->MoveFrameChild(_x, _y);

	if (_x > 0 || _y > 0)
	{
		_foodAlphaAnimOn = true;
		_foodMoveAnimOn = false;
	}
}

void Restaurant::FoodAlphaAnim()
{
	UIImage* foodImg = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("_foodImg"));
	foodImg->SetAlpha(foodImg->GetAlpha() - 5);

	if (foodImg->GetAlpha() < 0)
	{
		foodImg->SetAlpha(255);
		foodImg->SetIsViewing(false);
		_foodAlphaAnimOn = false;
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
			_isOpen = true;
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

	if (_isOpen)
	{
		_isOpen = false;
		this->Activate();
	}
}

void Restaurant::release()
{
	NPC::release();
}

void Restaurant::render(HDC hdc)
{
	NPC::render(hdc);
}

void Restaurant::Activate()
{
	ReNewUI();
	_isActivating = !_isActivating;
	_restaurantBase->ToggleIsViewing();
}

void Restaurant::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	_restaurantBase = UIMANAGER->GetGameFrame()->GetChild("_restaurantBase");
}

void Restaurant::SetRestaurantFood()
{
	int foodCount = RANDOM->range(3, 7);
	for (int i = 0; i < foodCount; i++)
	{
		FOODTYPE foodType = (FOODTYPE)RANDOM->range(FOODTYPE::F_END);

		Food* food = new Food();

		switch (foodType)
		{
		case F_PEASOUP:
			food->_name = "완두콩 스프";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.5f, 15.f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_EVADE);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 9.5f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 70;
			food->_satiation = RANDOM->range(48, 60);
			food->_img = IMAGEMANAGER->findImage("06_PeaSoup");
			food->_imgName = "06_PeaSoup";
			break;
		case F_HOTCHICKENSTEW:
			food->_name = "매운 치킨 스튜";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(5.f, 10.f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_EVADE);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 9.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 70 + food->_vStatusNum[2] * 60;
			food->_satiation = RANDOM->range(48, 67);
			food->_img = IMAGEMANAGER->findImage("11_HotChickenStew");
			food->_imgName = "11_HotChickenStew";
			break;
		case F_DELUXEBURGER:
			food->_name = "디럭스 버거";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(5.f, 10.f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 9.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 50 + food->_vStatusNum[2] * 60;
			food->_satiation = RANDOM->range(50, 67);
			food->_img = IMAGEMANAGER->findImage("09_DeluxeBurger");
			food->_imgName = "09_DeluxeBurger";
			break;
		case F_BREAD:
			food->_name = "빵";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 10.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 60;
			food->_satiation = RANDOM->range(48, 60);
			food->_img = IMAGEMANAGER->findImage("01_Bread");
			food->_imgName = "01_Bread";
			break;
		case F_FRIEDEEG:
			food->_name = "계란 프라이";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 13.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 50;
			food->_satiation = RANDOM->range(48, 55);
			food->_img = IMAGEMANAGER->findImage("02_FriedEgg");
			food->_imgName = "02_FriedEgg";
			break;
		case F_GRILLEDMUSHROOM:
			food->_name = "구운 버섯";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIPER);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 10.f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 12.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 50 + food->_vStatusNum[2] * 50;
			food->_satiation = RANDOM->range(50, 64);
			food->_img = IMAGEMANAGER->findImage("03_GrilledMushroom");
			food->_imgName = "03_GrilledMushroom";
			break;
		case F_TOMATOSOUP:
			food->_name = "토마토 수프";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 12.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 50;
			food->_satiation = RANDOM->range(48, 58);
			food->_img = IMAGEMANAGER->findImage("04_TamatoSoup");
			food->_imgName = "04_TamatoSoup";
			break;
		case F_ONIONSOUP:
			food->_name = "양파 수프";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 12.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 50;
			food->_satiation = RANDOM->range(48, 60);
			food->_img = IMAGEMANAGER->findImage("05_OnionSoup");
			food->_imgName = "05_OnionSoup";
			break;
		case F_VEGETABLESOUP:
			food->_name = "야채 살사 수프";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 12.f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 60 + food->_vStatusNum[1] * 50;
			food->_satiation = RANDOM->range(55, 67);
			food->_img = IMAGEMANAGER->findImage("07_VegetableSalsaSoup");
			food->_imgName = "07_VegetableSalsaSoup";
			break;
		case F_LEMONADE:
			food->_name = "레몬 에이드";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CHARGESPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(40, 55);
			food->_img = IMAGEMANAGER->findImage("08_Lemonade");
			food->_imgName = "08_Lemonade";
			break;
		case F_CHOCOLATECOOKIE: // 특수 특성 - (골드 획득 시 4 골드 추가 획득) : 추후 수정필요!
			food->_name = "초콜릿 쿠키";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 20.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("10_ChocolateCookie");
			food->_imgName = "10_ChocolateCookie";
			break;
		case F_RASPBERRYCOOKIE:
			food->_name = "라즈베리 쿠키";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ATKSPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("12_RaspberryCookie");
			food->_imgName = "12_RaspberryCookie";
			break;
		case F_GRIFFONEGG:
			food->_name = "그리핀 알 오믈렛";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXDASH);
			food->_vStatusNum.push_back(1);
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 50;
			food->_satiation = RANDOM->range(40, 50);
			food->_img = IMAGEMANAGER->findImage("13_GriffonEggOmelette");
			food->_imgName = "13_GriffonEggOmelette";
			break;
		case F_GARLICMEATBALL:
			food->_name = "양파 소스 미트볼";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(20);
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(5);
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(5);
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_EVADE);
			food->_vStatusNum.push_back(5);
			food->_price = food->_vHealPer[0] * 50 + 1100;
			food->_satiation = RANDOM->range(50, 67);
			food->_img = IMAGEMANAGER->findImage("14_GarlicMeatball");
			food->_imgName = "14_GarlicMeatball";
			break;
		case F_BIBIMBAP: // // 특수 특성 - (액세서리 슬롯 1개 추가, 약간의 위력 & 최대 체력) : 추후 수정필요!
			food->_name = "비빔밥";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 11.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 40;
			food->_satiation = RANDOM->range(60, 67);
			food->_img = IMAGEMANAGER->findImage("15_Bibimbap");
			food->_imgName = "15_Bibimbap";
			break;
		case F_MINOTAURS: // 특수 특성 - (쓰러지면 절반의 HP로 부활) : 추후 수정필요!
			food->_name = "미노타우르스 스테이크";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 15.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(55, 60);
			food->_img = IMAGEMANAGER->findImage("16_MinotaursSteak");
			food->_imgName = "16_MinotaursSteak";
			break;
		case F_COOKEDMEAT:
			food->_name = "특제 고기 요리";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_STRONG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 3.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 100;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("17_SpecialtyCookedMeat");
			food->_imgName = "17_SpecialtyCookedMeat";
			break;
		case F_STRAWBERRYPIE:
			food->_name = "딸기 파이";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(6.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_FIXEDDMG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 3.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 100;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("18_StrawberryPie");
			food->_imgName = "18_StrawberryPie";
			break;
		case F_SEASONINGBIRD:
			food->_name = "양념된 작은 새";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(7.0f, 11.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(6.0f, 9.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 14.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 60 + food->_vStatusNum[2] * 50;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("19_SeasoningSmallBird");
			food->_imgName = "19_SeasoningSmallBird";
			break;
		case F_BEER: // 특수 특성 - (무기 스왑 시 무기 스왑 시 10s동안 위력 50 증가 (재사용 대기시간 35s) & 위력) : 추후 수정필요!
			food->_name = "맥주";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 15.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("20_Beer");
			food->_imgName = "20_Beer";
			break;
		case F_PIZZA:
			food->_name = "콤비네이션 피자";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ATKSPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 45.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(55, 65);
			food->_img = IMAGEMANAGER->findImage("21_CombinationPizza");
			food->_imgName = "21_CombinationPizza";
			break;
		case F_SALMON: // 특수 특성 - (새로운 방으로 이동 시 포만감 - 1) : 추후 수정필요!
			food->_name = "훈제 연어";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_SATIATION);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 30.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 100;
			food->_satiation = RANDOM->range(46, 55);
			food->_img = IMAGEMANAGER->findImage("22_SmokedSalmon");
			food->_imgName = "22_SmokedSalmon";
			break;
		case F_SHRIMP:
			food->_name = "새우 튀김";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_STRONG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 2.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_FIXEDDMG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 2.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 11.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_EVADE);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_BLOCK);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 6.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 60 + food->_vStatusNum[1] * 50 + food->_vStatusNum[2] * 100 + food->_vStatusNum[3] * 100
				+ food->_vStatusNum[4] * 40 + food->_vStatusNum[5] * 60 + food->_vStatusNum[6] * 60;
			food->_satiation = RANDOM->range(60, 68);
			food->_img = IMAGEMANAGER->findImage("23_FriedShrimp");
			food->_imgName = "23_FriedShrimp";
			break;
		case F_EEL:
			food->_name = "장어 구이";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 45.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("24_GrilledEel");
			food->_imgName = "24_GrilledEel";
			break;
		case F_ROLL:
			food->_name = "시나몬 롤";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MOVESPEED);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 10.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ATKSPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CHARGESPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40 + food->_vStatusNum[1] * 40 + food->_vStatusNum[2] * 40;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("25_CinnamonRoll");
			food->_imgName = "25_CinnamonRoll";
			break;
		case F_SPARKLING:
			food->_name = "탄산수";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_SATIATION);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 30.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 100;
			food->_img = IMAGEMANAGER->findImage("26_SparklingWater");
			food->_satiation = 0;
			food->_imgName = "26_SparklingWater";
			break;
		case F_SWEETMEATBALL:
			food->_name = "단짠 미트볼";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(18.0f, 28.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 60;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("97_SweetMeatball");
			food->_imgName = "97_SweetMeatball";
			break;
		case F_HOTMEATBALL:
			food->_name = "매운 소스 미트볼";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(18.0f, 28.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(48, 58);
			food->_img = IMAGEMANAGER->findImage("98_HotMeatball");
			food->_imgName = "98_HotMeatball";
			break;
		default:
			break;
		}

		_vFoods.push_back(food);
	}
}

void Restaurant::BuyFood(Food* food, int index)
{
	Player* p = ENTITYMANAGER->getPlayer();

	if (food->_price > p->GetMoney())
	{
		UIMANAGER->GetGameFrame()->GetChild("noMoney")->SetViewingTimer(30);
	}

	else if (p->GetMaxSatiety() < p->GetSatiety() + food->_satiation)
	{
		UIMANAGER->GetGameFrame()->GetChild("full")->SetViewingTimer(30);
	}

	else
	{
		p->SetMoney(p->GetMoney() - food->_price);
		p->SetSatiety(p->GetSatiety() + food->_satiation);

		for (int i = 0; i < food->_vStatusType.size(); i++)
		{
			FOODSTATUSTYPE type = food->_vStatusType[i];

			switch (type)
			{
			case FST_POWER: {
				int newPower = p->GetPower() + food->_vStatusNum[i];
				p->SetPower(newPower);
				break;
			}
			case FST_DEF: {
				int newDef = p->GetDefence() + food->_vStatusNum[i];
				p->SetDefence(newDef);
				break;
			}
			case FST_EVADE: {
				int newEvade = p->GetEvasion() + food->_vStatusNum[i];
				p->SetEvasion(newEvade);
				break;
			}
			case FST_CRIPER: {
				int newCriPer = p->GetCriPer() * food->_vStatusNum[i] + p->GetCriPer();
				p->SetCriPer(newCriPer);
				break;
			}
			case FST_CRIDMG: {
				int newCriDmg = p->GetCriDamage() + food->_vStatusNum[i];
				p->SetCriDamage(newCriDmg);
				break;
			}
			case FST_MAXHP: {
				int newMaxHP = p->GetMaxHp() * food->_vStatusNum[i] + p->GetMaxHp();
				p->SetMaxHp(newMaxHP);
				break;
			}
			case FST_MAXDASH: {
				int newMaxDash = p->GetMaxDashCount() + food->_vStatusNum[i];
				p->SetMaxDashCount(newMaxDash);
				break;
			}
			case FST_FIXEDDMG: {
				int newFixedDMG = p->GetTrueDamage() + food->_vStatusNum[i];
				p->SetTrueDamage(newFixedDMG);
				break;
			}
			case FST_ATKSPEED: {
				int newAtkSpeed = p->GetAtkSpeed() + food->_vStatusNum[i] * p->GetAtkSpeed();
				p->SetAtkSpeed(newAtkSpeed);
				break;
			}
			case FST_CHARGESPEED: {
				int newChargeSpeed = p->GetReloadSpeed() + food->_vStatusNum[i] * p->GetReloadSpeed();
				p->SetReloadSpeed(newChargeSpeed);
				break;
			}
			case FST_MAXACCSLOT: {
				break;
			}
			case FST_STRONG: {
				int newStrong = p->GetToughness() + food->_vStatusNum[i];
				p->SetToughness(newStrong);
				break;
			}
			case FST_SATIATION: {
				int newSatiation = p->GetSatiety() - food->_vStatusNum[i];
				p->SetSatiety(newSatiation);
				break;
			}
			case FST_BLOCK: {
				int newBlock = p->GetBlock() + food->_vStatusNum[i];
				p->SetBlock(newBlock);
				break;
			}
			case FST_MOVESPEED: {
				int newMoveSpeed = p->GetMoveSpeed() + p->GetMoveSpeed() * food->_vStatusNum[i];
				p->SetMoveSpeed(newMoveSpeed);
				break;
			}
			default:
				break;
			}
		}
		for (int i = 0; i < food->_vHeal.size(); i++)
		{
			FOODHEAL _vHeal = food->_vHeal[i];
			switch (_vHeal)
			{
			case F_HEAL: {
				int newHp = p->GetInitHp() * food->_vHealPer[i] + p->GetHP();
				if (newHp > p->GetInitHp()) newHp = p->GetInitHp();
				p->SetHp(newHp);
				break;
			}
			default:
				break;
			}
		}

		_foodMoveAnimOn = true;
		UIMANAGER->GetGameFrame()->GetChild("_foodImg")->MoveFrameChild(170, 170);
		_vFoods.erase(_vFoods.begin() + index);
	}

	this->ReNewUI();
}


void Restaurant::ReNewUI()
{
	_restaurantBase->GetVChildFrames().clear();

	UIImage* _restaurantFoodBase = new UIImage();
	_restaurantFoodBase->init("_restaurantFoodBase", WINSIZEX / 2 - 100, 150, 1719, 390, "RestaurantTable", true, 0, 0, 1.4f, 1.4f);
	_restaurantBase->AddFrame(_restaurantFoodBase);

	UIFrame* _restaurantLabel = new UIFrame();
	_restaurantLabel->init("_restaurantLabel", 0, 0, 960, 96, "Label", 1.5f, 1.5f);
	_restaurantBase->AddFrame(_restaurantLabel);

	UIFrame* _wholeFoodFrame = new UIFrame();
	_wholeFoodFrame->init("_wholeFoodFrame", 50, 150, 333, 396, "Base_0", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_wholeFoodFrame);

	UIFrame* _exit = new UIFrame();
	_exit->init("_exit", WINSIZEX - 120, 30, 92, 79, "Xbutton");
	_restaurantBase->AddFrame(_exit);

	UIFrame* _satiation = new UIFrame();
	_satiation->init("_satiation", 50, WINSIZEY - 85, 333, 51, "restaurantSatiation", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_satiation);

	UIFrame* _foodIcon = new UIFrame();
	_foodIcon->init("_foodIcon", 75, WINSIZEY - 77, 51, 42, "FoodIcon", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_foodIcon);

	UIFrame* _money = new UIFrame();
	_money->init("_money", WINSIZEX - 300, WINSIZEY - 90, 200, 51, "restaurantMoney", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_money);

	UIText* moneyText = new UIText();
	moneyText->init("moneyText", 100, 18, 120, 30, to_string(ENTITYMANAGER->getPlayer()->GetMoney()), FONT::PIX, WORDSIZE::WS_BIG);
	_money->AddFrame(moneyText);

	UIText* satiationText = new UIText();
	satiationText->init("satiationText", -250, 18, 500, 30, to_string(ENTITYMANAGER->getPlayer()->GetSatiety()), FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
	_satiation->AddFrame(satiationText);
	UIText* slash = new UIText();
	slash->init("slash", 280, 18, 500, 90, "/", FONT::PIX, WORDSIZE::WS_BIG);
	_satiation->AddFrame(slash);
	UIText* maxSatiationText = new UIText();
	maxSatiationText->init("maxSatiationText", 330, 18, 500, 30, to_string(ENTITYMANAGER->getPlayer()->GetMaxSatiety()), FONT::PIX, WORDSIZE::WS_BIG);
	_satiation->AddFrame(maxSatiationText);

	for (int i = 0; i < _vFoods.size(); i++)
	{
		UIFrame* _foodFrame = new UIFrame();
		_foodFrame->init("_foodFrame" + to_string(i), 18, 20 + i * 165, 431, 160, "RestaurantMenu_Withoutmoney");
		_wholeFoodFrame->AddFrame(_foodFrame);
		_foodFrame->SetUseOutsideLimit(true);

		for (int j = 0; j < _vFoods[i]->_vStatusType.size(); j++)
		{
			UIText* foodName = new UIText();
			foodName->init("foodName", 10, 10, 500, 30, _vFoods[i]->_name, FONT::PIX, WORDSIZE::WS_MIDDLE);
			_foodFrame->AddFrame(foodName);

			UIText* foodHeal = new UIText();
			foodHeal->init("foodHeal", -115, 60, 500, 500, (to_string((int)_vFoods[i]->_vHealPer[0])),
				FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_RIGHT);
			_foodFrame->AddFrame(foodHeal);

			UIText* per = new UIText();
			per->init("per", -100, 60, 500, 500, " %", FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_RIGHT);
			_foodFrame->AddFrame(per);

			UIFrame* life = new UIFrame();
			life->init("life", 400, 60, 17, 14, "Fairy", 1.5f, 1.5f);
			_foodFrame->AddFrame(life);

			UIText* foodSatiation = new UIText();
			foodSatiation->init("foodSatiation", -100, 90, 500, 500, (to_string(_vFoods[i]->_satiation)),
				FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_RIGHT, RGB(0, 255, 0));
			_foodFrame->AddFrame(foodSatiation);

			UIFrame* gogi = new UIFrame();
			gogi->init("gogi", 400, 90, 17, 14, "Food", 1.5f, 1.5f);
			_foodFrame->AddFrame(gogi);

			UIText* foodPrice = new UIText();
			foodPrice->init("foodPrice", -100, 120, 500, 500, to_string(_vFoods[i]->_price),
				FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_RIGHT);
			_foodFrame->AddFrame(foodPrice);

			UIFrame* coin = new UIFrame();
			coin->init("coin", 400, 117, 17, 14, "Coin", 1.3f, 1.3f);
			_foodFrame->AddFrame(coin);

			UIText* triangle = new UIText();
			triangle->init("triangle", 10, 60 + j * 30, 500, 500, "▶ + ", FONT::PIX, WORDSIZE::WS_MIDDLESMALL);
			_foodFrame->AddFrame(triangle);

			UIText* foodStatNum = new UIText();
			foodStatNum->init("foodStatNum", 60, 60 + j * 30, 500, 500, to_string((int)_vFoods[i]->_vStatusNum[j]),
				FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_LEFT, RGB(0, 255, 0));
			_foodFrame->AddFrame(foodStatNum);

			string typetext;
			FOODSTATUSTYPE type = _vFoods[i]->_vStatusType[j];
			switch (type)
			{
			case FST_POWER:
				typetext = "위력";
				break;
			case FST_DEF:
				typetext = "방어력";
				break;
			case FST_EVADE:
				typetext = "회피";
				break;
			case FST_CRIPER:
				typetext = "크리티컬 확률";
				break;
			case FST_CRIDMG:
				typetext = "크리티컬 데미지";
				break;
			case FST_MAXHP:
				typetext = "최대체력";
				break;
			default:
				break;
			}
			UIText* foodStatType = new UIText();
			foodStatType->init("foodStatType", 100, 60 + j * 30, 500, 500, typetext, FONT::PIX, WORDSIZE::WS_MIDDLE);
			_foodFrame->AddFrame(foodStatType);
		}
	}
}

void Restaurant::MoveUI()
{
	if (PtInRect(&_restaurantBase->GetChild("_wholeFoodFrame")->GetRect(), _ptMouse) && INPUT->GetKey(VK_LBUTTON))
	{
		_scrollTimer++;
		if (_scrollTimer == 1)
		{
			_mouseLocation = _ptMouse.y;
		}

		else if (_scrollTimer > 1)
		{
			for (int i = 0; i < _vFoods.size(); i++)
			{
				_restaurantBase->GetChild("_wholeFoodFrame")->GetChild("_foodFrame" + to_string(i))->MoveFrameChild(0, _ptMouse.y - _mouseLocation);
			}
			_mouseLocation = _ptMouse.y;
		}
	}

	if (INPUT->GetIsLButtonUp())
	{
		_scrollTimer = 0;
		_mouseLocation = 0;
	}
}