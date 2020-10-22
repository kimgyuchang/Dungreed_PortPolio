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
	
	
	if (ENTITYMANAGER->getPlayer()->GetIsDash())
	{
		if (_isReady)
		{
			ENTITYMANAGER->makeBullet("Bomb0", "BulletFX0103", BT_PLAYER, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 0,15, 0, 500, true, 0, BST_GRAVITY,"æ∆¿Ã≈€_∆¯≈∫πŸ±∏¥œ");
		}
		_isReady = false;
		
	}
	else
	{
		_isReady = true;
	}


	
}

void BombPouch::render(HDC hdc)
{
}

void BombPouch::release()
{
}
