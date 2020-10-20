#include "stdafx.h"
#include "Shop.h"
#include "inventory.h"

HRESULT Shop::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_npcName = "크록";
	_vConvTexts = vector<string>{
		"물건 판다. 많이 준비해놨다.",
		"반갑다. 좋은 것들 가져왔다.",
		"많이 벌어서 가게 차릴거다."
	};

	_vSelectTexts = vector<string>{
		"상점",
		"아무것도"
	};

	_useConv = true;
	_useSelect = true;

	return S_OK;
}

void Shop::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			Activate();
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

void Shop::update()
{
	NPC::update();

	if (_selectFrame->GetIsViewing())
	{
		Conversation();
	}

	if (_shopBase->GetIsViewing())
	{
		if (_checkSellFrame->GetIsViewing())
		{
			CheckToSell();
		}
		else
		{
			BuyItem();
			if (_invenFrame->GetIsViewing()) SellItem();
		}
	}
}

void Shop::release()
{
	NPC::release();
}

void Shop::render(HDC hdc)
{
	NPC::render(hdc);
}

void Shop::Animation()
{
	NPC::Animation();
}

/// <summary>
/// DATAMANAGER에서 불러온 후 init 가능한 것들만 init한다.
/// </summary>
void Shop::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");

	_inven = ENTITYMANAGER->getPlayer()->GetInventory();
	_shopBase = UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase");
	_invenFrame = UIMANAGER->GetGameFrame()->GetChild("InventoryFrame");
	_checkSellFrame = UIMANAGER->GetGameFrame()->GetChild("CheckSell");
}

/// <summary>
/// 초기화시 Shop에 진열할 아이템들을 선택하고, 필요 변수들을 지정한다.
/// </summary>
void Shop::SetShopItem()
{
	_curToolTipItem = nullptr;
	_toolTipFinalY = 0;
	_toolTipIndex = 0;

	int itemSize = RANDOM->range(4, 6);
	for (int i = 0; i < itemSize; i++)
	{
		_vItemList.push_back(DATAMANAGER->GetItemById(RANDOM->range(DATAMANAGER->GetItemMinId(), DATAMANAGER->GetItemMaxId())));
	}
}

/// <summary>
/// 초기화 혹은 아이템 구매시 새롭게 UI를 재배치
/// </summary>
void Shop::ReNewUI()
{
	_shopBase->GetVChildFrames().clear(); // Frame 내부를 정리한 후

	for (int i = 0; i < _vItemList.size(); i++) // 각 아이템을 추가한다
	{
		Item* item = _vItemList[i];

		int nameR = 255, nameG = 255, nameB = 255;
		switch (item->GetItemClass())
		{
		case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
		case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
		case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
		case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
		}
		UIFrame* shopItem = new UIFrame();
		shopItem->init("ShopItem" + to_string(i), 20, 100 + i * IMAGEMANAGER->findImage("ShopItem")->getHeight(), IMAGEMANAGER->findImage("ShopItem")->getWidth(), IMAGEMANAGER->findImage("ShopItem")->getHeight(), "ShopItem");
		_shopBase->AddFrame(shopItem);

		UIFrame* itemImageFrame = new UIFrame();
		itemImageFrame->init("itemImageFrame", 0, 10, 57, 57, item->GetInvenImageName());
		shopItem->AddFrame(itemImageFrame);

		UIText* itemName = new UIText();
		itemName->init("itemName", 75, 12, 500, 50, item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_LEFT, RGB(nameR, nameG, nameB));
		shopItem->AddFrame(itemName);

		UIText* itemPrice = new UIText();
		itemPrice->init("itemPrice", 81, 41, 200, 40, to_string(item->GetBuyPrice()), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_RIGHT);
		shopItem->AddFrame(itemPrice);
	}

	UIImage* uiToolTip = new UIImage();
	uiToolTip->init("itemToolTip", 0, 0, 400, 500, "ToolTipCover", false, 0, 0, 4.0f, 5.0f, 130);
	_shopBase->AddFrame(uiToolTip);
	
	uiToolTip->SetIsViewing(false);
}

