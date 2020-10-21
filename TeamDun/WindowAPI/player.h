#pragma once
#include "Object.h"
#include "inventory.h"
#include "Item.h"

class CharToolTip
{
public :
	string frameName;
	string title;
	string description;
	string additionalDescription;
	float scaleX;
	float scaleY;

	void init(string fn, string t, string des, string add, float xSize, float ySize)
	{
		frameName = fn;
		title = t;
		description = des;
		additionalDescription = add;
		scaleX = xSize;
		scaleY = ySize;
	}
};

//캐릭터 상태
enum PLAYERSTATE
{
	PS_IDLE,PS_JUMP,PS_MOVE,PS_DIE,
};
struct ReloadEffect
{
	image* ig;
	float x;
	float y; 
	int frameX;
	int frameY;
	int frameTime;
	bool isViewing;
};
enum CLOTHTYPE
{
	PC_NORMAL, PC_METAL, PC_GUNNER, PC_ALICE, PC_HONGRYAN, PC_IKINABEAR, 
	PC_RIDERH, PC_CRIMINAL, PC_PICKKING, PC_FATGUY, 
	PC_HORSESWORD, PC_HUMANLASLEY, PC_MASTERCHEF
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
	bool			_isPlayerDead;

	bool			_isReload;
	float			_reloadCount;
	ReloadEffect	_reloadEffect;
	int				_bulletCount;
	int				_maxBullet;
	
	// 피격관련
	bool			_isStun;				//스턴상태인지
	int				_stunCount;
	int				_stunAniCout;
	int				_stunFrameX;
	int				_stunFrameY;
	bool			_isHit;					// 플레이어가 데미지를 입었는지
	int				_hitCount;				// 히트후 무적시간 세는용
	int				_hitAlpha;				//	히트시 먹일 알파값

	// 이동 관련 //					   
	// - 표면적 수치
	float			_moveSpeed;				// 이동속도
	float			_jumpPower;				// 점프력
	int				_dashCount;				// 대쉬 횟수
	int				_dashRestoreCount;		// 대쉬 복구카운트
	int				_dashRestoreTime;		// 대쉬 복구시간
	int				_maxDashCount;			// 최대 대쉬 횟수

	// - 내부적 수치
	float			_gravity;				// 중력
	float			_dashSpeed;				// 대쉬 속도
	Effect*			_dashEffect;			// 대쉬 이펙트
	int				_jumpCount;				// 점프 횟수
	int				_downJumpTimer;			// 아래 점프
	POINT			_dashPoint;				// 대쉬 위치
	int				_dashTimer;				// 대쉬 시간
	float			_moveSpeedPer;			// 이동속도 퍼센트

	// 전투 관련 //			
	// - 표면적 수치 (공격)
	int				_minDamage;				// 최소 데미지
	int				_maxDamage;				// 최대 데미지
	int				_power;					// 위력
	int				_trueDamage;			// 고정 데미지
	float			_atkSpeed;				// 공격속도
	float			_criticalPercent;		// 크리티컬
	float			_criticalDamage;		// 크리티컬 데미지
	bool			_isCritical;			// 크리티컬이 떴는지
	float			_dashDamage;			// 대쉬 공격력
	float			_reloadTime;			// 재장전에 걸리는 시간

	// - 표면적 수치 (방어) 					
	int				_initHp;				// 초기 체력
	float			_defence;				// 방어
	float			_evasion;				// 회피 
	float			_toughness;				// 강인함
	float			_block;					// 막기
	
	// - 내부적 수치 (공격)
	float			_angle;					// 조준 각도   
	float			_realCriticalPercent;	// 크리티컬 (변환)
	int				_finalDamage;			// 최종 데미지 추가량
	float			_finalDamagePercent;	// 최종 데미지 추가량 (비율)
	float			_reloadSpeed;			// 재장전 속도 추가량
	float			_fireAccuracy;			// 조준 정확도
	float			_realAttackSpeed;		// 공격속도(프레임)
	float			_atkSpeedPer;			// 공격속도 퍼센트
	RECT			_dashAttackRect;		// 대쉬 공격 렉트

