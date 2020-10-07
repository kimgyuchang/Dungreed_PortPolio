#pragma once
#include "Skill.h"

enum ITEMCLASS
{
	IC_NORMAL, IC_ADVANCED, IC_RARE, IC_LEGENDARY
};

enum ITEMTYPE
{
	IT_WEAPON_ONEHAND, IT_WEAPON_TWOHAND, IT_SUBWEAPON, IT_ACCESORRY
};

enum WEAPONTYPE
{
	WT_NEAR, WT_RANGE, WT_CHARGE, WT_SPEAR, WT_KATANA, WT_NOWEAPON
};

enum OPTIONTYPE
{
	POWER,				 // 위력
	ATKSPEED,			 // 공격속도
	DASHATK,			 // 대쉬 공격력
	DEFENCE,			 // 방어력
	BLOCK,				 // 막기
	CRITICALPERCENT,	 // 크리티컬 확률
	CRITICALDAMAGE,		 // 크리티컬 데미지
	MINDAMAGE,			 // 최소 데미지
	MAXDAMAGE,			 // 최대 데미지
	FINALDAMAGEPERCENT,	 // 최종 데미지 (%)
	FINALDAMAGE,		 // 최종 데미지
	TRUEDAMAGE,			 // 고정 데미지
	TOUGHNESS,			 // 강인함
	MAXHP,				 // 최대 HP
	MAXHPPERCENT,		 // 최대 HP (%)
	EVADE,				 // 회피
	MOVESPEED,			 // 이동 속도
	JUMPPOWER,			 // 점프력
	GOLDDROP,			 // 골드 드랍
	RELOADSPEED,		 // 재장전 속도
	DASHCOUNT,			 // 대쉬 횟수
	ACCURACY,			 // 조준 정확도
	IMMUNEFIRE,			 // 화염 면역
	IMMUNEICE,			 // 냉기 면역
	IMMUNEELEC,			 // 감전 면역
	IMMUNEPOSION,		 // 중독 면역
	TOFIRE,				 // 화염상태화
	TOICE,				 // 냉기상태화
	TOELEC,				 // 감전상태화
	TOPOSION,			 // 중독상태화
	FIREDAMAGE,			 // 화염 속성 데미지
	ICEDAMAGE,			 // 냉기 속성 데미지
	ELECDAMAGE,			 // 감전 속성 데미지
	POSIONDAMAGE,		 // 중독 속성 데미지
	ETC					 // 그 외 (수치가 아닌 케이스, DESCRIPTION으로 설명, 효과는 각자 구현 필요)
};

class SubOption
{
public :
	OPTIONTYPE	_optionId;
	float		_optionPower;
	string		_description;
};

class Item
{
private:
	ITEMTYPE			_itemType;			// 아이템의 종류
	WEAPONTYPE			_weaponType;		// 무기의 종류
	Skill*				_skill;				// 스킬
	int					_id;				// 아이템 아이디
	string				_name;				// 이름
	string				_description;		// 설명
	float				_minAtk;			// 최소 공격력
	float				_maxAtk;			// 최대 공격력
	float				_atkSpeed;			// 공격 속도
	int					_defence;			// 방어력

	vector<SubOption>	_subOption;			// 서브 옵션 목록
	bool				_useAtkSpeed;		// 공격 속도를 사용한다
	
	// 충전형 // 
	float				_chargePercent;		// 충전형 충전정도
	
	// 원거리 //
	int					_initNumOfBullet;	// 초기 총알 개수
	int					_curNumOfBullet;	// 현재 총알 개수
	int					_reloadTime;		// 재장전 시간
	Bullet*				_bullet;			// 사용 총알
	float				_accuracy;			// 조준 정확도
	int					_buyPrice;			// 구매 가격 (판매 가격 : 구매 가격 * 0.5)
	bool				_isBulletInfinite;	// 탄창이 무한한지
	
public:

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
	void EquipUnEquip(SubOption subOption, bool isEquip);
};

