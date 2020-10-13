#include "stdafx.h"
#include "Shop.h"

HRESULT Shop::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	
	return S_OK;
}

void Shop::update()
{
	NPC::update();
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
