#include "stdafx.h"
#include "GunShop.h"

HRESULT GunShop::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	_npcName = "샘";
	_vConvTexts = vector<string>
	{
		"겨우 무기 구실은 할 수 있겠군.",
		"오,이번에는 꽤 괜찮은데?.",
		"한 손에 한정씩은 사나이의 로망이긴 하지만, 효율도 안 좋고 위험해.    그만둬."
	};

	_isInteracting = false;
	_isActivating = false;
	_useConv = true;
	_isTalked = false;

	return S_OK;
}

void GunShop::update()
{
	PressActivateKey();
	CollisionInteraction();
	Animation();
}

void GunShop::release()
{
	Object::release();
}

void GunShop::render(HDC hdc)
{
	Object::render(hdc);
	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void GunShop::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
}

void GunShop::Activate()
{
	if (!_isTalked)
	{
		Item* item;
		while (true)
		{
			item = DATAMANAGER->GetItemByIndex(RANDOM->range(0, DATAMANAGER->GetItemSize() - 1));

			if (item->GetWeaponType() == WEAPONTYPE::WT_CHARGE || item->GetWeaponType() == WEAPONTYPE::WT_PISTOL || item->GetWeaponType() == WEAPONTYPE::WT_RANGE)
			{
				break;
			}
		}
		DropItem* dropItem = new DropItem();
		dropItem->init();
		dropItem->SetItem(_x - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameWidth() / 2)), _y - 70 - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameHeight() / 2)), 0, RANDOM->range(4.f, 6.f), item);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(dropItem);
		_isTalked = true;
	}
}

void GunShop::PressActivateKey()
{
	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		ShowConversation();
	}
}

void GunShop::ShowConversation()
{
	if (_useConv && !_isActivating)
	{
		SetConvUI();
		Activate();
		_convFrame->ToggleIsViewing();
	}
}

void GunShop::SetConvUI()
{
	dynamic_cast<UIText*>(_convFrame->GetChild("name"))->SetText(_npcName);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetCntPos(0);
	if (!_isTalked)
	{
		dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[RANDOM->range(0, 1)]);
	}
	if (_isTalked)
	{
		dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[2]);
	}
}

void GunShop::CollisionInteraction()
{
	_interactRect = RectMake(_x - 50, _y - 50, _vImages[_useImage]->getFrameWidth() + 100, _vImages[_useImage]->getFrameHeight() + 100);

	RECT temp;
	if (IntersectRect(&temp, &_interactRect, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		_isInteracting = true;
	}
	else
	{
		_isInteracting = false;
	}
}
