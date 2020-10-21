#include "stdafx.h"
#include "Gear.h"

HRESULT Gear::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_angle = 0;

	return S_OK;
}

void Gear::update()
{
	Object::update();
	_angle += PI / 18;
	if (_angle > (2 * PI)) _angle = 0;

	_body = RectMake(_x + _vImages[_useImage]->getFrameWidth() * 0.2f, _y + _vImages[_useImage]->getFrameHeight() * 0.2f, _vImages[_useImage]->getFrameWidth() * 0.6f, _vImages[_useImage]->getFrameHeight() * 0.6f);
	CheckCollision();
}

void Gear::release()
{
}

void Gear::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y, _angle);
}

void Gear::CheckCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &_body, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		ENTITYMANAGER->getPlayer()->GetHitDamage(7);
	}
}
