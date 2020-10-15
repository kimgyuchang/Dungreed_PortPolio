#include "stdafx.h"
#include "DemonSword.h"

HRESULT DemonSword::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name,
	string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed,
	int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet,
	float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_isRenderFirst = true;
	_animCount = 0;
	_finalAnimCount = 0;
	_slashImage = IMAGEMANAGER->findImage("DemonSword_Slash");
	_renderScale = 3.0f;
	return S_OK;
}

void DemonSword::update()
{
	SetBaseRenderPos();
	AttackAnim();
	SlashUpdater();
}

void DemonSword::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle + _renderAngle);
	for (int i = 0; i < _vSlashes.size(); i++) _vSlashes[i]->render(hdc);
}

void DemonSword::release()
{

}

void DemonSword::AttackAnim()
{
	_animCount++;

	if (_isAttacking)
	{
		if (_animCount < _finalAnimCount / 3)
		{
			if (_animCount == _renderFrontCount) _isRenderFirst = false;
			_renderAngle = getLerpByAmount(_renderAngle, _isLeftAttack ? PI : -PI, 0.5f);
		}

		else if (_animCount < _finalAnimCount / 3 * (1.5))
		{
		}

		else
		{
			_renderAngle = getLerpByAmount(_renderAngle, 0, 0.2f);

			if (_animCount >= _finalAnimCount)
			{
				_isAttacking = false;
				_renderAngle = 0;
				_isRenderFirst = true;
			}
		}
	}
}

void DemonSword::Activate()
{
	_isAttacking = true;
	_animCount = 0;
	_finalAnimCount = ENTITYMANAGER->getPlayer()->GetRealAttackSpeed();
	_renderFrontCount = _finalAnimCount * 0.2f;
	if (ENTITYMANAGER->getPlayer()->GetIsLeft()) _isLeftAttack = true;
	else _isLeftAttack = false;
	_renderAngle = 0;

	DemonSlash* slash = new DemonSlash();
	
	slash->init(GetAngleCheckPosX() - _slashImage->getFrameWidth()/2 * 3, GetAngleCheckPosY() - _slashImage->getFrameHeight()/2 * 3, _isLeftAttack ? 0 : 1, "DemonSword_Slash", -(_angle + (_isLeftAttack ? PI : -PI )));
	slash->_parent = this;
	_vSlashes.push_back(slash);
}

void DemonSword::SlashUpdater()
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

void DemonSword::ChangeMap()
{
	_vSlashes.clear();
}

void DemonSword::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 40 : 20);
	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2 * 3;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2 * 3;
	if (!_isAttacking)
	{
		_angle = getAngle(CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), _angleCheckPosY, _angleCheckPosX, CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		SetAngleInBoundary(_angle);
	}
}

void DemonSlash::init(float x, float y, int frameY, string imgName, float angle)
{
	_x = x;
	_y = y;
	_angle = SetAngleInBoundary(angle);

	_frameY = frameY;
	_radius = 180;

	_effect = EFFECTMANAGER->AddEffect(_x, _y, imgName, 6, 0, _frameY, false, 255, -_angle, 3.0f, 3.0f);
}

void DemonSlash::update()
{
	SetCollide();
}

void DemonSlash::render(HDC hdc)
{
}

void DemonSlash::SetCollide()
{
	if (_effect->GetFrameX() == 0 && _effect->GetAnimTimer() == 0)
	{
		vector<Object*> _vObjs = MAPMANAGER->GetPlayMap()->GetObjects();
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (UTIL::interactRectArc(_vObjs[i]->GetBody(), POINT{ (LONG)_parent->GetAngleCheckPosX(), (LONG)_parent->GetAngleCheckPosY() }, _radius, _angle - PI * 0.2f, _angle + PI * 0.2f, _radius /2))
				{
					_vObjs[i]->GetDamage();
				}
			}
		}
	}
}
