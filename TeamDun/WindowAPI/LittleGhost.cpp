#include "stdafx.h"
#include "LittleGhost.h"

HRESULT LittleGhost::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);

	_state = ES_IDLE;

	_index = _count = _attackCoolTime = _attackTime = 0;
	_frameX, _frameY = 0;

	_isLeft = false;

	return S_OK;
}

void LittleGhost::update()
{
	Enemy::update();

	_attackCoolTime++;
	_attackTime++;

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (_attackCoolTime % 100 == 0)
			{
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 200)
			{
				_state = ES_ATTACK;
			}
			break;
		case ES_ATTACK:
			this->Attack();
			if (_attackTime % 100 == 0)
			{
				_state = ES_IDLE;
			}
			break;
		default:
			break;
		}
		this->Animation();
		this->Move();
	}
	SetBodyPos();
}

void LittleGhost::release()
{
}

void LittleGhost::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void LittleGhost::Move()
{
	Enemy::Move();

	_x += cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
	_y += -sinf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
}

void LittleGhost::Attack()
{
	Enemy::Attack();

	_x += 2 * cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
	_y += 2 * -sinf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
}

void LittleGhost::Animation()
{
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
		_useImage = 0;
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
	default:
		break;
	}
}

void LittleGhost::pixelCollision()
{
}