#include "stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init()
{
	_particleTimer = 0;

	return S_OK;
}

void Bullet::update()
{
	speedTypeMove();
	moveBullet();
	Animation();
	GenerateTraceParticle();
	_distance = getDistance(_startX, _startY, _x, _y);
}

void Bullet::release()
{
}

void Bullet::render(HDC hdc)
{
	if (_isFrame)
	{
		CAMERAMANAGER->FrameRender(hdc, _ig, _x, _y, _frameX, _frameY,_igAngle);
	}

	else
	{
		CAMERAMANAGER->Render(hdc, _ig, _x, _y ,_igAngle);
	}

}

void Bullet::GenerateTraceParticle()
{
	if (_useTraceParticle)
	{
		_particleTimer--;
		if (_particleTimer < 0)
		{
			particle* curParticle = PARTICLEMANAGER->AddNewParticle();
			curParticle->initParticle(
				_x + _ig->getFrameWidth()/2,					// X좌표에 랜덤성 추가
				_y + _ig->getFrameHeight()/2,					// Y좌표에 랜덤성 추가
				0, 0,					// 스피드 XY 변화량
				0,						// X스피드 랜덤성 추가
				0,						// Y스피드 랜덤성 추가
				0,						// 각도값 변화량
				0,						// 각도값 랜덤성 추가
				3,						// 알파값 변화량
				255,					// 알파값 랜덤성 추가
				0,						// 크기 XY 변화량
				1,						// 크기 X 랜덤성 추가
				60,						// 파티클 생존 시간에 랜덤성 추가
				"SqaureParticle_5"		// 이미지 중 하나를 선택해 파티클에 입력
			);
			_particleTimer = 4;
		}
	}
}

void Bullet::makeBullet(const char * imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle,float damage, float speed, float maxDis, bool isFrame ,float igAngle ,BULLETSPEEDTYPE speedtype, string effectSound)
{
	_ig = IMAGEMANAGER->findImage(imageName);
	_effectIgName = effectIgName;
	_type = type;
	_x = _startX = x;
	_y = _startY = y;
	_angle = angle;
	_speed = speed;
	_isFrame = isFrame;
	_frameX = 0;
	_frameY = 0; 
	_frameTimer = 0;
	_distance = getDistance(_startX, _startY, _x, _y);
	_maxDistance = maxDis;
	_igAngle = igAngle;
	_speedType = speedtype;
	_jumpPower = -1;
	_gravity = 0.3f;
	_effectSound = effectSound;
	if (_type == BT_PLAYER || _type == BT_PLAYERNOCOL)
	{
		if (_speedType == BST_CHARGE)
		{
			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			if (p->GetSpecialAbilityOn(0, 2))
			if (p->GetMaxHp() * 0.6f > p->GetHP())
			{
				if (p->GetInitHp() * 0.6f > p->GetHP())
				{
					Playerdamage = p->GetMaxDamage();
				}
			}

			_damage = Playerdamage+damage;
		}
		else
		{

			Player* p = ENTITYMANAGER->getPlayer();
			int Playerdamage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
			if (p->GetSpecialAbilityOn(0, 2))
			{
				if (p->GetInitHp() * 0.6f > p->GetHP())
				{
					Playerdamage = p->GetMaxDamage();
				}
			}

			_damage = Playerdamage;
		}
	}
	else
	{
		_damage = damage;
	}
	_isDead = false;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::moveBullet()
{
	_x += cosf(_angle)*_speed;
	_y += -sinf(_angle)*_speed;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::Animation()
{

	_frameTimer++;
	_frameY = 0;
	
	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX > _ig->getMaxFrameX())
		{
			_frameX = 0;  //여기랑
		}
	}
}

void Bullet::speedTypeMove()
{
	switch (_speedType)
	{
	case BST_NOMAL:
		break;
	case BST_SLOW:
		_speed -= 0.03;

		if (_speed < 0)
		{
			_isDead = true;
		}
		break;
	case BST_FAST:
		_speed += 0.1;

		
		break;
	case BST_GRAVITY:
		_y += _jumpPower;
		_jumpPower += _gravity;
		break;
	default:
		break;
	}
}