/// <summary>
/// 인벤토리에서 조작이 들어가 아이템을 판매할 수 있도록 만듬
/// </summary>
void Shop::SellItem()
{
	if (INPUT->GetIsRButtonClicked())
	{
		for (int i = 0; i < _inven->GetVItemList().size(); i++)
		{
			Item* item = _inven->GetVItemList()[i];
			if (PtInRect(&_invenFrame->GetChild("itemFrame_" + to_string(i))->GetRect(), _ptMouse))
			{
				_checkSellFrame->SetIsViewing(true);
				_selectedItem = item;
				_index = i;
				RenewCheckUI();
				break;
			}
		}
	}
}

/// <summary>
/// 체크 프레임의 텍스트를 변경
/// </summary>
void Shop::RenewCheckUI()
{
	dynamic_cast<UIText*>(_checkSellFrame->GetChild("text"))->SetText(_selectedItem->GetName() + "을(를) 판매하시겠습니까?\n(가격 : " + to_string(_selectedItem->GetSellPrice()) + "G)");
}

/// <summary>
/// 체크 화면이 떳을때, 입력을 받아 판매하거나 돌아갈 수 있게함
/// </summary>
void Shop::CheckToSell()
{
	if (INPUT->GetIsLButtonClicked()) // 버튼 클릭
	{
		if (PtInRect(&_checkSellFrame->GetChild("yes")->GetRect(), _ptMouse))
		{
			ActivateSell();
		}

		else if (PtInRect(&_checkSellFrame->GetChild("no")->GetRect(), _ptMouse))
		{
			_selectedItem = nullptr;
			_index = 0;
			_checkSellFrame->SetIsViewing(false);
		}
	}

	else if (INPUT->GetKeyDown(VK_RETURN)) // 엔터
	{
		ActivateSell();
	}
}

/// <summary>
/// 판매하는 알고리즘
/// </summary>
void Shop::ActivateSell()
{
	SOUNDMANAGER->play("NPC_상점판매");
	ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() + _selectedItem->GetSellPrice());
	_inven->GetVItemList().erase(_inven->GetVItemList().begin() + _index);
	_inven->ReloadUIImages();

	_selectedItem = nullptr;
	_index = 0;
	_checkSellFrame->SetIsViewing(false);
}

/// <summary>
/// 우클릭을 통해 조건에 맞는다면 아이템을 사도록 함
/// </summary>
void Shop::BuyItem()
{
	UIImage* uiToolTip = dynamic_cast<UIImage*>(UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase")->GetChild("itemToolTip"));

	Item* item = nullptr;
	for (int i = 0; i < _vItemList.size(); i++)
	{
		if (PtInRect(&_shopBase->GetChild("ShopItem" + to_string(i))->GetRect(), _ptMouse))
		{
			item = _vItemList[i];
			_toolTipIndex = i;
			if (INPUT->GetIsRButtonClicked())
			{
				if (ENTITYMANAGER->getPlayer()->GetMoney() >= _vItemList[i]->GetBuyPrice()) // 돈이 충분
				{
					if (_inven->AddItem(_vItemList[i]) == true) // 넣는대에 성공하면
					{
						SOUNDMANAGER->play("NPC_상점판매");
						ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() - _vItemList[i]->GetBuyPrice());
						_vItemList.erase(_vItemList.begin() + i);
						ReNewUI();
					}
				}
			}
			break;
		}
	}

	if (item != nullptr)
	{
		uiToolTip->MoveFrameChild((_ptMouse.x) - uiToolTip->GetX(), (_ptMouse.y + (_toolTipIndex > 2 ? -_toolTipFinalY : 0) ) - uiToolTip->GetY());
		uiToolTip->SetIsViewing(true);
		
		if(item != _curToolTipItem)	InitToolTipItem(item);
	}

	else
	{
		uiToolTip->SetIsViewing(false);
	}
}

