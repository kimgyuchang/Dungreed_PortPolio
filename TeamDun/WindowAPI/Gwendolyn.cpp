#include "stdafx.h"
#include "Gwendolyn.h"

HRESULT Gwendolyn::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_isRenderFirst = true;
	_slashImage = IMAGEMANAGER->findImage("GwendolynEffect");
	_baseAngle = 0;
	_count = 0;

	return S_OK;
}

void Gwendolyn::update()
{
	Item::update();
	SlashUpdater();
	if (_isAttacking)
	{
		this->Shot();
	}
}

void Gwendolyn::render(HDC hdc)
{
	CAMERAMANAGER->FrameRender(hdc, _vImages[0], _renderPosX, _renderPosY, 0, _yFrame, _angle + _baseAngle);
	for (int i = 0; i < _vSlashes.size(); i++) _vSlashes[i]->render(hdc);
}

void Gwendolyn::Shot() 
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

void Gwendolyn::Activate()
{
	SOUNDMANAGER->play("¸Û¸ÛÀÌ ¿Ð¿Ð");
	_renderAngle = 0;
	_isAttacking = true;

	GwendolynEffect* slash = new GwendolynEffect();

	slash->init(GetAngleCheckPosX() - _slashImage->getFrameWidth(), GetAngleCheckPosY() - _slashImage->getFrameHeight(), _slashImage->getKey(), (_angle));
	slash->_parent = this;

	_vSlashes.push_back(slash);
}

void Gwendolyn::SlashUpdater()
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

void Gwendolyn::SetBaseRenderPos()
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

void Gwendolyn::ChangeMap()
{
	_vSlashes.clear();
}

void GwendolynEffect::init(float x, float y, string imgName, float angle)
{
	_x = x;
	_y = y;
	_angle = SetAngleInBoundary(angle);

	_radius = 180;

	_effect = EFFECTMANAGER->AddEffect(_x, _y, imgName, 6, 0, 0, false, 255, _angle, 2, 2);
}

void GwendolynEffect::update()
{
	SetCollide();
}

void GwendolynEffect::render(HDC hdc)
{
}

void GwendolynEffect::SetCollide()
{
	if (_effect->GetFrameX() == 0 && _effect->GetAnimTimer() == 0)
	{
		vector<Object*> _vObjs = MAPMANAGER->GetPlayMap()->GetObjects();
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (UTIL::interactRectArc(_vObjs[i]->GetBody(), POINT{ (LONG)_parent->GetAngleCheckPosX(), (LONG)_parent->GetAngleCheckPosY() }, _radius, _angle - PI * 0.1f, _angle + PI * 0.1f, _radius))
				{
					_vObjs[i]->GetDamage();
				}
			}
		}
	}
}