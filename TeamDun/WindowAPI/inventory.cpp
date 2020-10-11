#include "stdafx.h"
#include "inventory.h"
#include "player.h"

HRESULT Inventory::init()
{
	_InvenFrame = UIMANAGER->GetGameFrame()->GetChild("InventoryFrame");
	_invenFullTextOn = false;
	_invenFullTextTimer = 0;

	_p = ENTITYMANAGER->getPlayer();
	return S_OK;
}

void Inventory::update()
{
	CheckInvenText();

	if (_InvenFrame->GetIsViewing())
	{
		UpdateMoney();
		EquipItem();
		UnEquipItem();
	}
}

void Inventory::render(HDC hdc)
{
}

void Inventory::release()
{
}

void Inventory::UpdateMoney()
{
	dynamic_cast<UIText*>(_InvenFrame->GetChild("moneyText"))->SetText(to_string(_p->GetMoney()));
}


void Inventory::EquipItem()
{
	if (_leftClicked) _leftClickTimer++;
	if (_leftClickTimer > 15)
	{
		_leftClickTimer = 0;
		_leftClicked = false;
	}

	if (INPUT->GetIsLButtonClicked())
	{
		if (!_leftClicked)
		{
			for (int i = 0; i < 15; i++)
			{
				UIFrame* curFrame = _InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame");

				if (PtInRect(&curFrame->GetRect(), _ptMouse))
				{
					_leftClicked = true;
					_leftClickTimer = 0;
				}
			}
		}

		else
		{
			for (int i = 0; i < 15; i++)
			{
				UIFrame* curFrame = _InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame");

				if (PtInRect(&curFrame->GetRect(), _ptMouse))
				{
					if (_vInvenItems.size() > i)
					{
						Item* item = _vInvenItems[i];
						item->EquipUnEquipStatus(true);

						switch (item->GetitemType())
						{
						case ITEMTYPE::IT_WEAPON_ONEHAND:
							if (_p->GetWeapon(0) == nullptr)
							{
								_p->SetWeapon(0, item);
								if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}
							else if (_p->GetWeapon(1) == nullptr)
							{
								_p->SetWeapon(1, item);
								if (_p->GetSelectedWeaponIdx() != 1) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}
							else
							{
								_p->GetWeapon(0)->EquipUnEquipStatus(false);
								if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
								SwitchItem(0, item, i);
							}
							break;

						case ITEMTYPE::IT_WEAPON_TWOHAND:
							if (_p->GetWeapon(0) == nullptr)
							{
								_p->SetWeapon(0, item);
								if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}

							else if (_p->GetWeapon(1) == nullptr)
							{
								_p->SetWeapon(1, item);
								if (_p->GetSelectedWeaponIdx() != 1) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}

							else if (_vInvenItems.size() >= 15)
							{
								OnInvenFullText();
								item->EquipUnEquipStatus(false);
							}
							else
							{
								_p->GetWeapon(0)->EquipUnEquipStatus(false);
								if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
								SwitchItem(0, item, i);
								if (_p->GetSubWeapon(0) != nullptr)
								{
									AddItem(_p->GetSubWeapon(0));
									if (_p->GetSelectedWeaponIdx() == 0) _p->GetSubWeapon(0)->EquipUnEquipStatus(false);
									_p->SetSubWeapon(0, nullptr);
								}
							}
							break;

						case ITEMTYPE::IT_SUBWEAPON:

							if ((_p->GetWeapon(0) == nullptr || (_p->GetWeapon(0)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)) &&
								(_p->GetWeapon(1) == nullptr || (_p->GetWeapon(1)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND)))
							{ // 양쪽 다 서브무기를 낄 수 없는 상태라면
								OnInvenFullText();
								item->EquipUnEquipStatus(false);
							}

							else if (_p->GetWeapon(0) != nullptr && _p->GetWeapon(0)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(0) == nullptr)
							{ // 무기 0이 있고 두손무기가 아니며, 서브웨폰이 없다면
								_p->SetSubWeapon(0, item);
								if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}

							else if (_p->GetWeapon(1) != nullptr && _p->GetWeapon(1)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(1) == nullptr)
							{ // 무기 1이 있고 두손무기가 아니며, 서브웨폰이 없다면
								_p->SetSubWeapon(1, item);
								if (_p->GetSelectedWeaponIdx() != 1) item->EquipUnEquipStatus(false);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}

							else
							{
								if (_p->GetWeapon(0) != nullptr && _p->GetWeapon(0)->GetitemType() != ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(0) != nullptr)
								{
									_p->GetSubWeapon(0)->EquipUnEquipStatus(false);
									if (_p->GetSelectedWeaponIdx() != 0) item->EquipUnEquipStatus(false);
									SwitchItem(1, item, i);
								}
								else
								{
									OnInvenFullText();
									item->EquipUnEquipStatus(false);
								}
							}
							break;

						case ITEMTYPE::IT_ACCESORRY:
							bool equalCheck = false;
							for (int i = 0; i < _p->GetVAccessories().size(); i++)
							{
								if (_p->GetAccessory(i)->GetId() == item->GetId())
								{
									OnInvenEqualText();
									item->EquipUnEquipStatus(false);
									equalCheck = true;
									break;
								}
							}

							if (equalCheck) break;

							if (_p->GetVAccessories().size() == _p->GetAccesoryCount())
							{
								OnInvenFullText();
								item->EquipUnEquipStatus(false);
							}

							else
							{
								_p->GetVAccessories().push_back(item);
								_vInvenItems.erase(_vInvenItems.begin() + i);
							}
							break;
						}

						ReloadUIImages();
						break;
					}
				}
			}
		}
	}
}

