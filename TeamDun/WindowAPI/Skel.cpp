#include "stdafx.h"
#include "Skel.h"

HRESULT Skel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 42, 57);
	_state = ES_IDLE;
	_index = _count = 0;
	_frameX, _frameY = 0;
	_isLeft = false;

	return S_OK;
}

void Skel::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200)
			{
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)
			{
				_isLeft = true;
				_x += 3;
			}
			else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)
			{
				_isLeft = false;
				_x -= 3;
			}
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 < _x && ENTITYMANAGER->getPlayer()->GetX() + 70 > _x)
			{
				_state = ES_ATTACK;
				if (_x < ENTITYMANAGER->getPlayer()->GetX() + 20)
				{
					_isLeft = true;
				}
				else
				{
					_x = _x - 65;
					_isLeft = false;
				}
			}
			break;
		case ES_ATTACK:
			break;
		default:
			break;
		}
		this->Animation();
	}
}

void Skel::release()
{
}

void Skel::render(HDC hdc)
{

	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Skel::Move()
{
	Enemy::Move();
}

void Skel::Attack()
{
	Enemy::Attack();
}

void Skel::Animation()
{
	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
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
		_useImage = 0;
		if (_isLeft)
		{
			_frameY = 1;
		}
		else
		{
			_frameY = 0;
		}
		break;
	default:
		break;
	}
}
