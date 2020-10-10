#include "stdafx.h"
#include "SwordSkel.h"

HRESULT SwordSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 42, 57);
	_frameX = _frameY = 0;
	_count = _index = 0;
	_state = ES_IDLE;

	return S_OK;
}

void SwordSkel::update()
{
	Enemy::update();

	switch (_state)
	{
	case ES_IDLE:
		break;
	case ES_MOVE:
		break;
	case ES_ATTACK:
		break;
	default:
		break;
	}
}

void SwordSkel::release()
{
	Enemy::release();
}

void SwordSkel::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void SwordSkel::Move()
{
	if (_isSpawned)
	{
		Enemy::Move();
	}
}

void SwordSkel::Attack()
{
	Enemy::Attack();
}

void SwordSkel::Animation()
{
	Enemy::Animation();

	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 1;
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

void SwordSkel::pixelCollision()
{
}