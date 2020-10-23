#include "stdafx.h"
#include "Restaurant.h"

HRESULT Restaurant::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "È£·¹¸®Ä«";
	_vConvTexts = vector<string>
	{
		"¿À´ÃÀº ¾î¶² ¿ä¸®¸¦ µå½Ã·¯ ¿À¼Ì³ª¿ä?",
		"°­ÇÑ ÈûÀÌ ¾Æ´Ï´õ¶óµµ, Á¦ ¿ä¸®°¡ ´©±º°¡¸¦ ±¸¿øÇÒ ¼ö ÀÖÀ»°Å¶ó°í ¹Ï¾î¿ä."
	};
	_vSelectTexts = vector<string>
	{
		"À½½ÄÁ¡",
		"¾Æ¹«°Íµµ"
	};

	_useConv = true;
	_useSelect = true;
	_isOpen = false;

	for (int i = 0; i < _vFoods.size(); i++)
	{
		_vFoods[i]->_isSoldOut = false;
	}

	_count = 0;
	_speed = 0.64f;
	_x = -15;
	_y = -15;

	_mouseLocation = 0;
	_scrollTimer = 0;

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
		if (INPUT->GetKeyDown(VK_F8))
		{
			SetRestaurantFood();
			ReNewUI();
		}

		SetSatiationUI();
		SetHpUI();

		// ³ª°¡±â
		if (_restaurantBase->GetChild("_exit")->GetIsViewing() && PtInRect(&_restaurantBase->GetChild("_exit")->GetRect(), _ptMouse))
		{
			if (INPUT->GetIsLButtonClicked())
			{
				_restaurantBase->SetIsViewing(false);
				UIMANAGER->GetGameFrame()->GetChild("_foodImg")->SetIsViewing(false);
				_isActivating = false;
				_isOpen = false;
			}
		}
		// °¢ FOOD ±¸¸Å
		if (!_foodAlphaAnimOn && !_foodMoveAnimOn) // FOOD ¾ËÆÄ ¾Ö´Ï¸ÞÀÌ¼ÇÀÌ ²¨Á³À»¶§
		{
			UIImage* foodImg = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("_foodImg"));
			bool checkAnyoneCollided = false;
			for (int i = 0; i < _vFoods.size(); i++)
			{
				if (PtInRect(&_restaurantBase->GetChild("_foodFrame" + to_string(i))->GetRect(), _ptMouse))
				{
					_restaurantBase->GetChild("_foodFrame" + to_string(i))->SetImage(IMAGEMANAGER->findImage("RestaurantMenu_Withoutmoney_Selected"));
					if (!_vFoods[i]->_isSoldOut) {
						foodImg->SetImage(_vFoods[i]->_img);
						foodImg->SetIsViewing(true);
					}
					else
					{
						foodImg->SetImage(nullptr);
					}
					checkAnyoneCollided = true; // ÇÏ³ª¶óµµ Ãæµ¹ÇÏ¸é ON

					if (INPUT->GetIsRButtonClicked())
					{
						Food* food = _vFoods[i];
						this->BuyFood(food, i);
						break;
					}
				}
				else
				{
					_restaurantBase->GetChild("_foodFrame" + to_string(i))->SetImage(IMAGEMANAGER->findImage("RestaurantMenu_Withoutmoney"));
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
		_x = -15;
		_y = -15;
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
		foodImg->SetAlpha(150);
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
	UIMANAGER->GetGameFrame()->GetChild("_foodImg")->SetIsViewing(false);
}

void Restaurant::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	_restaurantBase = UIMANAGER->GetGameFrame()->GetChild("_restaurantBase");
	_foodImg = UIMANAGER->GetGameFrame()->GetChild("_foodImg");
}

