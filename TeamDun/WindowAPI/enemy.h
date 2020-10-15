#pragma once
#include "Object.h"
#include "Effect.h"

enum ENEMYSTATE {
	ES_IDLE, ES_MOVE, ES_ATTACK
};

class Enemy : public Object
{
protected :
	int				_Damage;				// 최종 데미지
	int				_minDamage;				// 최소 데미지
	int				_maxDamage;				// 최대 데미지
	int				_power;					// 위력
	float			_atkSpeed;				// 공격속도
	int				_initHp;				// 초기 체력
	float			_realDefence;			// 방어력
	image*			_hpBar1;
	image*			_hpBar2;
	int				_hpBarAlpha;

	ENEMYSTATE		_state;				// 현재 상태
	int				_attackCoolTime;	// 공격 쿨타임
	int				_useBulletId;		// 사용하는 불릿 ID
	float			_moveSpeed;			// 이동속도
	float			_gravity;			// 몬스터 중력값
	int				_count;				// 애니메이션 용 카운트
	int				_index;				// 애니메이션 용 인덱스
	bool			_isLeft;			// 애니메이션이 왼쪽이냐?
	bool			_isSpawned;			// 현재 스폰되었느냐
	Effect*			_spawnEffect;		// 스폰 이펙트


public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	
	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	SpawnEnemy();
	virtual void	SpawnAnimation();
	virtual void	GetDamage();
	void			HpBarDelete();
	// GETSET //
	int		GetAttackCoolTime() { return _attackCoolTime; }
	float	GetMoveSpeed()		{ return _moveSpeed; }
	bool	GetIsSpawned()		{ return _isSpawned; }
	int		GetHpBarAlphe()		{ return _hpBarAlpha; }

	void	SetHpBarAlpha(int hpBarAlpha) { _hpBarAlpha = hpBarAlpha; }
	void	SetAttackCoolTime(int coolTime)	{ _attackCoolTime = coolTime; }
	void	SetMoveSpeed(float speed)		{ _moveSpeed = speed; }
};