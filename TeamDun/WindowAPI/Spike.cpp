#include "stdafx.h"
#include "Spike.h"

HRESULT Spike::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	return S_OK;
}

void Spike::update()
{
	Object::update();
	_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	CheckCollision();
}

void Spike::release()
{
	Object::release();
}

void Spike::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
}

void Spike::CheckCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &_body, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		ENTITYMANAGER->getPlayer()->GetHitDamage(7);
	}
}
