#include "stdafx.h"
#include "GreatBow.h"

HRESULT GreatBow::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);
	_isRenderFirst = false;
	_isReady = false;
	_isBowSound = false;
	_range = 350;
	_Power = 0;
	_Speed = 5;
	return S_OK;
}

void GreatBow::update()
{
	SetBaseRenderPos();
	FireBullet();
	AttackAnim();

}

void GreatBow::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
}

void GreatBow::release()
{

}

void GreatBow::FireBullet()
{

	if (_isReady)
	{
		
		_range += 10;
		_Power+=1;
		_Speed+= 0.5f;
		if (_Speed > 35)
		{
			_Speed = 35;
		}
		
		if (_Power > 25)
		{
			_Power = 25;
		}
		
		if (INPUT->GetIsLButtonUp())
		{
			SOUNDMANAGER->play("무기_활발사");
		
			Bullet* bullet = ENTITYMANAGER->makeBullet("SkelArrow", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle,
				_Power, _Speed, _range, true, _angle, BST_CHARGE);
			bullet->SetUseTraceParticle(true);
			if (ENTITYMANAGER->getPlayer()->GetIsEquipMulti())
			{

				Bullet* bullet2 = ENTITYMANAGER->makeBullet("SkelArrow", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle- PI / 12,
					_Power, _Speed, _range, true, _angle- PI / 12, BST_CHARGE);
				bullet2->SetUseTraceParticle(true);
				Bullet* bullet3 = ENTITYMANAGER->makeBullet("SkelArrow", "BulletEffect01", BT_PLAYER, -20 + _angleCheckPosX + cosf(_angle) * 50, -30 + _angleCheckPosY - sinf(_angle) * 50, _angle+ PI / 12,
					_Power, _Speed, _range, true, _angle + PI / 12, BST_CHARGE);
				bullet3->SetUseTraceParticle(true);
			}
			_isReady = false;
			_Power = 0;
			_Speed = 10;
			_xFrame = 4;
			_range = 350;
			_isBowSound = false;
		}
	}

}

void GreatBow::AttackAnim()
{
	if (_isReady)
	{
		_frameTimer++;
		if (_frameTimer > 10)
		{
			_xFrame++;
			if (_xFrame == 1)
			{
				if (!_isBowSound)
				{
					SOUNDMANAGER->play("몬스터_궁수_쭈욱");
					_isBowSound = true;

				}
			}
			if (_xFrame > 3)
			{
				_xFrame = 3;
			}
		}
	}
	else
	{
		_xFrame = 0;
	}

}

void GreatBow::Activate()
{

	_isReady = true;

}

void GreatBow::ActivateAlways()
{

}

void GreatBow::SetBaseRenderPos()
{

	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//플레이어 왼쪽인지


	 _angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 10 : 60);

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