	// - 내부적 수치 (방어)
	float			_realEvasion;			// 회피 (변환)
	float			_realDefence;			// 방어력 (변환)
	int				_maxHp;					// 최대 체력 추가량
	float			_maxHpPercent;			// 최대 최력 추가량 (비율)

	// 속성 //
	bool			_isFire;
	int				_fireCount;
	bool			_isIce;
	bool			_isElectric;
	bool			_isPoison;
	bool			_immuneFire;			// 화염 면역
	bool			_immuneIce;				// 냉기 면역
	bool			_immuneElectric;		// 감전 면역
	bool			_immunePosion;			// 중독 면역
	bool			_immuneStun;			// 기절 면역
	int				_toFire;				// 공격 시 화염 확률
	int				_toIce;					// 공격 시 냉기 확률
	int				_toElectric;			// 공격 시 감전 확률
	int				_toPosion;				// 공격 시 중독 확률
	int				_toStun;				// 공격 시 스턴 확률
	int				_fireDamage;			// 화염 공격력 (화염 공격력)
	int				_iceDamage;				// 냉기 공격력 (냉기 시간)
	int				_elecDamage;			// 감전 d공격력 (감전 시간)
	int				_posionDamage;			// 중독 공격력 (중독 공격력)
	int				_stunDamage;			// 스턴 공격력 (스턴 시간)

	// 특성 관련 //
	int				_maxPoint;					// 전체 능력치
	int				_remainPoint;				// 남은 능력치
	int				_abilityNum[7];				// 투자된 능력치
	bool			_specialAbilityOn[7][3];	// 스폐셜 어빌리티 온
	RECT			_jumpAttackRect;			// 점프 공격 (분노 스폐셜)
	int				_damageUpTimer;				// 데미지 업 타이머 (분노 스폐셜)
	bool			_damageUpTimerUse;			// 데미지 업 타이머가 사용되고 있는지 (분노 스폐셜)
	bool			_atkSpdUpUse;				// 공격속도 업이 사용되었는지 (신속 스페셜)
	int				_dashInvincibTimer;			// 대쉬 무적 시간 (신속 스폐셜)
	bool			_dashInvinCible;			// 무적 상태인지 (신속 스폐셜)
	int				_deathDefencerTimer;		// 죽음 방지 타이머 (방어 스폐셜)
	bool			_deathDefencerActivated;	// 죽음 방지 타이머가 작동했는지 (방어 스폐셜)
	int				_regenTimer;				// 리젠 타이머 (방어 스폐셜)
	bool			_getRangeStatus;			// Range 능력치를 얻었는지 (집중 스폐셜)
	int				_reloadItemTimer;			// 재장전 장비 타이머 (집중 스폐셜)
	int				_reloadItemNumber;			// 재장전 아이템 갯수 (집중 스폐셜)
	int				_restorePrevHp;				// 직전에 받은 HP회복가능량 (갈망 스폐셜)
	int				_restoreHpTimer;			// Hp회복 가능 타이머 (갈망 스폐셜)

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
	int				_dustEffectCount;

	// 장착 //
	Inventory*		_inven;					// 인벤토리
	Item*			_weapons[2];			// 공격무기
	Item*			_subWeapons[2];			// 보조무기
	vector<Item*>	_vAccessories;			// 악세서리들
	int				_selectedWeaponIdx;		// 장착한 무기 인덱스
	int				_accesoryCount;			// 악세서리 최대 개수
	
	// 기타 //						 
	// - 표면적 수치
	int				_satiety;				// 포만감
	int				_maxSatiety;			// 최대 포만감
	int				_money;					// 돈
	int				_level;					// 레벨
	CLOTHTYPE		_clothType;				// 현재 입은 옷
	// - 내부적 수치
	int				_experience;			// 경험치
	int				_needExperience;		// 필요 경험치
	float			_goldDrop;				// 돈 드랍양

	// SWAP //
	int				_swapCoolTime;			// 스왑 쿨타임

