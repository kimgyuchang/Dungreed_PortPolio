#include "stdafx.h"
#include "BloodStoneRing.h"

HRESULT BloodStoneRing::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	
	return S_OK;
}

void BloodStoneRing::update()
{
	
	//혈석반지 피차는용
	if (ENTITYMANAGER->getPlayer()->GetKillPoint() == 10)
	{
		ENTITYMANAGER->getPlayer()->SetKillPoint(0);
		ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP()+5);
		if (ENTITYMANAGER->getPlayer()->GetHP() > ENTITYMANAGER->getPlayer()->GetMaxHp())
		{
			ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetMaxHp());
		}
	}
}

void BloodStoneRing::render(HDC hdc)
{
}

void BloodStoneRing::release()
{
}
