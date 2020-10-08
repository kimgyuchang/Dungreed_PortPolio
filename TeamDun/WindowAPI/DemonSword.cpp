#include "stdafx.h"
#include "DemonSword.h"

HRESULT DemonSword::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name,
	string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed,
	int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet,
	float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage);

	_isRenderFirst = true;

	return S_OK;
}

void DemonSword::update()
{
}

void DemonSword::render(HDC hdc)
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();
	int posX = ENTITYMANAGER->getPlayer()->GetX() + 40 - _vImages[_currentImage]->getWidth() / 2;
	int posY = ENTITYMANAGER->getPlayer()->GetY() + 45 - _vImages[_currentImage]->getHeight() / 2;
	float angle = -getAngle(CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y), 
		ENTITYMANAGER->getPlayer()->GetX() + 40, ENTITYMANAGER->getPlayer()->GetY() + 45);

	CAMERAMANAGER->Render(hdc, _vImages[_currentImage], posX, posY, angle);
}

void DemonSword::release()
{
}
