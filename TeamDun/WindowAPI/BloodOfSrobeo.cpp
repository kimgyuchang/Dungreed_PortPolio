#include "stdafx.h"
#include "BloodOfSrobeo.h"

HRESULT BloodOfSrobeo::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	_isReady = true;
	_CoolTime = 0;
	return S_OK;
}

void BloodOfSrobeo::update()
{
	if (!_isReady)
	{
		_CoolTime++;
		if (_CoolTime > 30)
		{
			_CoolTime = 0;
			_isReady = true;
		}
	}
	
	if (ENTITYMANAGER->getPlayer()->GetIsCritical() && _isReady)
	{
		
		ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() + 2);
		if (ENTITYMANAGER->getPlayer()->GetHP() > ENTITYMANAGER->getPlayer()->GetInitHp())
		{
			ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetInitHp());
		}
		ENTITYMANAGER->getPlayer()->SetIsCritical(false);
	}
}

void BloodOfSrobeo::render(HDC hdc)
{
}

void BloodOfSrobeo::release()
{
}
