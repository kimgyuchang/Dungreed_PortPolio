#include "stdafx.h"
#include "Rifle.h"

HRESULT Rifle::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, 
	float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite,
	vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_isRenderFirst = true;
	_animCount = 0;
	_finalAnimCount = 0;
	_fireCount = 0;

	return S_OK;
}

void Rifle::update()
{
	SetRenderPos();
	FireBullet();
}

void Rifle::SetRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();
	_yFrame = playerIsLeft ? 0 : 1;
	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 30 : 50);

	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
}

void Rifle::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void Rifle::release()
{
}

void Rifle::FireBullet()
{
	if (_isAttacking)
	{
		_fireCount++;

		if (_fireCount > 5)
		{
			if (!ENTITYMANAGER->getPlayer()->GetIsReload())
			{
				SOUNDMANAGER->play("무기_라이플");
				ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -10 + _angleCheckPosX + cosf(_angle) * 50, -20 + _angleCheckPosY - sinf(_angle) * 50, _angle,
					10, 22, 1000, true, _angle);

				if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
				{
					Bullet* bullet2 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -10 + _angleCheckPosX + cosf(_angle) * 50, -20 + _angleCheckPosY - sinf(_angle) * 50,
						_angle - PI / 12, 10, 22, 1000, true, _angle - PI / 24);

					Bullet* bullet3 = ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -10 + _angleCheckPosX + cosf(_angle) * 50, -20 + _angleCheckPosY - sinf(_angle) * 50,
						_angle + PI / 12, 10, 22, 1000, true, _angle + PI / 24);
				}
				ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);

				_curNumOfBullet--;
			}
			_fireCount = 0;
		}
	}
	if (_curNumOfBullet == 0)
	{
		_isAttacking = false;
	}
}

void Rifle::Activate()
{
	_isAttacking = true;
}