#include "stdafx.h"
#include "GoldenCandy.h"

HRESULT GoldenCandy::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	
	return S_OK;
}

void GoldenCandy::update()
{
	

	if (ENTITYMANAGER->getPlayer()->GetIsLeft())
	{
		EFFECTMANAGER->AddEffect(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), ENTITYMANAGER->getPlayer()->GetImage(0)->getKey(), 4 , 0 , 1,false,150);
	} 
	else
	{
		EFFECTMANAGER->AddEffect(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), ENTITYMANAGER->getPlayer()->GetImage(0)->getKey(), 4 , 0 , 0, false, 150);
	}
	

}

void GoldenCandy::render(HDC hdc)
{
}

void GoldenCandy::release()
{
}
