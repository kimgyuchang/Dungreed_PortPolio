#pragma once
#include "Object.h"

//캐릭터 상태
enum PLAYERSTATE
{
	PS_IDLE,PS_JUMP,PS_MOVE,PS_DIE,
};


class Player : public Object
{
private:
	int			_count;				//프레임 돌릴 카운트(속도조절)
	bool		_isLeft;			//왼쪽인지 (아닐시 오른쪽)
	bool		_jump;				//점프를 했는지
	PLAYERSTATE	_state;				//캐릭터 상태
	int			_hp;				//체력

	int			_numberOfDashes;	//대쉬 횟수
	int			_dashTimer;			//대쉬 시간
	bool		_isDash;
	POINT		_dashPoint;

	float		_speed;				//이동속도
	float		_gravity;
	float		_jumpPower;
	float		_angle;
	int			_satiety;			//포만감
	float		_damage;			//무기 공격력
	float		_power;				//위력
	float		_defense;			//방어력
	float		_atkSpeed;			//공격속도
	float		_evasion;			//회피
	float		_block;				//막기
	float		_toughness;			//강인함
	float		_trueDamage;		//고정 데미지
	float		_critical;			//크리티컬
	float		_criticalDamage;	//크리티컬 데미지
	float		_dashDamage;		//대쉬 공격력
	float		_dashSpeed;

	RECT		_collider[8];		//픽셀충돌용
	POINT		_pixelCenter;		//픽셀충돌용 몸 중앙
	float		_probeBottom;		//픽셀충돌용좌표
	bool		_isJump;
	bool		_downJump;
	bool		_leftBack;
	bool		_rightBack;
	int			_jumpCount;

	int			_downJmpTimer;
	bool		_bottomCol;
	
	Effect*		_dashEffect;
public:

	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();				//플레이어 움직임
	virtual void	pixelCollision();	//픽셀충돌
	virtual void	dash();

	int getHp() { return _hp; }
	float getDamage() { return _damage; }
	float getPower() { return _power; }
	float getAtkSpeed() { return _atkSpeed; }
	float getEvasion() { return _evasion; }
	float getBlock() { return _block; }
	float getToughness() { return _toughness; }
	float getTrueDamage() { return _trueDamage; }
	float getCritical() { return _critical; }
	float getCriticalDamage() { return _criticalDamage; }
	float getDashDamage() { return _dashDamage; }
	
};