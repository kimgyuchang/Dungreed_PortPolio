#include "stdafx.h"
#include "LittleGhost.h"

HRESULT LittleGhost::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);

	_state = ES_IDLE;

	_index = _count = _attackTime = _moveTimer = _moveCoolTime = 0;
	_frameX, _frameY = 0;
	_initHp = _HP = 15;
	_realMoveX, _realMoveY = 0;
	_Damage = 5;
	_isLeft = false;
	_isAtk = false;
	_attackCoolTime = RANDOM->range(20) + 20;
	return S_OK;
}

void LittleGhost::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		if (_realMoveX < 0)
		{
			_isLeft = false;
		}
		else if (_realMoveX >= 0)
		{
			_isLeft = true;
		}

		switch (_state)
		{
		case ES_IDLE:
			_attackCoolTime--;

			if (_attackCoolTime < 0)
			{
				_state = ES_MOVE;
				_attackCoolTime = RANDOM->range(20) + 20;
			}
			break;
		case ES_MOVE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 200)
			{
				GetNewMoveXY();
				_state = ES_ATTACK;
			}

			this->Move();
			break;
		case ES_ATTACK:
			_attackTime++;
			RECT temp;
			if (_isAtk == false)
			{
				_isAtk = true;
				if (IntersectRect(&temp,&ENTITYMANAGER->getPlayer()->GetBody(),&_body))
				{
					if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
					{
						float damage;
							float block;
							float evasion;

							damage = _Damage * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100;
							evasion = RANDOM->range(100);
							block = RANDOM->range(100);
						if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
						{
							if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
							{
								ENTITYMANAGER->getPlayer()->SetIsHit(true);
								ENTITYMANAGER->getPlayer()->SetHitCount(0);
								ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
							}
						}
					}
				} 
			}
			this->Attack();
			if (_attackTime > 100)
			{
				_isAtk = false;
				_state = ES_IDLE;
				_attackTime = 0;
			}
			break;
		default:
			break;
		}

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
		if (INPUT->GetKey(VK_F6)) CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void LittleGhost::GetNewMoveXY()
{
	_realMoveX = cosf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
	_realMoveY = -sinf(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
}

void LittleGhost::Move()
{
	Enemy::Move();

	_moveTimer++;

	if (_moveTimer > 100)
	{
		_moveTimer = 0;
		GetNewMoveXY();
	}


	_x += _realMoveX;
	_y += _realMoveY;

}

void LittleGhost::Attack()
{
	Enemy::Attack();

	_x += 2.5 * _realMoveX;
	_y += 2.5 * _realMoveY;
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
		_useImage = 0;
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
	default:
		break;
	}
}