#include "stdafx.h"
#include "BombPouch.h"

HRESULT BombPouch::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	_isReady = true;
	_CoolTime = 0;
	return S_OK;
}

void BombPouch::update()
{
	
	_isReady = true;
	if (_isReady)
	{
		if (ENTITYMANAGER->getPlayer()->GetIsDash())
		{

			_isReady = false;
		}
	}

	
}

void BombPouch::render(HDC hdc)
{
}

void BombPouch::release()
{
}
