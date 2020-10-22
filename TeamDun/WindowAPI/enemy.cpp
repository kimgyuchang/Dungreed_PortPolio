#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isSpawned = false;
	_isViewingHpBar = true;
	_hpBarAlpha = 0;
	_hpBar1 = IMAGEMANAGER->findImage("HpBar1");
	_hpBar2 = IMAGEMANAGER->findImage("HpBar2");
	_hongryanCount = 0;
	_hongryanEffectImage = IMAGEMANAGER->findImage("HongRyunEffect");
	_weakeningTimer = 0;
	_weakeningDmgTimer = 0;
	return S_OK;
}

void Enemy::update()
{
	SpawnAnimation();
	WeakeningChecker();
	HpBarDelete();
}

void Enemy::release()
{
	Object::release();
}

/// <summary>
/// 캐릭터 특성(갈망)에서 사용되는 '약화' 체크
/// </summary>
void Enemy::WeakeningChecker()
{
	if (_isWeakining)
	{
		_weakeningTimer--;
		_weakeningDmgTimer--;

		if (_weakeningTimer < 0)
		{
			_isWeakining = false;
		}
		if (_weakeningDmgTimer < 0)
		{
			_weakeningDmgTimer = 15;
			_hpBarAlpha = 255;
			SOUNDMANAGER->play("Hit_Monster");
			int dmg = RANDOM->range(1, 3);
			_hp -= dmg;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(dmg), PIX, WS_MIDDLE, WSORT_LEFT, RGB(230, 30, 30));
		}

		if (_hp <= 0)
		{
			
			MonsterDead();
		}
	}
}

void Enemy::render(HDC hdc)
{
	Object::render(hdc);
	if (_hpBarAlpha > 0 && _isViewingHpBar)
	{
		CAMERAMANAGER->alphaRender(hdc, _hpBar1, _x + _vImages[_useImage]->getFrameWidth() / 2 - _hpBar1->getWidth() / 2, _y + _vImages[_useImage]->getFrameHeight(), 0, 0, _hpBar1->getWidth(), _hpBar1->getHeight(), _hpBarAlpha);
		CAMERAMANAGER->alphaRender(hdc, _hpBar2, _x + _vImages[_useImage]->getFrameWidth() / 2 - _hpBar2->getWidth() / 2, _y + _vImages[_useImage]->getFrameHeight(), 0, 0, _hpBar2->getWidth() / (float)_initHp * _hp, _hpBar2->getHeight(), _hpBarAlpha);
	}

	renderHongryanCount(hdc);
}

void Enemy::renderHongryanCount(HDC hdc)
{
	if (_hongryanCount > 0)
	{
		CAMERAMANAGER->FrameRender(hdc, _hongryanEffectImage,
			_x + _vImages[0]->getFrameWidth() / 2 - _hongryanEffectImage->getFrameWidth() / 2,
			_y + _vImages[0]->getFrameHeight() + 20, _hongryanCount - 1, 0);
	}
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
	Player* _p = ENTITYMANAGER->getPlayer();

	if (_isSpawned)
	{
		SOUNDMANAGER->play("Hit_Monster");
		Player* p = ENTITYMANAGER->getPlayer();
		p->SetIsCritical(false);

		int damage = RANDOM->range(p->GetMinDamage(), p->GetMaxDamage());
		if (p->GetSpecialAbilityOn(0, 2))
		{
			if (p->GetMaxHp() * 0.6f > p->GetHP())
			{
				damage = p->GetMaxDamage();
			}
		}

		damage = damage + damage * (p->GetPower() + 6 * _hongryanCount) / 100 - _realDefence;
		int critical = RANDOM->range(100);
		if (critical <= p->GetRealCriPer())
		{
			p->SetIsCritical(true);
			_hpBarAlpha = 255;
			damage = damage + damage * p->GetCriDamage() / 100;
			_hp -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 0));
		}
		else
		{
			_hpBarAlpha = 255;
			_hp -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 255));

		}

		if (_hp <= 0)
		{
			for (int i = 0; i < ENTITYMANAGER->getPlayer()->GetVAccessories().size(); i++)
			{
				if (ENTITYMANAGER->getPlayer()->GetVAccessories()[i]->GetId() == 4007)
				{
					ENTITYMANAGER->getPlayer()->SetKillPoint(ENTITYMANAGER->getPlayer()->GetKillPoint() + 1);
				}

			}
			MonsterDead();
		}

		CheckSpecialPlayerInteractions();
	}
}

