#include "stdafx.h"
#include "Banshee.h"

HRESULT Banshee::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_Damage = 8;
	_isAtk = false;
	_initHp = _hp = 50;
	_attackCoolTime = RANDOM->range(200) + 250;
	return S_OK;
}

void Banshee::update()
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

void Banshee::release()
{
}

void Banshee::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Banshee::Attack()
{
	if (!_isAtk)
	{
		_attackCoolTime--;
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
			SOUNDMANAGER->play("¸ó½ºÅÍ_¹ê½Ã");
		}
	}
}

void Banshee::Animation()
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
						ENTITYMANAGER->makeBullet("BansheeBulletIdle", "BansheeBulletHit", BT_NOCOL, _x, _y, PI / 6 * i,_Damage,
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
					for(int i = 0 ;i < 12 ; i++)
					ENTITYMANAGER->makeBullet("BansheeBulletIdle", "BansheeBulletHit", BT_NOCOL , _x , _y,PI/6*i ,_Damage, 4, 1000 , true);
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
