#include "stdafx.h"
#include "Lilith.h"

HRESULT Lilith::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 78, 78);

	_state = ES_IDLE;
	_count = _attackTimer = _attackCoolTime = 0;
	_isLeft = _isAttack = false;

	return S_OK;
}

void Lilith::update()
{
	Enemy::update();

	this->Animation();
	this->Move();
	this->Attack();

	if (cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY())) < 0)
	{
		_isLeft = true;
	}
	else if (cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY())) >= 0)
	{
		_isLeft = false;
	}

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			break;

		case ES_MOVE:
			if (_x >= ENTITYMANAGER->getPlayer()->GetX() && _x <= ENTITYMANAGER->getPlayer()->GetX() + 56 && _y >= ENTITYMANAGER->getPlayer()->GetY() && _y <= ENTITYMANAGER->getPlayer()->GetY())
			{
				_state = ES_ATTACK;
				_isAttack = true;
				_x = ENTITYMANAGER->getPlayer()->GetX() - 10;
				_y = ENTITYMANAGER->getPlayer()->GetY() + 10;
			}
			break;

		case ES_ATTACK:
			_attackTimer++;
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
	Enemy::Attack();
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
			if (_count % 5 == 0)
			{
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
			if (_count % 5 == 0)
			{
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
		_useImage = 2;
		if (_isLeft)
		{
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
	default:
		break;
	}
}