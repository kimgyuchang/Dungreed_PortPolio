#include "stdafx.h"
#include "abyssBanshee.h"

HRESULT AbyssBanshee::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_damage = 12;
	_isAtk = false;
	_initHp = _hp = 100;
	_attackCoolTime = RANDOM->range(200) + 250;
	return S_OK;
}

void AbyssBanshee::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		Animation();
		Attack();
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
		else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
	}
}

void AbyssBanshee::release()
{
}

void AbyssBanshee::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void AbyssBanshee::Attack()
{
	if (!_isAtk)
	{
		_attackCoolTime--;

		if (_attackCoolTime == 100) CheckNewPos();

		if (_attackCoolTime < 0)
		{
			_attackCoolTime = RANDOM->range(200) + 250;
			_isAtk = true;
			_useImage = 1;
			if (_isLeft)
			{
				_frameX = 0;
				_leftAtk = true;
			}
			else
			{
				_frameX = _vImages[_useImage]->getMaxFrameX();
				_leftAtk = false;
			}
			_state = ES_ATTACK;
			SOUNDMANAGER->play("몬스터_밴시");
		}
	}
}

/// <summary>
/// 새로운 위치를 정해준다.
/// </summary>
void AbyssBanshee::CheckNewPos()
{
	EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameWidth() / 2, _y + _vImages[0]->getFrameHeight() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameHeight() / 2, "DieEffect", 3, 0, 0, false, 255, 0, 1, 1, false);

	while (true)
	{
		_x = RANDOM->range(MAPMANAGER->GetPlayMap()->GetMapSizeX() * 48);
		_y = RANDOM->range(MAPMANAGER->GetPlayMap()->GetMapSizeY() * 48);
		_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());

		COLORREF color1 = GetFastPixel(MAPMANAGER->GetPixelGetter(), _body.left, _body.top);
		COLORREF color2 = GetFastPixel(MAPMANAGER->GetPixelGetter(), _body.left, _body.bottom);
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), _body.right, _body.top);
		COLORREF color4 = GetFastPixel(MAPMANAGER->GetPixelGetter(), _body.right, _body.bottom);
		
		if (color1 != RGB(255, 0, 0) && color2 != RGB(255, 0, 0) && color3 != RGB(255, 0, 0) && color4 != RGB(255, 0, 0))
		{
			break;
		}
	}
	
	EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameWidth() / 2, _y + _vImages[0]->getFrameHeight() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameHeight() / 2, "DieEffect", 3, 0, 0, false, 255, 0, 1, 1, false);
}

void AbyssBanshee::Animation()
{
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
			_count++;

			_frameY = 0;
			if (_count % 5 == 0)
			{
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_count++;

			_frameY = 1;
			if (_count % 5 == 0)
			{
				_frameX--;
				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	case ES_MOVE:
		_useImage = 0;
		if (_isLeft)
		{
			_count++;
			_frameY = 0;
			if (_count % 5 == 0)
			{
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_count++;
			_frameY = 1;
			if (_count % 5 == 0)
			{
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	case ES_ATTACK:
		if (_leftAtk)
		{
			_count++;
			_frameY = 0;
			if (_count % 10 == 0)
			{
				_frameX++;
				if (_frameX == _vImages[_useImage]->getMaxFrameX() / 2)
				{
					for (int i = 0; i < 12; i++)
						ENTITYMANAGER->makeBullet("BansheeBulletIdle", "BansheeBulletHit", BT_NOCOL, _x, _y, PI / 6 * i, _damage,
							4, 1000, true);
				}
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
					_state = ES_IDLE;
					_isAtk = false;
				}
			}
		}
		else
		{
			_count++;
			_frameY = 1;
			if (_count % 10 == 0)
			{
				_frameX--;
				if (_frameX == _vImages[_useImage]->getMaxFrameX() / 2)
				{
					for (int i = 0; i < 12; i++)
						ENTITYMANAGER->makeBullet("BansheeBulletIdle", "BansheeBulletHit", BT_NOCOL, _x, _y, PI / 6 * i, _damage, 4, 1000, true);
				}
				if (_frameX < 0)
				{
					_frameX = 0;
					_state = ES_IDLE;
					_isAtk = false;
				}
			}
		}
		break;
	default:
		break;
	}
}
