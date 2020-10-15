#include "stdafx.h"
#include "Colt.h"

HRESULT Colt::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	_isRenderFirst = false;
	_animCount = 0;
	_finalAnimCount = 0;
	return S_OK;
}

void Colt::update()
{
	SetBaseRenderPos();
	FireBullet();
	
}

void Colt::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void Colt::release()
{
}

void Colt::FireBullet()
{
	if (_isAttacking)
	{
		ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_PLAYER, _angleCheckPosX +cosf(-_angle)*50,-50+ _angleCheckPosY+ sinf(_angle) * 50, _angle,
			10, 10, 1000, true, _angle);
		_isAttacking = false;
	}
}

void Colt::AttackAnim()
{
	
}

void Colt::Activate()
{
	_isAttacking = true;
}

void Colt::ChangeMap()
{
}