void Restaurant::SetRestaurantFood()
{
	_vFoods.clear();

	int foodCount = RANDOM->range(3, 7);
	for (int i = 0; i < foodCount; i++)
	{
		FOODTYPE foodType = (FOODTYPE)RANDOM->range(FOODTYPE::F_END);

		Food* food = new Food();

		switch (foodType)
		{
		case F_PEASOUP:
			food->_name = "¿ÏµÎÄá ½ºÇÁ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_È£·Ï";
			break;
		case F_HOTCHICKENSTEW:
			food->_name = "¸Å¿î Ä¡Å² ½ºÆ©";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_ÈÄ·è";
			break;
		case F_DELUXEBURGER:
			food->_name = "µð·°½º ¹ö°Å";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_BREAD:
			food->_name = "»§";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_FRIEDEEG:
			food->_name = "°è¶õ ÇÁ¶óÀÌ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_GRILLEDMUSHROOM:
			food->_name = "±¸¿î ¹ö¼¸";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_TOMATOSOUP:
			food->_name = "Åä¸¶Åä ¼öÇÁ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_È£·Ï";
			break;
		case F_ONIONSOUP:
			food->_name = "¾çÆÄ ¼öÇÁ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_È£·Ï";
			break;
		case F_VEGETABLESOUP:
			food->_name = "¾ßÃ¤ »ì»ç ¼öÇÁ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_È£·Ï";
			break;
		case F_LEMONADE:
			food->_name = "·¹¸ó ¿¡ÀÌµå";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CHARGESPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(40, 55);
			food->_img = IMAGEMANAGER->findImage("08_Lemonade");
			food->_imgName = "08_Lemonade";
			food->_soundName = "NPC_·¹½ºÅä¶û_²Ü²©";
			break;
		case F_CHOCOLATECOOKIE: // Æ¯¼ö Æ¯¼º - (°ñµå È¹µæ ½Ã 4 °ñµå Ãß°¡ È¹µæ) : ÃßÈÄ ¼öÁ¤ÇÊ¿ä!
			food->_name = "ÃÊÄÝ¸´ ÄíÅ°";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 20.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("10_ChocolateCookie");
			food->_imgName = "10_ChocolateCookie";
			food->_soundName = "NPC_·¹½ºÅä¶û_±îÀñ";
			break;
		case F_RASPBERRYCOOKIE:
			food->_name = "¶óÁîº£¸® ÄíÅ°";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ATKSPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 40.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("12_RaspberryCookie");
			food->_imgName = "12_RaspberryCookie";
			food->_soundName = "NPC_·¹½ºÅä¶û_±îÀñ";
			break;
		case F_GRIFFONEGG:
			food->_name = "±×¸®ÇÉ ¾Ë ¿À¹É·¿";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXDASH);
			food->_vStatusNum.push_back(1);
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 50;
			food->_satiation = RANDOM->range(40, 50);
			food->_img = IMAGEMANAGER->findImage("13_GriffonEggOmelette");
			food->_imgName = "13_GriffonEggOmelette";
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_GARLICMEATBALL:
			food->_name = "¾çÆÄ ¼Ò½º ¹ÌÆ®º¼";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_BIBIMBAP:
			food->_name = "ºñºö¹ä";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(5.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(8.0f, 11.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXACCSLOT);
			food->_vStatusNum.push_back(1);
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30 + food->_vStatusNum[1] * 40;
			food->_satiation = RANDOM->range(60, 67);
			food->_img = IMAGEMANAGER->findImage("15_Bibimbap");
			food->_imgName = "15_Bibimbap";
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_MINOTAURS: // Æ¯¼ö Æ¯¼º - (¾²·¯Áö¸é Àý¹ÝÀÇ HP·Î ºÎÈ°) : ÃßÈÄ ¼öÁ¤ÇÊ¿ä!
			food->_name = "¹Ì³ëÅ¸¿ì¸£½º ½ºÅ×ÀÌÅ©";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 15.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(55, 60);
			food->_img = IMAGEMANAGER->findImage("16_MinotaursSteak");
			food->_imgName = "16_MinotaursSteak";
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_COOKEDMEAT:
			food->_name = "Æ¯Á¦ °í±â ¿ä¸®";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_STRONG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 3.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 100;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("17_SpecialtyCookedMeat");
			food->_imgName = "17_SpecialtyCookedMeat";
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_STRAWBERRYPIE:
			food->_name = "µþ±â ÆÄÀÌ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_¿ÍÀÛ";
			break;
		case F_SEASONINGBIRD:
			food->_name = "¾ç³äµÈ ÀÛÀº »õ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_BEER: // Æ¯¼ö Æ¯¼º - (¹«±â ½º¿Ò ½Ã ¹«±â ½º¿Ò ½Ã 10sµ¿¾È À§·Â 50 Áõ°¡ (Àç»ç¿ë ´ë±â½Ã°£ 35s) & À§·Â) : ÃßÈÄ ¼öÁ¤ÇÊ¿ä!
			food->_name = "¸ÆÁÖ";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 15.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(57, 67);
			food->_img = IMAGEMANAGER->findImage("20_Beer");
			food->_imgName = "20_Beer";
			food->_soundName = "NPC_·¹½ºÅä¶û_²Ü²©";
			break;
		case F_PIZZA:
			food->_name = "ÄÞºñ³×ÀÌ¼Ç ÇÇÀÚ";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ATKSPEED);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 45.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(55, 65);
			food->_img = IMAGEMANAGER->findImage("21_CombinationPizza");
			food->_imgName = "21_CombinationPizza";
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_SALMON:
			food->_name = "ÈÆÁ¦ ¿¬¾î";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_ROOMSATIATION);
			food->_vStatusNum.push_back(1);
			food->_price = food->_vHealPer[0] * 50 + 1000;
			food->_satiation = RANDOM->range(55,68);
			food->_img = IMAGEMANAGER->findImage("22_SmokedSalmon");
			food->_imgName = "22_SmokedSalmon";
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_SHRIMP:
			food->_name = "»õ¿ì Æ¢±è";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_DEF);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_STRONG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 2.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_FIXEDDMG);
			food->_vStatusNum.push_back(RANDOM->range(1.0f, 2.0f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(4.0f, 8.0f));
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
			food->_soundName = "NPC_·¹½ºÅä¶û_±îÀñ";
			break;
		case F_EEL:
			food->_name = "Àå¾î ±¸ÀÌ";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_MAXHP);
			food->_vStatusNum.push_back(RANDOM->range(20.0f, 45.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 40;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("24_GrilledEel");
			food->_imgName = "24_GrilledEel";
			food->_soundName = "NPC_·¹½ºÅä¶û_­h";
			break;
		case F_ROLL:
			food->_name = "½Ã³ª¸ó ·Ñ";
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
			food->_soundName = "NPC_·¹½ºÅä¶û_¿ÍÀÛ";
			break;
		case F_SPARKLING:
			food->_name = "Åº»ê¼ö";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(0);
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_SATIATION);
			food->_vStatusNum.push_back(RANDOM->range(10.0f, 30.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 100;
			food->_img = IMAGEMANAGER->findImage("26_SparklingWater");
			food->_satiation = 0;
			food->_imgName = "26_SparklingWater";
			food->_soundName = "NPC_·¹½ºÅä¶û_²Ü²©";
			break;
		case F_SWEETMEATBALL:
			food->_name = "´ÜÂ§ ¹ÌÆ®º¼";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_CRIDMG);
			food->_vStatusNum.push_back(RANDOM->range(18.0f, 28.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 60;
			food->_satiation = RANDOM->range(50, 60);
			food->_img = IMAGEMANAGER->findImage("97_SweetMeatball");
			food->_imgName = "97_SweetMeatball";
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		case F_HOTMEATBALL:
			food->_name = "¸Å¿î ¼Ò½º ¹ÌÆ®º¼";
			food->_vHeal.push_back(FOODHEAL::F_HEAL);
			food->_vHealPer.push_back(RANDOM->range(5.0f, 12.5f));
			food->_vStatusType.push_back(FOODSTATUSTYPE::FST_POWER);
			food->_vStatusNum.push_back(RANDOM->range(18.0f, 28.0f));
			food->_price = food->_vHealPer[0] * 50 + food->_vStatusNum[0] * 30;
			food->_satiation = RANDOM->range(48, 58);
			food->_img = IMAGEMANAGER->findImage("98_HotMeatball");
			food->_imgName = "98_HotMeatball";
			food->_soundName = "NPC_·¹½ºÅä¶û_Äí½¹";
			break;
		default:
			break;
		}

		_vFoods.push_back(food);
	}
}

void Restaurant::SetSatiationUI()
{
	dynamic_cast<UIProgressBar*>(_restaurantBase->GetChild("realSatiation"))->FillCheck(ENTITYMANAGER->getPlayer()->GetMaxSatiety(), ENTITYMANAGER->getPlayer()->GetSatiety());
}

void Restaurant::SetHpUI()
{
}

void Restaurant::BuyFood(Food* food, int index)
{
	Player* p = ENTITYMANAGER->getPlayer();

	float foodSatiety = (p->GetSpecialAbilityOn(4, 2) ? (food->_satiation * 0.9f) : food->_satiation);
	if (food->_price > p->GetMoney())
	{
		UIMANAGER->GetGameFrame()->GetChild("noMoney")->SetViewingTimer(30);
	}
	else if (p->GetMaxSatiety() < p->GetSatiety() + foodSatiety)
	{
		UIMANAGER->GetGameFrame()->GetChild("full")->SetViewingTimer(30);
	}
	else if (food->_isSoldOut) {}
	else
	{
		UIImage* foodImg = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("_foodImg"));
		foodImg->SetAlpha(255);

		p->SetMoney(p->GetMoney() - food->_price);
		p->SetSatiety(p->GetSatiety() + foodSatiety);

		for (int i = 0; i < food->_vStatusType.size(); i++)
		{
			FOODSTATUSTYPE type = food->_vStatusType[i];

			switch (type)
			{
			case FST_POWER: {
				int newPower = p->GetPower() + food->_vStatusNum[i];
				p->SetPower(newPower);
				p->SetFoodPower(p->GetFoodPower() + food->_vStatusNum[i]);
				break;
			}
			case FST_DEF: {
				int newDef = p->GetDefence() + food->_vStatusNum[i];
				p->SetDefence(newDef);
				p->SetFoodDef(p->GetFoodDef() + food->_vStatusNum[i]);
				break;
			}
			case FST_EVADE: {
				int newEvade = p->GetEvasion() + food->_vStatusNum[i];
				p->SetEvasion(newEvade);
				p->SetFoodEvade(p->GetFoodEvade() + food->_vStatusNum[i]);
				break;
			}
			case FST_CRIPER: {
				int newCriPer = p->GetCriPer() + food->_vStatusNum[i];
				p->SetCriPer(newCriPer);
				p->SetFoodCriPer(p->GetFoodCriPer() + food->_vStatusNum[i]);
				break;
			}
			case FST_CRIDMG: {
				int newCriDmg = p->GetCriDamage() + food->_vStatusNum[i];
				p->SetCriDamage(newCriDmg);
				p->SetFoodCriDmg(p->GetFoodCriDmg() + food->_vStatusNum[i]);
				break;
			}
			case FST_MAXHP: {
				int newMaxHP = p->GetInitHp() + food->_vStatusNum[i];
				p->SetInitHp(newMaxHP);
				p->SetNewMaxHp();
				p->SetFoodInitHp(p->GetFoodInitHp() + food->_vStatusNum[i]);
				break;
			}
			case FST_MAXDASH: {
				p->AddMaxDash();
				p->SetFoodMaxDash(p->GetFoodMaxDash() + 1);
				break;
			}
			case FST_FIXEDDMG: {
				int newFixedDMG = p->GetTrueDamage() + food->_vStatusNum[i];
				p->SetTrueDamage(newFixedDMG);
				p->SetFoodTrueDamage(p->GetFoodTrueDamage() + food->_vStatusNum[i]);
				break;
			}
			case FST_ATKSPEED: {
				float newAtkSpeed = p->GetAtkSpeedPer() + food->_vStatusNum[i];
				p->SetAtkSpeedPer(newAtkSpeed);
				p->SetFoodAtkSpeedPer(p->GetFoodAtkSpeedPer() + food->_vStatusNum[i]);
				break;
			}
			case FST_CHARGESPEED: {
				int newChargeSpeed = p->GetReloadSpeed() + food->_vStatusNum[i];
				p->SetReloadSpeed(newChargeSpeed);
				p->SetFoodReloadSpeed(p->GetFoodReloadSpeed() + food->_vStatusNum[i]);
				break;
			}
			case FST_MAXACCSLOT: {
				p->SetAccesoryCount(p->GetAccesoryCount() + 1);
				p->SetFoodAccsCount(p->GetFoodAccsCount() + 1);
				p->GetInventory()->SetInventoryAccesoryUI(); 
				p->GetInventory()->ReloadUIImages();
				break;
			}
			case FST_STRONG: {
				int newStrong = p->GetToughness() + food->_vStatusNum[i];
				p->SetToughness(newStrong);
				p->SetFoodToughness(p->GetFoodToughness() + food->_vStatusNum[i]);
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
				p->SetFoodBlock(p->GetFoodBlock() + food->_vStatusNum[i]);
				break;
			}
			case FST_MOVESPEED: {
				float newMoveSpeed = p->GetMoveSpeed() + (p->GetMoveSpeed() * (food->_vStatusNum[i] / 100));
				p->SetMoveSpeed(newMoveSpeed);
				p->SetFoodMoveSpeed(p->GetFoodMoveSpeed() + food->_vStatusNum[i]);
				break;
			}
			case FST_ROOMSATIATION: {
				p->SetRoomMoveSatiation(p->GetRoomMoveSatiation() + 1);
				p->SetFoodRoomMoveSatiation(p->GetFoodRoomMoveSatiation() + 1);
				break;
			}
			default:
				break;
			}
			if (p->GetSatiety() < 0) p->SetSatiety(0);
		}
		for (int i = 0; i < food->_vHeal.size(); i++)
		{
			FOODHEAL _vHeal = food->_vHeal[i];
			switch (_vHeal)
			{
			case F_HEAL: {
				int newHp = p->GetMaxHp() * food->_vHealPer[i] + p->GetHP();
				if (newHp > p->GetMaxHp()) newHp = p->GetMaxHp();
				p->SetHp(newHp);
				break;
			}
			default:
				break;
			}
		}
		food->_isSoldOut = true;
		_foodMoveAnimOn = true;
		UIMANAGER->GetGameFrame()->GetChild("_foodImg")->MoveFrameChild(170, 170);
		SOUNDMANAGER->play(food->_soundName);
	}

	this->ReNewUI();
}


