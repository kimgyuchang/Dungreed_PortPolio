#include "stdafx.h"
#include "TreasureSpawner.h"

HRESULT TreasureSpawner::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 48, 48);
	_isOff = false;

	return S_OK;
}

void TreasureSpawner::update()
{
	if (!_isOff)
	{
		Object::update();
	}
}

void TreasureSpawner::release()
{
	Object::release();
}

void TreasureSpawner::render(HDC hdc)
{
	if (INPUT->GetKey(VK_F5))
	{
		CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

/// <summary>
/// 상자 스포너를 통해 상자를 스폰
/// </summary>
void TreasureSpawner::SpawnTreasure()
{
	if (!_isOff)
	{
		SetIsOff(true);
		int treasureId = RANDOM->range(2, 6);

		Treasure* treasure = new Treasure(*dynamic_cast<Treasure*>(DATAMANAGER->GetObjectById(treasureId)));
		dynamic_cast<Treasure*>(treasure)->initSecond();
		treasure->SetX(_x + (_vImages[_useImage]->getWidth() / 2) - treasure->GetImage(_useImage)->getFrameWidth() / 2);
		treasure->SetY(_y - treasure->GetImage(_useImage)->getFrameWidth() / 2);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(treasure);

		_isDead = true;
	}
	
}
