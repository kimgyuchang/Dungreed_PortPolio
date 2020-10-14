#include "stdafx.h"
#include "Coin.h"

HRESULT Coin::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	DropObjs::init(id, name, type, imgNames);

	return S_OK;
}

void Coin::update()
{
	DropObjs::update();
}

void Coin::release()
{
	DropObjs::release();
}

void Coin::render(HDC hdc)
{
	DropObjs::render(hdc);
}

void Coin::SetCoin(float x, float y, float speedX, float speedY)
{
	_x = x;
	_y = y;
	_speedX = speedX;
	_speedY = speedY;
	_gravity = 0.5f;
}

void Coin::CheckCollision()
{
	RECT temp;

	if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
	{
		EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2 + RANDOM->range(-30, 30), _y + RANDOM->range(-30, 30), 100, 100, _useImage == 0 ? "100G" : "10G", PIX, WS_MIDDLE, WSORT_LEFT, RGB(250, 222, 82));
		ENTITYMANAGER->getPlayer()->SetMoney(ENTITYMANAGER->getPlayer()->GetMoney() + (_useImage == 0 ? 100 : 10));
		_isDead = true;
	}
}
