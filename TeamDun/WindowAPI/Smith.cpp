#include "stdafx.h"
#include "Smith.h"

HRESULT Smith::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	_npcName = "신홍";
	_vConvTexts = vector<string>
	{
		"그리 좋은 물건은 아니지만... 보탬은 될 걸세!",
		"나름 쓸만한 놈을 만들어 봤다네! 멋지지 않은가?! 으하하!",
		"오늘 만든 건 그게 끝이라네. 다음에 다시 오게나."
	};

	_isInteracting = false;
	_isActivating = false;
	_useConv = true;
	_isTalked = false;

	return S_OK;
}

void Smith::update()
{
	PressActivateKey();
	CollisionInteraction();
	Animation();
}

void Smith::release()
{
	Object::release();
}

void Smith::render(HDC hdc)
{
	Object::render(hdc);
	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void Smith::Activate()
{
	if (!_isTalked)
	{
		Item* item;
		while (true) {
			item = DATAMANAGER->GetItemByIndex(RANDOM->range(0, DATAMANAGER->GetItemSize() - 1));
			if (item->GetWeaponType() != WEAPONTYPE::WT_CHARGE && item->GetWeaponType() != WEAPONTYPE::WT_PISTOL && item->GetWeaponType() != WEAPONTYPE::WT_RANGE)
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

void Smith::PressActivateKey()
{
	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		ShowConversation();
	}
}

void Smith::ShowConversation()
{
	if (_useConv && !_isActivating)
	{
		SetConvUI();
		Activate();
		_convFrame->ToggleIsViewing();
	}
}

void Smith::SetConvUI()
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

void Smith::CollisionInteraction()
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

void Smith::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
}