void Restaurant::ReNewUI()
{
	_restaurantBase->GetVChildFrames().clear();

	for (int i = 0; i < _vFoods.size(); i++)
	{
		UIFrame* _foodFrame = new UIFrame();
		_foodFrame->init("_foodFrame" + to_string(i), 18, 15 + i * 165, 431, 160, "RestaurantMenu_Withoutmoney");
		_restaurantBase->AddFrame(_foodFrame);

		if (_vFoods[i]->_isSoldOut)
		{
			_restaurantBase->GetChild("_foodFrame" + to_string(i))->GetVChildFrames().clear();
			_restaurantBase->GetChild("_foodFrame" + to_string(i))->SetImage(IMAGEMANAGER->findImage("RestaurantMenu_Withoutmoney"));

			UIFrame* ThankYou = new UIFrame();
			ThankYou->init("ThankYou", 45, 45, 297, 57, "ThankYou.korean", 1.2f, 1.2f);
			_restaurantBase->GetChild("_foodFrame" + to_string(i))->AddFrame(ThankYou);
		}

		else
		{
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
				foodSatiation->init("foodSatiation", -100, 90, 500, 500, (to_string_with_precision((ENTITYMANAGER->getPlayer()->GetSpecialAbilityOn(4, 2) ? _vFoods[i]->_satiation * 0.9f : _vFoods[i]->_satiation),0)),
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

				string typetext;
				FOODSTATUSTYPE type = _vFoods[i]->_vStatusType[j];
				switch (type)
				{
				case FST_POWER:
					typetext = "À§·Â";
					break;
				case FST_DEF:
					typetext = "¹æ¾î·Â";
					break;
				case FST_EVADE:
					typetext = "È¸ÇÇ";
					break;
				case FST_CRIPER:
					typetext = "Å©¸®Æ¼ÄÃ È®·ü";
					break;
				case FST_CRIDMG:
					typetext = "Å©¸®Æ¼ÄÃ µ¥¹ÌÁö";
					break;
				case FST_MAXHP:
					typetext = "ÃÖ´ë Ã¼·Â";
					break;
				case FST_MAXDASH:
					typetext = "´ë½¬ È½¼ö";
					break;
				case FST_FIXEDDMG:
					typetext = "°íÁ¤ µ¥¹ÌÁö";
					break;
				case FST_ATKSPEED:
					typetext = "% °ø°Ý ¼Óµµ";
					break;
				case FST_CHARGESPEED:
					typetext = "% ÀçÀåÀü ¼Óµµ";
					break;
				case FST_MAXACCSLOT:
					typetext = "¾Ç¼¼»ç¸® ½½·Ô";
					break;
				case FST_STRONG:
					typetext = "°­ÀÎÇÔ";
					break;
				case FST_SATIATION:
					typetext = "Æ÷¸¸°¨ °¨¼Ò";
					break;
				case FST_BLOCK:
					typetext = "¸·±â";
					break;
				case FST_MOVESPEED:
					typetext = "% ÀÌµ¿ ¼Óµµ";
					break;
				case FST_ROOMSATIATION:
					typetext = "¹æ ÀÌµ¿½Ã Æ÷¸¸°¨ °¨¼Ò";
				default:
					break;
				}
				if (j < 4)
				{
					UIText* triangle = new UIText();
					triangle->init("triangle", 10, 50 + j * 25, 500, 160, "¢º + ", FONT::PIX, WORDSIZE::WS_SMALL);
					_foodFrame->AddFrame(triangle);

					UIText* foodStatNum = new UIText();
					foodStatNum->init("foodStatNum", 50, 50 + j * 25, 500, 160, to_string((int)_vFoods[i]->_vStatusNum[j]),
						FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(0, 255, 0));
					_foodFrame->AddFrame(foodStatNum);

					UIText* foodStatType = new UIText();
					foodStatType->init("foodStatType", 75, 50 + j * 25, 500, 500, typetext, FONT::PIX, WORDSIZE::WS_MIDDLESMALL);
					_foodFrame->AddFrame(foodStatType);
				}
				else if (j >= 4) // »õ¿ìÆ¢±è¿ë
				{
					UIText* triangle = new UIText();
					triangle->init("triangle", 200, 50 + (j - 4) * 25, 500, 160, "¢º + ", FONT::PIX, WORDSIZE::WS_SMALL);
					_foodFrame->AddFrame(triangle);

					UIText* foodStatNum = new UIText();
					foodStatNum->init("foodStatNum", 240, 50 + (j - 4) * 25, 500, 160, to_string((int)_vFoods[i]->_vStatusNum[j]),
						FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(0, 255, 0));
					_foodFrame->AddFrame(foodStatNum);

					UIText* foodStatType = new UIText();
					foodStatType->init("foodStatType", 260, 50 + (j - 4) * 25, 500, 500, typetext, FONT::PIX, WORDSIZE::WS_MIDDLESMALL);
					_foodFrame->AddFrame(foodStatType);
				}
			}
		}
	}


	UIFrame* _wholeFoodFrame = new UIFrame();
	_wholeFoodFrame->init("_wholeFoodFrame", -50, -150, WINSIZEX, WINSIZEY, "baseFrame");
	_restaurantBase->AddFrame(_wholeFoodFrame);

	UIImage* _restaurantFoodBase = new UIImage();
	_restaurantFoodBase->init("_restaurantFoodBase", WINSIZEX / 2 - 150, 0, 1719, 390, "RestaurantTable", true, 0, 0, 1.4f, 1.4f);
	_restaurantBase->AddFrame(_restaurantFoodBase);

	UIFrame* _restaurantLabel = new UIFrame();
	_restaurantLabel->init("_restaurantLabel", -50, -150, 960, 96, "Label", 1.5f, 1.5f);
	_restaurantBase->AddFrame(_restaurantLabel);

	UIFrame* _exit = new UIFrame();
	_exit->init("_exit", WINSIZEX - 170, -120, 92, 79, "Xbutton");
	_restaurantBase->AddFrame(_exit);

	UIProgressBar* realSatiation = new UIProgressBar();
	realSatiation->init("realSatiation", 118, WINSIZEY - 220, 1, 33, "SatiationProgressBar", "");
	_restaurantBase->AddFrame(realSatiation);

	UIFrame* _satiation = new UIFrame();
	_satiation->init("_satiation", 0, WINSIZEY - 235, 333, 51, "Base_1", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_satiation);

	UIFrame* _foodIcon = new UIFrame();
	_foodIcon->init("_foodIcon", 25, WINSIZEY - 227, 51, 42, "FoodIcon", 1.4f, 1.4f);
	_restaurantBase->AddFrame(_foodIcon);

	UIFrame* _money = new UIFrame();
	_money->init("_money", WINSIZEX - 350, WINSIZEY - 235, 200, 51, "restaurantMoney", 1.4f, 1.4f);
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
				_restaurantBase->GetChild("_foodFrame" + to_string(i))->MoveFrameChild(0, _ptMouse.y - _mouseLocation);
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