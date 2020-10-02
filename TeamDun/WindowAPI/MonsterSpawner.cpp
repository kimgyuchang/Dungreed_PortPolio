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
	if (!_isOff && IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
	{
		SetToSpawnMonsters();
	}
}

void MonsterSpawner::release()
{
	Object::release();
}

void MonsterSpawner::render(HDC hdc)
{
	if (INPUT->GetKey(VK_F5))
	{
		CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

/// <summary>
/// 몬스터 스포너를 통해 몬스터를 스폰시킨다.
/// </summary>
void MonsterSpawner::SetToSpawnMonsters()
{
	SetIsOff(true);

	for (int i = 0; i < _belongMap->GetObjects().size(); i++)
	{
		Object* obj = _belongMap->GetObjects()[i];
		if (obj->GetId() == 2500)
		{
			dynamic_cast<MonsterSpawner*>(obj)->SetIsOff(true);
		}
	} // 해당 맵의 전체 몬스터 스포너를 off상태로 만든다.

	_belongMap->SetDoorSpawning();
	_belongMap->SetIsSpawning(true);
}
