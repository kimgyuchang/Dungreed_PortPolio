#include "stdafx.h"
#include "BowSkel.h"

HRESULT BowSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	_state = ES_IDLE;
	_stateTimer = 0;
	_isAtk = false;
	_initHp = _HP = 30;
	_skelBow.bowIg = IMAGEMANAGER->findImage("SkelBow");
	_skelBow.frameX = 0;
	_skelBow.frameY = 0;
	_skelBow.angle = 0.f;
	_attackCoolTime = 150 + RANDOM->range(200);

	_Damage = 10;
	return S_OK;
}

void BowSkel::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		if (getDistance(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY()) < 600)
		{
			_skelBow.angle = getAngle(_x, _y, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
		}
		Animation();
		
		Attack();
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
		else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
	}
}

void BowSkel::release()
{
	Enemy::release();
}

void BowSkel::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
		CAMERAMANAGER->FrameRender(hdc,_skelBow.bowIg, _x, _y + 20,_skelBow.frameX,_skelBow.frameY, _skelBow.angle);
	}
}


void BowSkel::Attack()
{
	if (!_isAtk)
	{
		_attackCoolTime--;
		if (_attackCoolTime < 0)
		{
			_attackCoolTime = 150 + RANDOM->range(200);
			_isAtk = true;
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
		}
	}
}

void BowSkel::Animation()
{
	if (_isLeft)
	{
		_frameY = 0;
	}
	else
	{
		_frameY = 1;
	}
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		

		break;

		
	case ES_ATTACK:


		

		_count++;

		
		if (_count % 10 == 0)
		{

			_skelBow.frameX++;
			if (_skelBow.frameX == 3)
			{
				ENTITYMANAGER->makeBullet("SkelArrow", "BatBulletHit", BT_NOMAL, _x, _y+20,
					_skelBow.angle,_Damage,10, 1000, true ,_skelBow.angle);
			}
			if (_skelBow.frameX > _skelBow.bowIg->getMaxFrameX())
			{
				_skelBow.frameX = 0;

				_state = ES_IDLE;
				_isAtk = false;
			}
		}


		break;
	default:
		break;
	}
}


