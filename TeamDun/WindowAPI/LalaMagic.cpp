#include "stdafx.h"
#include "LalaMagic.h"

HRESULT LalaMagic::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_animCount = 0;
	_finalAnimCount = 0;

	return S_OK;
}

void LalaMagic::update()
{
	SetBaseRenderPos();
	FireBullet();

}

void LalaMagic::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void LalaMagic::release()
{
}

void LalaMagic::FireBullet()
{
	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{

			SOUNDMANAGER->play("¹«±â_±ÇÃÑ");
			ENTITYMANAGER->makeBullet("Bullet01", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle,
				10, 22, 1000, true, _angle);
			ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);


			_curNumOfBullet--;

		}
		_isAttacking = false;
	}

}

void LalaMagic::AttackAnim()

{

}

void LalaMagic::Activate()
{
	_isAttacking = true;
}



