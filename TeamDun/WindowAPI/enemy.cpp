#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isSpawned = false;

	return S_OK;
}

void Enemy::update()
{
	SpawnAnimation();
	
}

void Enemy::release()
{
	Object::release();
}

void Enemy::render(HDC hdc)
{
	Object::render(hdc);

	
	
}

void Enemy::Move()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::Attack()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::Animation()
{
	// 미구현 (상속 클래스 내부에서 세부구현) //
}

void Enemy::SpawnAnimation()
{

	if (_spawnEffect != nullptr)
	{
		if (_spawnEffect->GetIsDead())
		{
			_isSpawned = true;
			_spawnEffect = nullptr;
		}
	}
}

void Enemy::GetDamage()
{
	if (_isSpawned)
	{

		Player* p = ENTITYMANAGER->getPlayer();
		int damage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());

		damage = damage + damage * p->GetPower() / 100 - _realDefence;

		
		_HP -= damage;

		if (_HP <= 0)
		{
			SetIsDead(true);
		}
		
		EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 255));
	}
}

void Enemy::SpawnEnemy()
{
	if(_spawnEffect == nullptr && !_isSpawned)
		_spawnEffect = EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth()/2 - 46, _y + _vImages[0]->getFrameHeight()/2 - 46, "monsterSpawnEffect", 6);
}
