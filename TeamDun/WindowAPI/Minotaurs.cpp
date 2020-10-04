#include "stdafx.h"
#include "Minotaurs.h"

HRESULT Minotaurs::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 156, 114);
	_state = ES_IDLE;

	_index = _count = _dashTimer = _dashCount = _moveTimer = 0;
	_frameX, _frameY = 0;

	_moveSpeed = 15.0f;

	_isLeft = _isDash = _isAttack = false;
	return S_OK;
}

void Minotaurs::update()
{
	Enemy::update();

	_dashTimer++;
	_moveTimer++;

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 300 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100)
			{
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			if (ENTITYMANAGER->getPlayer()->GetX() > _x)
			{
				_isLeft = true;
			}
			else if (ENTITYMANAGER->getPlayer()->GetX() < _x)
			{
				_isLeft = false;
			}
			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				_state = ES_ATTACK;
			}
			else if (!_isLeft && _frameX <= 0)
			{
				_state = ES_ATTACK;
			}
			break;
		case ES_ATTACK:
			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				_state = ES_IDLE;
				_isDash = false;
				_dashCount = 0;
			}
			else if (!_isLeft && _frameX <= 0)
			{
				_state = ES_IDLE;
				_isDash = false;
				_dashCount = 0;
			}
			break;
		default:
			break;
		}
	}
	this->Move();
	this->Animation();
	this->pixelCollision();
}

void Minotaurs::release()
{
}

void Minotaurs::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Minotaurs::Move()
{
	Enemy::Move();
	if (_state == ES_MOVE)
	{
		_isDash = true;
	}
	if (_isDash && _dashCount == 0)
	{
		if (!_isLeft)
		{
			_x -= _moveSpeed;
			_dashCount++;
		}
		else if (_isLeft)
		{
			_x += _moveSpeed;
			_dashCount++;
		}
	}
}

void Minotaurs::Attack()
{
	Enemy::Attack();
}

void Minotaurs::Animation()
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

void Minotaurs::pixelCollision()
{
}