/// <summary>
/// Shop의 UI를 OnOff함
/// </summary>
void Shop::Activate()
{
	ReNewUI();
	_isActivating = !_isActivating;
	_shopBase->ToggleIsViewing();
	UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->SetIsViewing(_shopBase->GetIsViewing());
	_checkSellFrame->SetIsViewing(false);
}

/// <summary>
/// Inventory의 Tooltip과 같음. Shop용 ToolTip
/// </summary>
void Shop::InitToolTipItem(Item* item)
{
	_curToolTipItem = item;

	UIImage* uiToolTip = dynamic_cast<UIImage*>(_shopBase->GetChild("itemToolTip"));
	uiToolTip->GetVChildFrames().clear();

	// 이름 색
	int nameR = 255, nameG = 255, nameB = 255;
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
	case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
	case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
	case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
	}

	// 이름
	UIText* itemName = new UIText();
	itemName->init("itemName", 0, 10, 400, 200, item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(nameR, nameG, nameB));
	uiToolTip->AddFrame(itemName);

	// 이미지 프레임
	UIFrame* imgFrame = new UIFrame();
	imgFrame->init("imgFrame", 10, 50, IMAGEMANAGER->findImage("IconWhite")->getWidth(), IMAGEMANAGER->findImage("IconWhite")->getHeight(), "IconWhite");
	uiToolTip->AddFrame(imgFrame);

	// 아이템 이미지
	UIFrame* itemImage = new UIFrame();
	itemImage->init("itemImage", 0, 0, item->GetInvenImage()->getWidth(), item->GetInvenImage()->getHeight(), item->GetInvenImageName());
	imgFrame->AddFrame(itemImage);

	// 공격력
	if (item->GetMinAtk() != 0 && item->GetMaxAtk() != 0)
	{
		UIText* attack = new UIText();
		attack->init("attack", 75, 50, 80, 80, "공격력 : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attack);

		UIText* attackValue = new UIText();
		attackValue->init("attackValue", 155, 50, 200, 80, to_string_with_precision(item->GetMinAtk(), 0) + " ~ " + to_string_with_precision(item->GetMaxAtk(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackValue);
	}

	// 공격속도
	if (item->GetAtkSpeed() != 0)
	{
		UIText* attackSpd = new UIText();
		attackSpd->init("attackSpd", 75, 70, 200, 80, "초당 공격 횟수 : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(attackSpd);

		UIText* attackSpdValue = new UIText();
		attackSpdValue->init("attackSpdValue", 225, 70, 200, 80, to_string_with_precision(item->GetAtkSpeed(), 2), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(attackSpdValue);
	}

	// 방어력
	if (item->GetDefence() != 0)
	{
		UIText* def = new UIText();
		def->init("def", 75, 90, 200, 80, "방어력 : ", FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(255, 255, 255));
		uiToolTip->AddFrame(def);

		UIText* defValue = new UIText();
		defValue->init("defValue", 155, 90, 200, 80, to_string_with_precision(item->GetDefence(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		uiToolTip->AddFrame(defValue);
	}

	// 추가 옵션
	for (int i = 0; i < item->GetSubOptions().size(); i++)
	{
		SubOption* option = item->GetSubOptions()[i];

		int optionR = 255, optionG = 255, optionB = 255;
		if (option->_optionPower < 0) optionR = 255, optionG = 0, optionB = 0;
		if (option->_optionPower > 0) optionR = 0, optionG = 255, optionB = 0;

		UIText* startText = new UIText();
		startText->init("▶" + to_string(i), 15, 120 + i * 15, 30, 30, "▶", FONT::PIX, WORDSIZE::WS_SMALLEST);
		uiToolTip->AddFrame(startText);

		UIText* descript = new UIText();
		descript->init("descript" + to_string(i), 30, 122 + i * 15, 370, 30, OptionString(option), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT,
			RGB(optionR, optionG, optionB));
		uiToolTip->AddFrame(descript);
	}

	_toolTipFinalY = item->GetSubOptions().size() * 20 + 122;

	// 아이템 클래스
	string itemClassString = "일반 아이템";
	switch (item->GetItemClass())
	{
	case ITEMCLASS::IC_NORMAL: itemClassString = "일반 아이템"; break;
	case ITEMCLASS::IC_ADVANCED: itemClassString = "고급 아이템";  break;
	case ITEMCLASS::IC_RARE: itemClassString = "희귀 아이템"; break;
	case ITEMCLASS::IC_LEGENDARY: itemClassString = "전설 아이템"; break;
	}

	UIText* itemClass = new UIText();
	itemClass->init("itemClass", 10, _toolTipFinalY + 5, 150, 30, itemClassString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemClass);

	// 아이템 종류
	string itemKindString = "양손무기";
	switch (item->GetitemType())
	{
	case ITEMTYPE::IT_WEAPON_ONEHAND: itemKindString = "한손무기"; break;
	case ITEMTYPE::IT_WEAPON_TWOHAND: itemKindString = "양손무기"; break;
	case ITEMTYPE::IT_SUBWEAPON: itemKindString = "보조장비"; break;
	case ITEMTYPE::IT_ACCESORRY: itemKindString = "악세서리"; break;
	}

	UIText* itemKind = new UIText();
	itemKind->init("itemKind", 10, _toolTipFinalY + 20, 150, 30, itemKindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(120, 120, 120));
	uiToolTip->AddFrame(itemKind);
	_toolTipFinalY += 15;

	// 비고
	string weaponkindString = "";
	switch (item->GetWeaponType())
	{
	case WEAPONTYPE::WT_CHARGE: weaponkindString = "#충전형"; break;
	case WEAPONTYPE::WT_KATANA: weaponkindString = "#카타나"; break;
	case WEAPONTYPE::WT_PISTOL: weaponkindString = "#권총"; break;
	case WEAPONTYPE::WT_SPEAR: weaponkindString = "#창"; break;
	}

	if (weaponkindString != "")
	{
		UIText* tag = new UIText();
		tag->init("tag", 10, _toolTipFinalY + 25, 100, 30, weaponkindString, FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(162, 210, 148));
		uiToolTip->AddFrame(tag);
		_toolTipFinalY += 20;
	}

	// 스킬
	if (item->GetSkill() != nullptr)
	{
		UIImage* skillFrame = new UIImage();
		skillFrame->init("skillFrame", 10, _toolTipFinalY + 25, 280, 55, "ToolTipSkillCover", false, 0, 0, 280 / 30.f, 55 / 30.f, 80);
		uiToolTip->AddFrame(skillFrame);
		UIFrame* skillImage = new UIFrame();
		skillImage->init("skillImage", 2, 2, 51, 51, item->GetSkill()->GetImageName(), 51.f / 57, 51.f / 57);
		skillFrame->AddFrame(skillImage);
		UIText* skillName = new UIText();
		skillName->init("skillName", 55, 2, 300, 80, item->GetSkill()->GetName(), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_LEFT, RGB(230, 230, 0));
		skillFrame->AddFrame(skillName);
		UIText* skillDescription = new UIText();
		skillDescription->init("skillDescription", 55, 22, 220, 120, item->GetSkill()->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT);
		skillFrame->AddFrame(skillDescription);
		UIText* skillCoolTime = new UIText();
		skillCoolTime->init("skillCoolTime", 257, 39, 20, 30, to_string_with_precision(item->GetSkill()->GetCoolTime(), 1), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_RIGHT, RGB(221, 173, 103));
		skillFrame->AddFrame(skillCoolTime);
		_toolTipFinalY += 45;
	}

	// 설명
	UIText* description = new UIText();
	description->init("description", 10, _toolTipFinalY + 45, 350, 200, item->GetDescription(), FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(208, 247, 252));
	uiToolTip->AddFrame(description);
	_toolTipFinalY += (item->GetDescription().length() / 22) * 10 + 70;

	if (_shopBase->GetIsViewing())
	{
		UIFrame* moneyImg = new UIFrame();
		moneyImg->init("moneyImg", 352, _toolTipFinalY - 2, 19, 19, "moneyUI");
		uiToolTip->AddFrame(moneyImg);

		UIText* sellMoney = new UIText();
		sellMoney->init("sellMoney", 250, _toolTipFinalY, 100, 50, to_string_with_precision(item->GetSellPrice(), 0), FONT::PIX, WORDSIZE::WS_SMALL, WORDSORT::WSORT_RIGHT);
		uiToolTip->AddFrame(sellMoney);
	}

	_toolTipFinalY += 30;
	uiToolTip->SetScaleY(_toolTipFinalY / 100.f);
}

/// <summary>
/// Inventory의 OptionString과 같음. Shop용.
/// </summary>
string Shop::OptionString(SubOption* option)
{
	string optionResult = "";

	if (option->_optionPower != 0)
	{
		optionResult += (option->_optionPower >= 0 ? "+" : "") + to_string_with_precision(option->_optionPower, 0);

		switch (option->_optionId)
		{
		case POWER:
			optionResult += " 위력";
			break;
		case ATKSPEED:
			optionResult += "% 공격속도";
			break;
		case DASHATK:
			optionResult += "% 대쉬 공격력";
			break;
		case DEFENCE:
			optionResult += " 방어력";
			break;
		case BLOCK:
			optionResult += " 막기";
			break;
		case CRITICALPERCENT:
			optionResult += " 크리티컬";
			break;
		case CRITICALDAMAGE:
			optionResult += " 크리티컬 데미지";
			break;
		case MINDAMAGE:
			optionResult += " 최소 데미지";
			break;
		case MAXDAMAGE:
			optionResult += " 최대 데미지";
			break;
		case FINALDAMAGEPERCENT:
			optionResult += "% 최종 데미지";
			break;
		case FINALDAMAGE:
			optionResult += " 최종 데미지";
			break;
		case TOUGHNESS:
			optionResult += " 강인함";
			break;
		case TRUEDAMAGE:
			optionResult += " 고정 데미지";
			break;
		case MAXHP:
			optionResult += " 최대 체력";
			break;
		case MAXHPPERCENT:
			optionResult += "% 최대 체력";
			break;
		case EVADE:
			optionResult += " 회피";
			break;
		case MOVESPEED:
			optionResult += "% 이동속도";
			break;
		case JUMPPOWER:
			optionResult += " 점프력";
			break;
		case GOLDDROP:
			optionResult += "% 골드 드랍";
			break;
		case RELOADSPEED:
			optionResult += "% 재장전 속도";
			break;
		case DASHCOUNT:
			optionResult += " 대쉬 횟수";
			break;
		case ACCURACY:
			optionResult += " 조준 정확도";
			break;
		case FIREDAMAGE:
			optionResult += " 화상 피해";
			break;
		case ICEDAMAGE:
			optionResult += " 냉기 피해";
			break;
		case ELECDAMAGE:
			optionResult += " 감전 피해";
			break;
		case POSIONDAMAGE:
			optionResult += " 중독 피해";
			break;
		case STUNDAMAGE:
			optionResult += " 기절 피해";
		default:
			break;
		}
	}

	switch (option->_optionId)
	{
	case IMMUNEFIRE:
		optionResult += "화상 면역";
		break;
	case IMMUNEICE:
		optionResult += "냉기 면역";
		break;
	case IMMUNEELEC:
		optionResult += "감전 면역";
		break;
	case IMMUNEPOSION:
		optionResult += "중독 면역";
		break;
	case IMMUNESTUN:
		optionResult += "기절 면역";
		break;
	case TOFIRE:
		optionResult += "화상 부여";
		break;
	case TOICE:
		optionResult += "냉기 부여";
		break;
	case TOELEC:
		optionResult += "감전 부여";
		break;
	case TOPOSION:
		optionResult += "중독 부여";
		break;
	case TOSTUN:
		optionResult += "기절 부여";
	}

	if (option->_description != ".")
		optionResult += option->_description;

	return optionResult;
}