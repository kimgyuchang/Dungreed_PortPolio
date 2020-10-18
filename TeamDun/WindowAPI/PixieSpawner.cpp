#include "stdafx.h"
#include "PixieSpawner.h"

HRESULT PixieSpawner::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 48, 48);
	_isOff = false;

	return S_OK;
}

void PixieSpawner::update()
{
	if (!_isOff)
	{
		Object::update();
	}
}

void PixieSpawner::release()
{
	Object::release();
}

void PixieSpawner::render(HDC hdc)
{
	if (INPUT->GetKey(VK_F5))
	{
		CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

/// <summary>
/// 상자 스포너를 통해 상자를 스폰
/// </summary>
void PixieSpawner::SpawnPixie()
{
	if (!_isOff)
	{
		SetIsOff(true);
		int treasureId = RANDOM->range(2, 6);

		int pixieCase = RANDOM->range(100);
		if (pixieCase < 60) pixieCase = 13;
		else if (pixieCase < 90) pixieCase = 14;
		else if (pixieCase < 97) pixieCase = 15;
		else pixieCase = 16;

		HpPixie* pixie = new HpPixie(*dynamic_cast<HpPixie*>(DATAMANAGER->GetObjectById(pixieCase)));
		pixie->SetX(_x + (_vImages[_useImage]->getWidth() / 2) - pixie->GetImage(_useImage)->getFrameWidth() / 2);
		pixie->SetY(_y);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(pixie);

		_isDead = true;
	}
}
