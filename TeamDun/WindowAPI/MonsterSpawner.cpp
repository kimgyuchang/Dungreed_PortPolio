#include "stdafx.h"
#include "MonsterSpawner.h"

HRESULT MonsterSpawner::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 48, 48);
	_isOff = false;

	return S_OK;
}

void MonsterSpawner::update()
{
	if (!_isOff)
	{
		Object::update();
		CheckCollision();
	}
}

void MonsterSpawner::CheckCollision()
{
	RECT temp;
	if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetRect(), &_body))
	{
		_isOff = true;
		_belongMap->SetIsSpawning(true);
	}
}

void MonsterSpawner::release()
{
	Object::release();
}

void MonsterSpawner::render(HDC hdc)
{
	Object::render(hdc);
}