	// UI //
	vector<CharToolTip>		_vToolTips;				// 툴팁 프레임 목록
	vector<string>			_vToolTipsName;			// 툴팁 프레임 이름 목록
	UIFrame*				_hpFrame;				// HPFrame
	UIFrame*				_dashFrame;				// DashFrame
	UIFrame*				_traitFrame;			// traitFrame
	int						_uiScrollTimer;			// 스크롤에 사용되는 타이머
	float					_uiMouseLocation;		// 저장된 마우스 X좌표
	float					_movedX;				// 움직인 거리
	string					_vTraitTooltip[7][3];	// 특성 툴팁들
	
	// 각 캐릭터별 특성 //

	// 총잡이 //
	bool			_useGun;
	

	// 앨리스 //
	image*			_aliceZone;
	float			_aliceZoneRadius;
	bool			_aliceZoneIn;
	bool			_alicePowerDownCheck;

	// 이키나곰 //
	int				_rageCurrent;					// 현재 화난 값
	int				_rageMax;						// 화남값 최대 -> 변신 -> 화남값 0
	bool			_isRaging;						// 현재 변신해있는지
	int				_rageTimer;						// 변신 시간

	// 라이더H //
	int				_prevPowerPlus;					// 저번 프레임의 증가된 파워량
	

public:

	virtual HRESULT init();
	virtual void	update();
	void DashInvincibility();
	void AddMaxDash();
	void SubMaxDash();
	void DashAttack();
	void DashImageCheck();
	void SetTextLeftDown();
	void DashUICheck();
	void RangeGetStatusAbility();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	Move();				//플레이어 움직임
	void DamageJumpAttackRect();
	void ControlDamageUpTimer();
	void DamageUpEnemyKill();
	void SpecialAtkSpeedUp();
	virtual void	pixelCollision();	//픽셀충돌
	virtual void	dash();				//대쉬
	virtual void	GetDamage();
	void invincibility();				//히트시 무적
	void UpdateCharPage();
	void SetRealStat();
	void CharPageToolTipOn();

	void ReInitTooltip(int n);
	void SetToolTipFrame(float x, float y, int index);

	void SetDeathDefencerTimerDown();

	void RegenDefenceSkill();

	void GetHitDamage(int damage);

	void RestoreHpTimerChecker();

	void RemoveMagicShield();

	void ControlTraitPage();
	void ReloadItemChecker();
	void AddTraitPoint();
	void ReloadTraitPoint();
	void CheckTraitIconHovered();
	void ReInitTraitUI();

	void CheckUsePistolGunner();

	void MoveTraitUI();
	
	void SwitchWeapon();
	void JumpAttackRectUpdate();
	void AbnormalState(); // 상태이상 구현
	void ReloadBullet();
	//캐릭터 능력 구현 함수
	void CheckAliceZone();
	void AdjustAlicePower();
	void SetIkinaBearAngry();
	void CheckMoveSpeedRiderH();
	void CheckCliminal();
	
