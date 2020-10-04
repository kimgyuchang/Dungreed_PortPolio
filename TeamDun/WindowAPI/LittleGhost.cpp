#include "stdafx.h"
#include "LittleGhost.h"

HRESULT LittleGhost::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);

	_state = ES_IDLE;

	_index = _count = 0;
	_frameX, _frameY = 0;

	_isLeft = false;

	return S_OK;
}

void LittleGhost::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		// this->Move();
		this->Animation();
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
	if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) > 10 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) > 10)
	{
		if (_isLeft)
		{
			_x += 3;

			if (_y < ENTITYMANAGER->getPlayer()->GetY())
			{
				_y += 3;
			}
			else
			{
				_y -= 3;
			}
		}
		else
		{
			_x -= 3;

			if (_y < ENTITYMANAGER->getPlayer()->GetY())
			{
				_y += 3;
			}
			else
			{
				_y -= 3;
			}
		}
	}
}

void LittleGhost::Attack()
{
	Enemy::Attack();
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