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
	NPC::render(hdc);
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
		coin->SetCoin(_x, _y, RANDOM->range(-5.f, 5.f), RANDOM->range(2.f, 5.f));
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(coin);
	}
}