	void SetHpUI();
	// GETSET //
	PLAYERSTATE		GetState()				{ return _state; }
	bool			GetIsLeft()				{ return _isLeft; }
	bool			GetJump()				{ return _jump; }
	bool			GetIsJump()				{ return _isJump; }
	bool			GetDownJump()			{ return _downJump; }
	bool			GetIsDash()				{ return _isDash; }
	bool			GetIsHit()				{ return _isHit; }
	bool			GetIsStun()				{ return _isStun; }
	float			GetMoveSpeed()			{ return _moveSpeed; }
	float			GetJumpPower()			{ return _jumpPower; }
	int				GetDashCount()			{ return _dashCount; }
	float			GetGravity()			{ return _gravity; }
	float			GetDashSpeed()			{ return _dashSpeed; }
	Effect*			GetDashEffect()			{ return _dashEffect; }
	int				GetJumpCount()			{ return _jumpCount; }
	int				GetDownJumpTimer()		{ return _downJumpTimer; }
	POINT			GetDashPoint()			{ return _dashPoint; }
	int				GetDashTimer()			{ return _dashTimer; }
	float			GetMoveSpeedPer()		{ return _moveSpeedPer; }
	int				GetMinDamage()			{ return _minDamage; }
	int				GetMaxDamage()			{ return _maxDamage; }
	int				GetPower()				{ return _power; }
	int				GetTrueDamage()			{ return _trueDamage; }
	float			GetAtkSpeed()			{ return _atkSpeed; }
	float			GetRealCriPer()			{ return _realCriticalPercent; }
	float			GetCriDamage()			{ return _criticalDamage; }
	float			GetDashDamage()			{ return _dashDamage; }
	float			GetReloadTime()			{ return _reloadTime; }
	int				GetBulletCount()		{ return _bulletCount; }
	int				GetMaxBullet()			{ return _maxBullet; }
	int				GetInitHp()				{ return _initHp; }
	float			GetRealDefence()		{ return _realDefence; }
	float			GetRealEvasion()		{ return _realEvasion; }
	float			GetToughness()			{ return _toughness; }
	float			GetBlock()				{ return _block; }
	float			GetAngle()				{ return _angle; }
	float			GetCriPer()				{ return _criticalPercent; }
	bool			GetIsCritical()			{ return _isCritical;}
	int				GetFinalDamage()		{ return _finalDamage; }
	float			GetFinalDamagePer()		{ return _finalDamagePercent; }
	float			GetReloadSpeed()		{ return _reloadSpeed; }
	float			GetFireAccuracy()		{ return _fireAccuracy; }
	float			GetDefence()			{ return _defence; }
	float			GetEvasion()			{ return _evasion; }
	int				GetMaxHp()				{ return _maxHp; }
	float			GetMaxHpPer()			{ return _maxHpPercent; }
	bool			GetImmuneFire()			{ return _immuneFire; }
	bool			GetImmuneIce()			{ return _immuneIce; }
	bool			GetImmuneElec()			{ return _immuneElectric; }
	bool			GetImmunePosion()		{ return _immunePosion; }
	bool			GetImmuneStun()			{ return _immuneStun; }
	int				GetToFire()				{ return _toFire; }
	int				GetToIce()				{ return _toIce; }
	int				GetToElec()				{ return _toElectric; }
	int				GetToPosion()			{ return _toPosion; }
	int				GetToStun()				{ return _toStun; }
	int				GetFireDamage()			{ return _fireDamage; }
	int				GetIceDamage()			{ return _iceDamage; }
	int				GetElecDamage()			{ return _elecDamage; }
	int				GetPosionDamage()		{ return _posionDamage; }
	int				GetStunDamage()			{ return _stunDamage; }
	int				GetAnimCount()			{ return _animCount; }
	Inventory*		GetInventory()			{ return _inven; }
	Item*			GetWeapon(int num)		{ return _weapons[num]; }
	Item*			GetSubWeapon(int num)	{ return _subWeapons[num]; }
	vector<Item*>&	GetVAccessories()		{ return _vAccessories; }
	Item*			GetAccessory(int num)	{ return _vAccessories[num]; }
	int				GetSelectedWeaponIdx()	{ return _selectedWeaponIdx; }
	int				GetSatiety()			{ return _satiety; }
	int				GetMoney()				{ return _money; }
	int				GetLevel()				{ return _level; }
	int				GetExperience()			{ return _experience; }
	int				GetNeedExperience()		{ return _needExperience; }
	float			GetRealAttackSpeed()	{ return _realAttackSpeed; }
	float			GetAtkSpeedPer()		{ return _atkSpeedPer; }
	float			GetGoldDrop()			{ return _goldDrop; }
	int				GetAccesoryCount()	    { return _accesoryCount; }
	int				GetMaxDashCount()		{ return _maxDashCount; }
	int				GetMaxSatiety()			{ return _maxSatiety; }
	int				GetRageCurrent()		{ return _rageCurrent; }
	int				GetRageMax()			{ return _rageMax; }
	bool			GetIsRaging()			{ return _isRaging; }
	int				GetRageTimer()			{ return _rageTimer; }
	float			GetPrevPowerPlus()		{ return _prevPowerPlus; }
	bool			GetIsReload()			{ return _isReload; }
	bool			GetDashInvincible()		{ return _dashInvinCible; }
	bool			GetDashInvincibleTimer(){ return _dashInvincibTimer; }
	CLOTHTYPE		GetClothType()			{ return _clothType; }
	int				GetRestorePrevHp()		{ return _restorePrevHp; }
	bool			GetSpecialAbilityOn(int indexBig, int indexSmall) { return _specialAbilityOn[indexBig][indexSmall]; }
	
