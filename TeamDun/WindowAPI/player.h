#pragma once
#include "Object.h"
#include "inventory.h"
#include "Item.h"
//캐릭터 상태
enum PLAYERSTATE
{
	PS_IDLE,PS_JUMP,PS_MOVE,PS_DIE,
};

class Player : public Object
{
private:
	// 상태머신 // 
	// - 내부적 수치
	PLAYERSTATE		_state;					// 캐릭터 상태
	bool			_isLeft;				// 왼쪽인지 (아닐시 오른쪽)
	bool			_jump;					// 점프를 했는지
	bool			_isJump;				// 점프중인지
	bool			_downJump;				// 아래점프중인지
	bool			_isDash;

	// 이동 관련 //					   
	// - 표면적 수치
	float			_moveSpeed;				// 이동속도
	float			_jumpPower;				// 점프력
	int				_dashCount;				// 대쉬 횟수

	// - 내부적 수치
	float			_gravity;				// 중력
	float			_dashSpeed;				// 대쉬 속도
	Effect*			_dashEffect;			// 대쉬 이펙트
	int				_jumpCount;				// 점프 횟수
	int				_downJumpTimer;			// 아래 점프
	POINT			_dashPoint;				// 대쉬 위치
	int				_dashTimer;				// 대쉬 시간

	// 전투 관련 //			
	// - 표면적 수치 (공격)
	int				_minDamage;				// 최소 데미지
	int				_maxDamage;				// 최대 데미지
	int				_power;					// 위력
	float			_trueDamage;			// 고정 데미지
	float			_atkSpeed;				// 공격속도
	float			_realCriticalPercent;	// 크리티컬
	float			_criticalDamage;		// 크리티컬 데미지
	float			_dashDamage;			// 대쉬 공격력
	float			_reloadTime;			// 재장전에 걸리는 시간

	// - 표면적 수치 (방어) 					
	int				_initHp;				// 초기 체력
	int				_hp;					// 체력
	float			_realDefence;			// 방어력
	float			_realEvasion;			// 회피
	float			_toughness;				// 강인함
	float			_block;					// 막기
	
	// - 내부적 수치 (공격)
	float			_angle;					// 조준 각도   
	float			_criticalPercent;		// 크리티컬 (변환)
	int				_finalDamage;			// 최종 데미지 추가량
	float			_finalDamagePercent;	// 최종 데미지 추가량 (비율)
	float			_reloadSpeed;			// 재장전 속도 추가량
	float			_fireAccuracy;			// 조준 정확도

	// - 내부적 수치 (방어)
	float			_defence;				// 방어율 (변환)
	float			_evasion;				// 회피율 (변환)
	int				_maxHp;					// 최대 체력 추가량
	float			_maxHpPercent;			// 최대 최력 추가량 (비율)

	// 속성 //
	bool			_immuneFire;			// 화염 면역
	bool			_immuneIce;				// 냉기 면역
	bool			_immuneElectric;		// 감전 면역
	bool			_immunePosion;			// 중독 면역
	int				_toFire;				// 공격 시 화염 확률
	int				_toIce;					// 공격 시 냉기 확률
	int				_toElectric;			// 공격 시 감전 확률
	int				_toPosion;				// 공격 시 중독 확률
	int				_fireDamage;			// 화염 공격력
	int				_iceDamage;				// 냉기 공격력
	int				_elecDamage;			// 감전 공격력
	int				_posionDamage;			// 중독 공격력

	// 픽셀충돌 전용 //					 
	RECT			_collider[8];			// 픽셀충돌용
	POINT			_pixelCenter;			// 픽셀충돌용 몸 중앙
	float			_probeBottom;			// 픽셀충돌용좌표
	bool			_leftBack;				   
	bool			_rightBack;				   
	bool			_bottomCol;
	
	// 애니메이션 //
	// - 내부적 수치
	int				_animCount;				// 프레임 돌릴 카운트(속도조절)

	// 장착 //
	Inventory*		_inven;					// 인벤토리
	Item*			_weapons[2];			// 공격무기
	Item*			_subWaepons[2];			// 보조무기
	vector<Item*>	_vAccessories;			// 악세서리들
	bool			_isUseFirstWeapon;		// 첫번째 무기를 장착하고 있는지

	// 기타 //						 
	// - 표면적 수치
	int				_satiety;				// 포만감
	int				_money;					// 돈
	int				_level;					// 레벨
	
											// - 내부적 수치
	int				_experience;			// 경험치
	int				_needExperience;		// 필요 경험치
	float			_goldDrop;				// 돈 드랍양

	
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
	float getPower() { return _power; }
	float getAtkSpeed() { return _atkSpeed; }
	float getEvasion() { return _realEvasion; }
	float getBlock() { return _block; }
	float getToughness() { return _toughness; }
	float getTrueDamage() { return _trueDamage; }
	float getCritical() { return _realCriticalPercent; }
	float getCriticalDamage() { return _criticalDamage; }
	float getDashDamage() { return _dashDamage; }
	
};