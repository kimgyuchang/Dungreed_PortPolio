#include "stdafx.h"
#include "PurpleGiantBat.h"

HRESULT PurpleGiantBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_isAtk = false;
	_initHp = _HP = 80;
	_fireAngle = 0;

	_Damage = 11;
	return S_OK;
}

void PurpleGiantBat::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		
		Animation();
		Attack();
		switch (_state)
		{
		case ES_IDLE:
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
			else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
			break;
		case ES_MOVE:
			break;
		case ES_ATTACK:
			break;
		default:
			break;
		}
	
	}
}

void PurpleGiantBat::release()
{
}

void PurpleGiantBat::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void PurpleGiantBat::Attack()
{
	if (!_isAtk)
	{
		_attackCoolTime++;
		if (_attackCoolTime > 300)
		{
			_attackCoolTime = 0;
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
			_fireAngle = getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
		}
	}
}

void PurpleGiantBat::Animation()
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
				if (_frameX == 2)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x+_vImages[_useImage]->getFrameWidth()/2-20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI/12,_Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle+ PI / 12, _Damage,
						8, 1000, true);
					
				} 
				if (_frameX == 3)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI / 12, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle + PI / 12, _Damage,
						8, 1000, true);

				}
				if (_frameX == 4)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI / 12, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle + PI / 12, _Damage,
						8, 1000, true);

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
				if (_frameX == _vImages[_useImage]->getMaxFrameX()-2)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI / 12, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle + PI / 12, _Damage,
						8, 1000, true);

				}
				if (_frameX == _vImages[_useImage]->getMaxFrameX() - 3)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI / 12, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle + PI / 12, _Damage,
						8, 1000, true);

				}
				if (_frameX == _vImages[_useImage]->getMaxFrameX() - 4)
				{
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle - PI / 12, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle, _Damage,
						8, 1000, true);
					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x + _vImages[_useImage]->getFrameWidth() / 2 - 20, _y + _vImages[_useImage]->getFrameHeight() / 2 - 20,
						_fireAngle + PI / 12, _Damage,
						8, 1000, true);

				}
				if (_frameX < 0)
				{

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
