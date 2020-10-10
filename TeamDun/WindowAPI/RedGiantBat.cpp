#include "stdafx.h"
#include "RedGiantBat.h"

HRESULT RedGiantBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_isAtk = false;
	_ReadyBullet = false;
	_bulletStop = false;
	_ReadyBulletTime = 0;
	_bulletCount = 0;
	_hp = 50;
	_angle = 0;
	return S_OK;
}

void RedGiantBat::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		
		Animation();
		if (_vBatBullet.size() == 0)
		{
			_isAtk = false;
			_bulletStop = false;
		}
		switch (_state)
		{
		case ES_IDLE:

			if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
			else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
			
			Attack();
			
			break;
		case ES_ATTACK:
			break;
		default:
			break;
		}

		for (int i = 0; i < _vBatBullet.size(); i++)
		{
			if (_vBatBullet[i]->getIsDead() == true)
			{
				_vBatBullet.erase(_vBatBullet.begin() + i);
			}
		}

		
	}
}

void RedGiantBat::release()
{
}

void RedGiantBat::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
		
	}
}

void RedGiantBat::Attack()
{
	if (!_isAtk && !_bulletStop)
	{
		_attackCoolTime++;

		if (_attackCoolTime > 200)
		{
			_attackCoolTime = 0;
			_isAtk = true;
			_ReadyBullet = true;
		}
	}

	if (_ReadyBullet)
	{
		
		_ReadyBulletTime++;
		if (_ReadyBulletTime >5)
		{
			image* ig = _vImages[_useImage];
			_ReadyBulletTime = 0;
			Bullet* bullet = ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x+ig->getFrameWidth()/2-20, _y+ig->getFrameHeight()/2-20,
				_angle, 10, 1500, true);
			_vBatBullet.push_back(bullet);
			_angle += PI / 9;
		}

		if (_vBatBullet.size() == 18)
		{
			_angle = 0;
			_ReadyBullet = false;
		}
	}
	if (_bulletStop == false)
	{
		_shootCount = 0;
		for (int i = 0; i < _vBatBullet.size(); i++)
		{
			if (getDistance(_vBatBullet[i]->getStartX(), _vBatBullet[i]->getStartY(), _vBatBullet[i]->getX(), _vBatBullet[i]->getY()) > 100)
			{
				_vBatBullet[i]->SetSpeed(0);

			}
			if (_vBatBullet[i]->getSpeed() == 0)
			{
				_shootCount++;
			}
			if (_shootCount == 18)
			{
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
				_bulletStop = true;
			}
		}
	}
	
	
}

void RedGiantBat::Animation()
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
					
					for (int i = 0; i < _vBatBullet.size(); i++)
					{
						
						_vBatBullet[i]->SetAngle(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
						_vBatBullet[i]->SetSpeed(8);
						
					}
					
				}
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
					_state = ES_IDLE;
					
					
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

					for (int i = 0; i < _vBatBullet.size(); i++)
					{
						
						_vBatBullet[i]->SetAngle(getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()));
						_vBatBullet[i]->SetSpeed(8);
					}
				}
				if (_frameX < 0)
				{
					_frameX = 0;
					_state = ES_IDLE;
					
				
				}
			}
		}
		break;
	default:
		break;
	}

}

void RedGiantBat::SetIsDead(bool isDead)
{
	_isDead = isDead;
	if (_isDead == true)
	{
		for (int i = 0; i < _vBatBullet.size(); i++)
		{
			if (_vBatBullet[i]->getSpeed() == 0)
			{
				EFFECTMANAGER->AddEffect(_vBatBullet[i]->getX(), _vBatBullet[i]->getY(), _vBatBullet[i]->getEffectIgName(), 4, 0, 0, false, 255);
				_vBatBullet[i]->SetIsDead(true);

			}
		}
	}
}

