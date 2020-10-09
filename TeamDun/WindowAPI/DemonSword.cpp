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
	_animCount = 0;
	_finalAnimCount = 0;
	_slashImage = IMAGEMANAGER->findImage("DemonSword_Slash");
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
	CAMERAMANAGER->FrameRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _angle + _renderAngle);
	for (int i = 0; i < _vSlashes.size(); i++) _vSlashes[i]->render(hdc);
	CAMERAMANAGER->TextDraw(hdc, _renderPosX, _renderPosY, to_string(_angle).c_str(), to_string(_angle).length());
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
	slash->init(GetAngleCheckPosX() - _slashImage->getFrameWidth()/2 * 3, GetAngleCheckPosY() - _slashImage->getFrameHeight()/2 * 3, _isLeftAttack ? 0 : 1, _slashImage, _angle);
	slash->_parent = this;
	_vSlashes.push_back(slash);
}

void DemonSword::SlashUpdater()
{
	for (int i = 0; i < _vSlashes.size(); i++)
	{
		_vSlashes[i]->update();
		if (_vSlashes[i]->_isDead)
		{
			_vSlashes.erase(_vSlashes.begin() + i);
			i--;
		}
	}
}

void DemonSlash::init(float x, float y, int frameY, image* img, int angle)
{
	_x = x;
	_y = y;
	_angle = angle;
	_image = img;
	_frameY = frameY;
	_animTimer = 0;
	_radius = 150;
	_frameX = 0;
	_isDead = false;
}

void DemonSlash::update()
{
	animation();
	SetCollide();
}

void DemonSlash::animation()
{
	if (!_isDead)
	{
		_animTimer++;
		if (_animTimer > 5)
		{
			_animTimer = 0;
			_frameX++;

			if (_frameX >= _image->getMaxFrameX())
			{
				_isDead = true;
			}
		}
	}
}

void DemonSlash::render(HDC hdc)
{
	CAMERAMANAGER->FrameStretchRender(hdc, _image, _x, _y, _frameX, _frameY, 3.0f, 3.0f, _angle);
	CAMERAMANAGER->TextDraw(hdc, _parent->GetAngleCheckPosX(), _parent->GetAngleCheckPosY(), "HERE", strlen("HERE"));

	CAMERAMANAGER->LineMake(hdc, _parent->GetAngleCheckPosX(), _parent->GetAngleCheckPosY(), _parent->GetAngleCheckPosX() + cos(_angle - PI * 0.2) * _radius, _parent->GetAngleCheckPosY() - sin(_angle - PI * 0.2) * _radius);
	CAMERAMANAGER->LineMake(hdc, _parent->GetAngleCheckPosX(), _parent->GetAngleCheckPosY(), _parent->GetAngleCheckPosX() + cos(_angle + PI * 0.2) * _radius, _parent->GetAngleCheckPosY() - sin(_angle + PI * 0.2) * _radius);
}

void DemonSlash::SetCollide()
{
	if (_frameX == 0 && _animTimer == 1)
	{
		vector<Object*> _vObjs = MAPMANAGER->GetPlayMap()->GetObjects();
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (UTIL::interactRectArc(_vObjs[i]->GetBody(), POINT{ (LONG)_parent->GetAngleCheckPosX(), (LONG)_parent->GetAngleCheckPosY() }, _radius, _angle - PI * 0.2, _angle + PI * 0.2))
				{
					_vObjs[i]->SetIsDead(true);
				}
			}
		}
	}
}
