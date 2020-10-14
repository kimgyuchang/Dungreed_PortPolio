#include "stdafx.h"
#include "Treasure.h"

HRESULT Treasure::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_isOpened = false;
	return S_OK;
}

void Treasure::update()
{
	NPC::update();
}

void Treasure::release()
{
	NPC::release();
}

void Treasure::render(HDC hdc)
{
	if (_vImages[_useImage]->getMaxFrameX() == 0) CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
	else CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
	
	if (_isInteracting && !_isOpened)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void Treasure::Animation()
{
	NPC::Animation();
}

void Treasure::initSecond()
{
	NPC::initSecond();
}

void Treasure::Activate()
{
	int coinNumber = RANDOM->range(10, 30);
	for (int i = 0; i < coinNumber; i++)
	{
		Coin* coin = new Coin(*dynamic_cast<Coin*>(DATAMANAGER->GetObjectById(524)));
		coin->SetUseImage(i == 0 ? 0 : (RANDOM->range(10) > 8 ? 0 : 1));
		coin->SetCoin(_x, _y - 30, RANDOM->range(-5.f, 5.f), RANDOM->range(4.f, 6.f));
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(coin);
		_isOpened = true;
		_useImage = 1;
	}

	Item* item = new Item(*dynamic_cast<Item*>(DATAMANAGER->GetItemById(RANDOM->range(DATAMANAGER->GetItemMinId(), DATAMANAGER->GetItemMaxId()))));
	DropItem* dropItem = new DropItem();
	dropItem->init();
	dropItem->SetItem(_x - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameWidth() / 2)), _y - 70 - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameHeight() / 2)), 0, RANDOM->range(4.f, 6.f), item);
	MAPMANAGER->GetPlayMap()->GetObjects().push_back(dropItem);
}
