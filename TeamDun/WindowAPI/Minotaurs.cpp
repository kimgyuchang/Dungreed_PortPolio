#include "stdafx.h"
#include "Minotaurs.h"

HRESULT Minotaurs::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 156, 114);
	_state = ES_IDLE;

	_index = _count = _dashTimer = _movePoint = _attackCoolTime = _attackCount = _attackIndexFix = 0;
	_frameX, _frameY = 0;

	_moveSpeed = 10;
	_isLeft = _isAttack = _isDash = false;

	_attackAnimFrame = vector<int>{ 3,3,30,5,5,5,5 };

	return S_OK;
}

void Minotaurs::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			_attackCoolTime++;

			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 300 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100)
			{
				if (_attackCount <= 0)
				{
					_state = ES_MOVE;
				}
				else if (_attackCount >= 1)
				{
					if (_attackCoolTime > 100)
					{
						_state = ES_MOVE;
						_attackCoolTime = 0;
					}
				}

				if (_x < ENTITYMANAGER->getPlayer()->GetX()) { _moveSpeed = 10; _isLeft = true; }
				else if (_x >= ENTITYMANAGER->getPlayer()->GetX()) { _moveSpeed = -10; _isLeft = false; }
			}
			break;
		case ES_MOVE:

			this->Move();

			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				_state = ES_ATTACK;
				_frameX = 0;
			}
			else if (!_isLeft && _frameX <= 0)
			{
				_state = ES_ATTACK;
				_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
			}
			break;
		case ES_ATTACK:
			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				_state = ES_IDLE;
				_attackCount++;
			}
			else if (!_isLeft && _frameX <= 0)
			{
				_state = ES_IDLE;
				_attackCount++;
			}
			break;
		default:
			break;
		}
	}

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

	_movePoint++;
	_dashTimer++;
	_isDash = true;

	if (_isDash)
	{
		_x += _moveSpeed;

		if (_dashTimer > 100)
		{
			_dashTimer = 0;
			_isDash = false;
		}
	}

	if (_movePoint > 100) // 혹은 충돌했을떄
	{
		_state = ES_ATTACK;
		if (_moveSpeed > 0)
		{
			_frameX = 0;
		}
		else
		{
			_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
		}
		_movePoint = 0;
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

			if (_frameX == 4)
			{
				if (_count > 5)
				{
					_frameX = 4;
					_count = 0;

					if (_frameX > _vImages[_useImage]->getMaxFrameX())
					{
						_frameX = 0;
					}
				}
			}
			else
			{
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
		}
		else
		{
			_frameY = 1;
			if (_frameX == 3)
			{
				if (_count > 5)
				{
					_count = 0;
					_frameX = 3;

					if (_frameX < 0)
					{
						_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
					}
				}
			}
			else
			{
				if (_count > 5)
				{
					_count = 0;
					_frameX--;

					if (_frameX < 0)
					{
						_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
					}
				}
			}
		}
		break;
	case ES_ATTACK:
		_useImage = 2;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count > _attackAnimFrame[_frameX])
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
			if (_count > _attackAnimFrame[_vImages[_useImage]->getMaxFrameX() - _frameX])
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
					_attackIndexFix = 0;
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