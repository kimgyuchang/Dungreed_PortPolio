#pragma once
#include "Object.h"

enum ENEMYSTATE {
	ES_IDLE, ES_MOVE, ES_ATTACK
};

class Enemy : public Object
{
protected :
	ENEMYSTATE		_state;				// 현재 상태
	RECT			_body;				// 충돌체
	int				_attackCoolTime;	// 공격 쿨타임
	int				_useBulletId;		// 사용하는 불릿 ID
	float			_moveSpeed;			// 이동속도
	float			_gravity;			// 몬스터 중력값
	int				_count;				// 애니메이션 용 카운트
	int				_index;				// 애니메이션 용 인덱스

public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	
	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();

	// GETSET //
	RECT getBody() { _body; }
	int getAttackCoolTime() { _attackCoolTime; }
	float getMoveSpeed() { _moveSpeed; }

	void setBody(RECT rc) { _body = rc; }
	void setAttackCoolTime(int coolTime) { _attackCoolTime = coolTime; }
	void setMoveSpeed(float speed) { _moveSpeed = speed; }
};