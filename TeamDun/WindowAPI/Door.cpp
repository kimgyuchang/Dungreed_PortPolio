#include "stdafx.h"
#include "Door.h"

HRESULT Door::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	return S_OK;
}

void Door::update()
{
	Object::update();
}

void Door::release()
{
	Object::release();
}

void Door::render(HDC hdc)
{
//	Object::render(hdc);
	string n = to_string(_x) + " " + to_string(_y) + " " + to_string(_x / 48) + " " + to_string(_y / 48);
	CAMERAMANAGER->TextDraw(hdc, _x, _y, n.c_str(), n.length(), 255, 255, 255);
}

void Door::Animation()
{
	Object::Animation();
}
