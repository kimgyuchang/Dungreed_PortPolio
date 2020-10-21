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
	Move();
	PixelCollision();
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
	_speedY = 0;
	_gravity = 0.5f;
}

void Treasure::Activate()
{
	if (!_isOpened)
	{
		int coinNumber = RANDOM->range(10, 30);
		for (int i = 0; i < coinNumber + coinNumber * ((ENTITYMANAGER->getPlayer()->GetGoldDrop() - 100) / 100.f); i++)
		{
			Coin* coin = new Coin(*dynamic_cast<Coin*>(DATAMANAGER->GetObjectById(524)));
			coin->SetUseImage(i == 0 ? 0 : (RANDOM->range(10) > 8 ? 0 : 1));
			coin->SetCoin(_x, coin->GetUseImage() == 0 ? _y - 40 : _y - 30, RANDOM->range(-5.f, 5.f), RANDOM->range(4.f, 6.f));
			MAPMANAGER->GetPlayMap()->GetObjects().push_back(coin);
			_isOpened = true;
			_useImage = 1;
		}

		Item* item = DATAMANAGER->GetItemByIndex(RANDOM->range(0, DATAMANAGER->GetItemSize()-1));
		DropItem* dropItem = new DropItem();
		dropItem->init();
		dropItem->SetItem(_x - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameWidth() / 2)), _y - 70 - ((item->GetRenderScale() - 1) * (item->GetDropImage()->getFrameHeight() / 2)), 0, RANDOM->range(4.f, 6.f), item);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(dropItem);

		switch (_treasureType)
		{
		case TREASURETYPE::TST_BLUE : case TREASURETYPE::TST_BROWN: case TREASURETYPE::TST_GOLD: case TREASURETYPE::TST_GRAY:
			SOUNDMANAGER->play("오브젝트_상자오픈_별거아님");
			break;

		case TREASURETYPE::TST_LEGENDARY:
			SOUNDMANAGER->play("오브젝트_전설상자오픈");
			break;

		case TREASURETYPE::TST_BOSS:
			SOUNDMANAGER->play("NPC_보스상자열기");
			break;
		}
	}
}

void Treasure::Move()
{
	float _moveY = -sin(PI / 4) * _speedY;
	_y += _moveY;

	_speedY -= _gravity;
}

void Treasure::PixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* coinImg = _vImages[_useImage];

	float _probeBottom = _y + coinImg->getFrameHeight();

	for (int i = _probeBottom + _speedY - 2; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + coinImg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 || (r == 0 && g == 0 && b == 255))
		{
			isCollide = true;
			_y = i - _vImages[_useImage]->getFrameHeight();
			_speedY = _speedY / 10 * 9;
			break;
		}
	}

}