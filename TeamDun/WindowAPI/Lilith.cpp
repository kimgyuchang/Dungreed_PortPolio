#include "stdafx.h"
#include "Lilith.h"

HRESULT Lilith::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 78, 78);
	_initHp = _hp = 50;
	_state = ES_IDLE;
	_count = _attackTimer = _attackCoolTime = 0;
	_isLeft = _isAttack = false;
	_isHit = false;
	_hitCount = 0;
	_Damage = 10;
	return S_OK;
}

void Lilith::update()
{
	Enemy::update();


	if (_isSpawned)
	{
		this->Animation();

		if (_x > ENTITYMANAGER->getPlayer()->GetX() + 60)
		{
			_isLeft = true;
		}
		if (_x < ENTITYMANAGER->getPlayer()->GetX() - 20)
		{
			_isLeft = false;
		}

		switch (_state)
		{
		case ES_IDLE:
			_renderOrder = 1;
			if (_isHit)
			{
				_hitCount++;

				if (_hitCount > 50)
				{
					_hitCount = 0;
					_isHit = false;
				}
			}
			this->Move();
			RECT temp;
			if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
			{
				if (_isHit == false)
				{
					ENTITYMANAGER->getPlayer()->GetHitDamage(_Damage);
					ENTITYMANAGER->getPlayer()->SetIsStun(true);
					_state = ES_ATTACK;
					_isAttack = true;
					_isHit = true;

				}

			}
			break;

		case ES_MOVE:
			//충돌처리

			break;

		case ES_ATTACK:

			_renderOrder = 2;
			_attackTimer++;

			if (!_isLeft)
			{
				_x = ENTITYMANAGER->getPlayer()->GetX() - 25;
				_y = ENTITYMANAGER->getPlayer()->GetY() + 10;
				_body = RectMake(_x, _y, 78, 78);
			}
			else
			{
				_x = ENTITYMANAGER->getPlayer()->GetX() + 40;
				_y = ENTITYMANAGER->getPlayer()->GetY() + 10;
				_body = RectMake(_x, _y, 78, 78);
			}

			if (_attackTimer > 50)
			{

				_attackTimer = 0;
				_isAttack = false;
				_state = ES_IDLE;

			}
			break;
		default:
			break;
		}
	}
}

void Lilith::release()
{
	Enemy::release();
}

void Lilith::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Lilith::Move()
{
	Enemy::Move();
	_body = RectMake(_x, _y, 78, 78);
	_x += 2 * cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
	_y += 2 * -sinf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
}

void Lilith::Attack()
{



}

void Lilith::Animation()
{
	Enemy::Animation();
	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		break;
	case ES_MOVE:
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	case ES_ATTACK:
		_useImage = 2;
		if (_isLeft)
		{
			_frameY = 1;
			if (_count > 15)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count > 15)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	default:
		break;
	}
}