void Enemy::MonsterDead()
{
	SOUNDMANAGER->play("몬스터_사망 (1)", 0.5f, true);
	EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameWidth() / 2, _y + _vImages[0]->getFrameHeight() / 2 - IMAGEMANAGER->findImage("DieEffect")->getFrameHeight() / 2, "DieEffect", 3, 0, 0, false, 255, 0, 1, 1, false);

	int dropCoin = RANDOM->range(0, 1);
	if (dropCoin == 0)
	{
		int coinCount = RANDOM->range(1, 6);
		for (int i = 0; i < coinCount + coinCount * ((ENTITYMANAGER->getPlayer()->GetGoldDrop() - 100) / 100.f); i++)
		{
			Coin* coin = new Coin(*dynamic_cast<Coin*>(DATAMANAGER->GetObjectById(524)));
			coin->SetUseImage(1);
			coin->SetCoin(_x, _y, RANDOM->range(-5.f, 5.f), RANDOM->range(2.f, 3.f));
			MAPMANAGER->GetPlayMap()->GetObjects().push_back(coin);
		}
	}
	SetIsDead(true);
}

void Enemy::GetDamage(int damage)
{
	Player* _p = ENTITYMANAGER->getPlayer();

	if (_isSpawned)
	{
		SOUNDMANAGER->play("Hit_Monster");
		Player* p = ENTITYMANAGER->getPlayer();
		p->SetIsCritical(false);
		damage = damage + damage * (p->GetPower() + 6 * _hongryanCount) / 100 - _realDefence;
		int critical = RANDOM->range(100);
		if (critical <= p->GetRealCriPer())
		{
			p->SetIsCritical(true);
			_hpBarAlpha = 255;
			damage = damage + damage * p->GetCriDamage() / 100;
			_hp -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 0));
		}
		else
		{
			_hpBarAlpha = 255;
			_hp -= damage;
			EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, to_string(damage), PIX, WS_MIDDLE, WSORT_LEFT, RGB(255, 255, 255));
		}

		if (_hp <= 0)
		{
			for (int i = 0; i < ENTITYMANAGER->getPlayer()->GetVAccessories().size(); i++)
			{
				if (ENTITYMANAGER->getPlayer()->GetVAccessories()[i]->GetId() == 4007)
				{
					ENTITYMANAGER->getPlayer()->SetKillPoint(ENTITYMANAGER->getPlayer()->GetKillPoint() + 1);
				}

			}
			MonsterDead();
		}

		CheckSpecialPlayerInteractions();
	}
}

void Enemy::CheckSpecialPlayerInteractions()
{
	Player* _p = ENTITYMANAGER->getPlayer();
	int curHp = ENTITYMANAGER->getPlayer()->GetHP();

	if (_p->GetClothType() == PC_HONGRYAN) _hongryanCount++;

	if (_p->GetClothType() == PC_IKINABEAR && !_p->GetIsRaging())
	{
		int rage = _p->GetRageCurrent() + 1;
		if (rage > _p->GetRageMax()) rage = _p->GetRageMax();
		_p->SetRageCurrent(rage);
	}

	if ((_p->GetSpecialAbilityOn(6, 0) && RANDOM->range(10) < 1) || _p->GetSpecialAbilityOn(6, 2))
	{
		if (!_isWeakining) _weakeningDmgTimer = 15;
		_isWeakining = true;
		_weakeningTimer = 600;
	}

	if (_p->GetSpecialAbilityOn(6, 1) && _isWeakining && _p->GetRestorePrevHp() != 0)
	{
		int newHp = _p->GetHP() + _p->GetRestorePrevHp();
		if (newHp > _p->GetMaxHp()) newHp = _p->GetMaxHp();
		_p->SetHp(newHp);
		_p->SetRestorePrevHp(0);
	}
}

void Enemy::HpBarDelete()
{
	if (_hpBarAlpha > 0)
	{
		_hpBarAlpha -= 2;

	}
	if (_hpBarAlpha < 0)
	{
		_hpBarAlpha = 0;
	}

}

void Enemy::SpawnEnemy()
{
	if (_spawnEffect == nullptr && !_isSpawned)
	{
		_spawnEffect = EFFECTMANAGER->AddEffect(_x + _vImages[0]->getFrameWidth() / 2 - 46, _y + _vImages[0]->getFrameHeight() / 2 - 46, "monsterSpawnEffect", 6);
		SOUNDMANAGER->play("스폰몬스터", 0.5f, true);
	}
}
