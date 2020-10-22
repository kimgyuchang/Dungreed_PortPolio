#include "stdafx.h"
#include "Rapier.h"

HRESULT Rapier::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_isRenderFirst = true;
	_slashImage = IMAGEMANAGER->findImage("RapierEffect");
	_baseAngle = 0;
	_count = 0;
	
	return S_OK;
}

void Rapier::update()
{
	Item::update();
	SlashUpdater();
	if (_isAttacking)
	{
		this->Shot();
	}
}

void Rapier::render(HDC hdc)
{
	CAMERAMANAGER->FrameRender(hdc, _vImages[0], _renderPosX, _renderPosY, 0, _yFrame, _angle + _baseAngle);
	for (int i = 0; i < _vSlashes.size(); i++) _vSlashes[i]->render(hdc);
}

void Rapier::Activate()
{
	SOUNDMANAGER->play("무기_레이피어");
	_renderAngle = 0;
	_isAttacking = true;

	RapierEffect* slash = new RapierEffect();

	slash->init(GetAngleCheckPosX() - _slashImage->getFrameWidth(), GetAngleCheckPosY() - _slashImage->getFrameHeight(), _slashImage->getKey(), (_angle));
	slash->_parent = this;

	_vSlashes.push_back(slash);
}

void Rapier::Shot()
{
	_count++;

	_renderPosX = _renderPosX + cosf(_angle) * 20;
	_renderPosY = _renderPosY - sinf(_angle) * 20;

	if (_count > 10)
	{
		_isAttacking = false;
		_count = 0;
	}
}

void Rapier::SlashUpdater()
{
	for (int i = 0; i < _vSlashes.size(); i++)
	{
		_vSlashes[i]->update();
		if (_vSlashes[i]->GetEffect()->GetIsDead())
		{
			_vSlashes.erase(_vSlashes.begin() + i);
			i--;
		}
	}
}

void Rapier::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();
	_baseAngle < 0 ? _yFrame = 1 : _yFrame = 0;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 25 : 50);
	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 50;
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

void Rapier::ChangeMap()
{
	_vSlashes.clear();
}

void RapierEffect::init(float x, float y, string imgName, float angle)
{
	_x = x;
	_y = y;
	_angle = SetAngleInBoundary(angle);

	int posX, posY;
	if (ENTITYMANAGER->getPlayer()->GetIsLeft())
	{
		posX = 280;
		posY = 240;
	}
	else
	{
		posX = 200;
		posY = 240;
	}
	_radius = 180;

	_effect = EFFECTMANAGER->AddEffect(_x + posX, _y + posY, imgName, 6, 0, 0, false, 255, _angle);
}

void RapierEffect::update()
{
	SetCollide();
}

void RapierEffect::render(HDC hdc)
{
}

void RapierEffect::SetCollide()
{
	if (_effect->GetFrameX() == 0 && _effect->GetAnimTimer() == 0)
	{
		vector<Object*> _vObjs = MAPMANAGER->GetPlayMap()->GetObjects();
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (UTIL::interactRectArc(_vObjs[i]->GetBody(), POINT{ (LONG)_parent->GetAngleCheckPosX(), (LONG)_parent->GetAngleCheckPosY() }, _radius, _angle - PI * 0.1f, _angle + PI * 0.1f, _radius / 2))
				{
					_vObjs[i]->GetDamage();
				}
			}
		}
	}
}