void Inventory::SwitchItem(int num, Item* item, int index)
{
	Item* getItem;
	if (num == 0)
	{
		getItem = _p->GetWeapon(0);
		_p->SetWeapon(0, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 1)
	{
		getItem = _p->GetSubWeapon(0);
		_p->SetSubWeapon(0, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 2)
	{
		getItem = _p->GetWeapon(1);
		_p->SetWeapon(1, item);
		_vInvenItems[index] = getItem;
	}

	else if (num == 3)
	{
		getItem = _p->GetSubWeapon(1);
		_p->SetSubWeapon(1, item);
		_vInvenItems[index] = getItem;
	}

	else
	{
		getItem = _p->GetAccessory(num - 4);
		_p->SetVAccessory(num - 4, item);
		_vInvenItems[index] = getItem;
	}
}

void Inventory::UnEquipItem()
{
	if (INPUT->GetIsLButtonClicked())
	{
		if (!_leftClicked)
		{
			if (PtInRect(&_InvenFrame->GetChild("curWeapon_1")->GetRect(), _ptMouse) ||
				PtInRect(&_InvenFrame->GetChild("curWeapon_2")->GetRect(), _ptMouse) ||
				PtInRect(&_InvenFrame->GetChild("curWeaponSub_1")->GetRect(), _ptMouse) ||
				PtInRect(&_InvenFrame->GetChild("curWeaponSub_2")->GetRect(), _ptMouse))
			{
				_leftClicked = true;
				_leftClickTimer = 0;
			}

			else
			{
				for (int i = 0; i < _p->GetAccesoryCount(); i++)
				{
					if (PtInRect(&_InvenFrame->GetChild("accesoryFrame_" + to_string(i))->GetRect(), _ptMouse))
					{
						_leftClicked = true;
						_leftClickTimer = 0;
					}
				}
			}
		}

		else
		{
			if (PtInRect(&_InvenFrame->GetChild("curWeapon_1")->GetRect(), _ptMouse) && _p->GetWeapon(0) != nullptr)
			{
				if ((_vInvenItems.size() > 13 && _p->GetWeapon(0)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(0) != nullptr) || _vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetWeapon(0));
					if(_p->GetSelectedWeaponIdx() == 0)	_p->GetWeapon(0)->EquipUnEquipStatus(false);
					_p->SetWeapon(0, nullptr);
					if (_p->GetSubWeapon(0) != nullptr)
					{
						AddItem(_p->GetSubWeapon(0));
						if (_p->GetSelectedWeaponIdx() == 0) _p->GetSubWeapon(0)->EquipUnEquipStatus(false);
						_p->SetSubWeapon(0, nullptr);
					}
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeapon_2")->GetRect(), _ptMouse) && _p->GetWeapon(1) != nullptr)
			{
				if ((_vInvenItems.size() > 13 && _p->GetWeapon(1)->GetitemType() == ITEMTYPE::IT_WEAPON_TWOHAND && _p->GetSubWeapon(1) != nullptr) || _vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetWeapon(1));
					if (_p->GetSelectedWeaponIdx() == 1) _p->GetWeapon(1)->EquipUnEquipStatus(false);
					_p->SetWeapon(1, nullptr);
					if (_p->GetSubWeapon(1) != nullptr)
					{
						AddItem(_p->GetSubWeapon(1));
						if (_p->GetSelectedWeaponIdx() == 1) _p->GetSubWeapon(1)->EquipUnEquipStatus(false);
						_p->SetSubWeapon(1, nullptr);
					}
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_1")->GetRect(), _ptMouse) && _p->GetSubWeapon(0) != nullptr)
			{
				if (_vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetSubWeapon(0));
					if (_p->GetSelectedWeaponIdx() == 0) _p->GetSubWeapon(0)->EquipUnEquipStatus(false);
					_p->SetSubWeapon(0, nullptr);
				}
			}

			else if (PtInRect(&_InvenFrame->GetChild("curWeaponSub_2")->GetRect(), _ptMouse) && _p->GetSubWeapon(1) != nullptr)
			{
				if (_vInvenItems.size() > 14)
				{
					OnInvenFullText();
				}

				else
				{
					AddItem(_p->GetSubWeapon(1));
					if (_p->GetSelectedWeaponIdx() == 1) _p->GetSubWeapon(1)->EquipUnEquipStatus(false);
					_p->SetSubWeapon(1, nullptr);
				}
			}

			else
			{
				for (int i = 0; i < _p->GetAccesoryCount(); i++)
				{
					if (PtInRect(&_InvenFrame->GetChild("accesoryFrame_" + to_string(i))->GetRect(), _ptMouse) && _p->GetVAccessories().size() > i)
					{
						if (_vInvenItems.size() > 14)
						{
							OnInvenFullText();
						}

						else
						{
							AddItem(_p->GetAccessory(i));
							_p->GetAccessory(i)->EquipUnEquipStatus(false);
							_p->GetVAccessories().erase(_p->GetVAccessories().begin() + i);
						}
						break;
					}
				}
			}

			ReloadUIImages();
		}
	}
}

bool Inventory::AddItem(Item* item)
{
	if (_vInvenItems.size() < 15)
	{
		_vInvenItems.push_back(item);
		ReloadUIImages();
		return true;
	}

	return false;
}

void Inventory::ReloadUIImages()
{
	Player* p = ENTITYMANAGER->getPlayer();
	_InvenFrame->GetChild("curWeapon_1")->SetImage(nullptr);
	if (p->GetWeapon(0) != nullptr) _InvenFrame->GetChild("curWeapon_1")->SetImage(p->GetWeapon(0)->GetInvenImage());
	_InvenFrame->GetChild("curWeapon_2")->SetImage(nullptr);
	if (p->GetWeapon(1) != nullptr) _InvenFrame->GetChild("curWeapon_2")->SetImage(p->GetWeapon(1)->GetInvenImage());
	_InvenFrame->GetChild("curWeaponSub_1")->SetImage(nullptr);
	if (p->GetSubWeapon(0) != nullptr) _InvenFrame->GetChild("curWeaponSub_1")->SetImage(p->GetSubWeapon(0)->GetInvenImage());
	_InvenFrame->GetChild("curWeaponSub_2")->SetImage(nullptr);
	if (p->GetSubWeapon(1) != nullptr) _InvenFrame->GetChild("curWeaponSub_2")->SetImage(p->GetSubWeapon(1)->GetInvenImage());
	for (int i = 0; i < p->GetAccesoryCount(); i++)
	{
		_InvenFrame->GetChild("accesoryFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(nullptr);
		if (p->GetVAccessories().size() > i && p->GetAccessory(i) != nullptr)
			_InvenFrame->GetChild("accesoryFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(p->GetAccessory(i)->GetInvenImage());
	}

	for (int i = 0; i < 15; i++)
	{
		_InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(nullptr);
		if (i < _vInvenItems.size())
			_InvenFrame->GetChild("itemFrame_" + to_string(i))->GetChild("itemImageFrame")->SetImage(_vInvenItems[i]->GetInvenImage());
	}
}

void Inventory::OnInvenFullText()
{
	_invenFullTextOn = true;
	_invenFullTextTimer = 0;
	UIMANAGER->GetGameFrame()->GetChild("isFullText")->SetIsViewing(true);
}

void Inventory::OnInvenEqualText()
{
	_invenEqualTextOn = true;
	_invenEqualTextTimer = 0;
	UIMANAGER->GetGameFrame()->GetChild("isEqualText")->SetIsViewing(true);
}

void Inventory::CheckInvenText()
{
	if (_invenFullTextOn)
	{
		_invenFullTextTimer++;
		if (_invenFullTextTimer > 25)
		{
			UIMANAGER->GetGameFrame()->GetChild("isFullText")->SetIsViewing(false);
			_invenFullTextTimer = 0;
			_invenFullTextOn = false;
		}
	}

	if (_invenEqualTextOn)
	{
		_invenEqualTextTimer++;
		if (_invenEqualTextTimer > 25)
		{
			UIMANAGER->GetGameFrame()->GetChild("isEqualText")->SetIsViewing(false);
			_invenEqualTextTimer = 0;
			_invenEqualTextOn = false;
		}
	}
}

void Inventory::SwitchWeapon(int selectedWeapon)
{
	if (selectedWeapon == 0)
	{
		if (_p->GetWeapon(0) != nullptr)
			_p->GetWeapon(0)->EquipUnEquipStatus(true);
		if (_p->GetSubWeapon(0) != nullptr)
			_p->GetSubWeapon(0)->EquipUnEquipStatus(true);
		if (_p->GetWeapon(0) != nullptr)
			_p->GetWeapon(0)->EquipUnEquipStatus(false);
		if (_p->GetSubWeapon(1) != nullptr)
			_p->GetSubWeapon(1)->EquipUnEquipStatus(false);
	}

	else
	{
		if (_p->GetWeapon(0) != nullptr)
			_p->GetWeapon(0)->EquipUnEquipStatus(false);
		if (_p->GetSubWeapon(0) != nullptr)
			_p->GetSubWeapon(0)->EquipUnEquipStatus(false);
		if (_p->GetWeapon(0) != nullptr)
			_p->GetWeapon(0)->EquipUnEquipStatus(true);
		if (_p->GetSubWeapon(1) != nullptr)
			_p->GetSubWeapon(1)->EquipUnEquipStatus(true);
	}
}