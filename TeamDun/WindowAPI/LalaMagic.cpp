#include "stdafx.h"
#include "LalaMagic.h"

HRESULT LalaMagic::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_animCount = 0;
	_finalAnimCount = 0;
	_renderAngle = -PI / 6;
	return S_OK;
}

void LalaMagic::update()
{
	_skill->update();
	SetBaseRenderPos();
	FireBullet();
	DoSkill();
}

void LalaMagic::render(HDC hdc)
{
	CAMERAMANAGER->StretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _renderScale, _renderScale, _angle + _renderAngle);
}

void LalaMagic::release()
{
}

void LalaMagic::DoSkill()
{
	if (INPUT->GetKeyDown('Q'))
	{
		_skill->SetParent(this);
		_skill->Activate();
	}
}

void LalaMagic::FireBullet()
{
	if (_isAttacking)
	{
		if (!ENTITYMANAGER->getPlayer()->GetIsReload())
		{
			_renderAngle = _renderAngle < 0 ? PI / 2 : -PI / 6;
			
			SOUNDMANAGER->play("무기_라라의 요술봉");
			
			if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
			{
				Bullet* bullet1 = ENTITYMANAGER->makeBullet("StarBullet", "StarBulletFX", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle - PI/6,
					10, 10, 1500, true, _angle, BST_TRACE);
				bullet1->SetUseTraceImage("StarBulletParticle");
				bullet1->SetParticleTime(1);
				bullet1->SetUseTraceParticle(true);
				bullet1->SetTraceAlphaChanger(10);
				bullet1->SetUseWallCollision(false);
				Bullet* bullet2 = ENTITYMANAGER->makeBullet("StarBullet", "StarBulletFX", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle + PI/6,
					10, 10, 1500, true, _angle, BST_TRACE);
				bullet2->SetUseTraceImage("StarBulletParticle");
				bullet2->SetParticleTime(1);
				bullet2->SetUseTraceParticle(true);
				bullet2->SetTraceAlphaChanger(10);
				bullet2->SetUseWallCollision(false);
			}

			Bullet* bullet = ENTITYMANAGER->makeBullet("StarBullet", "StarBulletFX", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle,
				10, 10, 1500, true, _angle, BST_TRACE);
			bullet->SetUseTraceImage("StarBulletParticle");
			bullet->SetParticleTime(1);
			bullet->SetUseTraceParticle(true);
			bullet->SetTraceAlphaChanger(10);
			bullet->SetUseWallCollision(false);
			ENTITYMANAGER->getPlayer()->SetBulletCount(ENTITYMANAGER->getPlayer()->GetBulletCount() - 1);

			_curNumOfBullet--;
		}
		_isAttacking = false;
	}
}


void LalaMagic::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//플레이어 왼쪽인지
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 20 : 50);	//아이템 타입이 한손일때,각도체크용 중점에 플레이어의 x좌표+ 왼쪽인지 여부에따라 맞으면 +20,아니면 +40

	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;	//각도 체크용 중점에 플레이어의 Y좌표를 받아와서  +45만큼
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)	//공격중이 아니면
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

void LalaMagic::Activate()
{
	_isAttacking = true;
}