	void			SetIsReload(bool isReload)						{ _isReload = isReload; }
	void			SetHitCount(int hitCount)						{ _hitCount = hitCount; }
	void			SetState(PLAYERSTATE state)						{ _state = state; }
	void			SetIsLeft(bool isLeft) 							{ _isLeft = isLeft; }
	void			SetJump(bool jump) 								{ _jump = jump; }
	void			SetIsJump(bool isJump)							{ _isJump = isJump; }
	void			SetDownJump(bool downJump) 						{ _downJump = downJump; }
	void			SetIsDash(bool isDash) 							{ _isDash = isDash; }
	void			SetIsHit(bool isHit)							{ _isHit = isHit; }
	void			SetMoveSpeed(float moveSpeed) 					{ _moveSpeed = moveSpeed; }
	void			SetJumpPower(float jumpPower) 					{ _jumpPower = jumpPower; }
	void			SetDashCount(int dashCount) 					{ _dashCount = dashCount; }
	void			SetGravity(float gravity) 						{ _gravity = gravity; }
	void			SetDashSpeed(float dashSpeed) 					{ _dashSpeed = dashSpeed; }
	void			SetDashEffect(Effect* dashEffect) 				{ _dashEffect = dashEffect; }
	void			SetJumpCount(int jumpCount) 					{ _jumpCount = jumpCount; }
	void			SetDownJumpTimer(int downJumpTimer)				{ _downJumpTimer = downJumpTimer; }
	void			SetDashPoint(POINT dashPoint) 					{ _dashPoint = dashPoint; }
	void			SetDashTimer(int dashTimer) 					{ _dashTimer = dashTimer; }
	void			SetMoveSpeedPer(float moveSpeedPer)				{ _moveSpeedPer = moveSpeedPer; }
	void			SetMinDamage(int minDamage) 					{ _minDamage = minDamage; }
	void			SetMaxDamage(int maxDamage) 					{ _maxDamage = maxDamage; }
	void			SetPower(int power) 							{ _power = power; }
	void			SetTrueDamage(int trueDamage)					{ _trueDamage = trueDamage; }
	void			SetAtkSpeed(float atkSpeed) 					{ _atkSpeed = atkSpeed; }
	void			SetAtkSpeedPer(float atkSpeedPer) 				{ _atkSpeedPer = atkSpeedPer; }
	void			SetRealCriPer(float realCriPer) 				{ _realCriticalPercent = realCriPer; }
	void			SetCriDamage(float criDamage) 					{ _criticalDamage = criDamage; }
	void			SetDashDamage(float dashDamage) 				{ _dashDamage = dashDamage; }
	void			SetReloadTime(float reloadTime) 				{ _reloadTime = reloadTime; }
	void			SetInitHp(int initHp)							{ _initHp = initHp; }
	void			SetRealDefence(float realDefence)				{ _realDefence = realDefence; }
	void			SetRealEvasion(float realEvasion)				{ _realEvasion = realEvasion; }
	void			SetToughness(float toughness) 					{ _toughness = toughness; }
	void			SetBlock(float block) 							{ _block = block; }
	void			SetAngle(float angle) 							{ _angle = angle; }
	void			SetCriPer(float criticalPercent)				{ _criticalPercent = criticalPercent; }
	void			SetIsCritical(bool isCritical)					{ _isCritical = isCritical; }
	void			SetFinalDamage(int finalDamage)					{ _finalDamage = finalDamage; }
	void			SetFinalDamagePer(float finalDamagePercent)		{ _finalDamagePercent = finalDamagePercent; }
	void			SetReloadSpeed(float reloadSpeed) 				{ _reloadSpeed = reloadSpeed; }
	void			SetFireAccuracy(float fireAccuracy)				{ _fireAccuracy = fireAccuracy; }
	void			SetDefence(float defence) 						{ _defence = defence; }
	void			SetEvasion(float evasion) 						{ _evasion = evasion; }
	void			SetMaxHp(int maxHp) 							{ _maxHp = maxHp; }
	void			SetMaxHpPer(float maxHpPercent) 				{ _maxHpPercent = maxHpPercent; }
	void			SetImmuneFire(bool immuneFire)					{ _immuneFire = immuneFire; }
	void			SetImmuneIce(bool immuneIce) 					{ _immuneIce = immuneIce; }
	void			SetImmuneElec(bool immuneElec)					{ _immuneElectric = immuneElec; }
	void			SetImmunePosion(bool immunePosion)  			{ _immunePosion = immunePosion; }
	void			SetImmuneStun(bool immuneStun)					{ _immuneStun = immuneStun; }
	void			SetToFire(int toFire) 							{ _toFire = toFire; }
	void			SetToIce(int toIce) 							{ _toIce = toIce; }
	void			SetToElec(int toElec)							{ _toElectric = toElec; }
	void			SetToPosion(int toPosion)						{ _toPosion = toPosion; }
	void			SetToStun(int toStun)							{ _toStun = toStun; }
	void			SetFireDamage(int fireDamage)					{ _fireDamage = fireDamage; }
	void			SetIceDamage(int iceDamage) 					{ _iceDamage = iceDamage; }
	void			SetElecDamage(int elecDamage) 					{ _elecDamage = elecDamage; }
	void			SetPosionDamage(int posionDamage)  				{ _posionDamage = posionDamage; }
	void			SetStunDamage(int stunDamage)					{ _stunDamage = stunDamage; }
	void			SetAnimCount(int animCount) 					{ _animCount = animCount; }
	void			SetInventory(Inventory* inven) 					{ _inven = inven; }
	Item*			SetWeapon(int num, Item* item)					{ Item* saveItem = _weapons[num]; _weapons[num] = item; return saveItem; }
	Item*			SetSubWeapon(int num, Item* item)				{ Item* saveItem = _subWeapons[num]; _subWeapons[num] = item; return saveItem; }
	Item*			SetVAccessory(int num, Item* item)				{ Item* saveItem = _vAccessories[num]; _vAccessories[num] = item; return saveItem; }
	void			SetSelectedWeaponIdx(int selectWeaponidx)		{ _selectedWeaponIdx = selectWeaponidx; }
	void			SetSatiety(int satiety) 						{ _satiety = satiety; }
	void			SetMoney(int money) 							{ _money = money; }
	void			SetLevel(int level) 							{ _level = level; }
	void			SetExperience(int experience) 					{ _experience = experience; }
	void			SetNeedExperience(int needExperience) 			{ _needExperience = needExperience; }
	void			SetGoldDrop(float goldDrop) 					{ _goldDrop = goldDrop; }
	void			SetAccesoryCount(int accesoryCount)				{ _accesoryCount = accesoryCount; }
	void			SetMaxDashCount(int dashCount)					{ _maxDashCount = dashCount; }
	void			SetMaxSatiety(int satiety)						{ _maxSatiety = satiety; }
	void			SetIsStun(bool isStun)							{ _isStun = isStun; }
	void			SetClothType(CLOTHTYPE type)					{ _clothType = type; }
	void			SetRageCurrent(int rage)						{ _rageCurrent = rage; }
	void			SetPrevPowerPlus(float num)						{ _prevPowerPlus = num; }
	void			SetRestorePrevHp(int num)						{ _restorePrevHp = num; }
	void			SetMaxBullet(int maxBullet)						{ _maxBullet = maxBullet; }
	void			SetBulletCount(int bulletCount)					{ _bulletCount = bulletCount; }
};
