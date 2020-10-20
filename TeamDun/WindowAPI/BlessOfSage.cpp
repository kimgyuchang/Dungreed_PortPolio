#include "stdafx.h"
#include "BlessOfSage.h"

HRESULT BlessOfSage::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_vSubOption.push_back(new SubOption(OPTIONTYPE::BLOCK, 5, ""));
	_vSubOption.push_back(new SubOption(OPTIONTYPE::CRITICALPERCENT, 3, ""));
	_vSubOption.push_back(new SubOption(OPTIONTYPE::POWER, 5, ""));
	return S_OK;
}

void BlessOfSage::update()
{
}

void BlessOfSage::render(HDC hdc)
{
}

void BlessOfSage::release()
{
}

