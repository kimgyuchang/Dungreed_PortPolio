#pragma once
#include "enemy.h"
#include "BelialDie.h"
enum BELIALPATTERN
{
	RAZER, KNIFE, BULLET
};
struct bossHands
{
	image*		ig;
	float		x;
	float		y;
	float		frameX;
	float		frameY;
	int			Timer;
	float		CenterX;
	float		CenterY;
	ENEMYSTATE	state;

};
struct BossSword
{
	image* ig;
	float x;
	float y;
	float angle;
	float speed;
	bool  isDead;
	bool  isCol;
	bool  isHit;
	RECT body;
	int Timer;
	int frameX;
	int frameY;
	
};

struct Razer
{
	image* ig;
	float x;
	float y;
	int frameX;
	int frameY;
	RECT body;
};

class Belial : public Enemy
{
private:
	image*			_bossBack;
	BELIALPATTERN	_BelialPattern;
	float			_angle;
	int				_PatternTime;
	float			_fireAngle;
	int				_bulletFireTimer;
	int				_bulletEndTimer;
	bool			_realIsViewing;
	int				_handAlpha;
	//레이저패턴 변수
	bool			_RazerEnd;
	int				_RazerEndCount;
	int				_RazerCount;
	float			_playerY1;
	float			_playerY2;
	vector<Razer*>	_vLeftRazer;
	vector<Razer*>	_vRightRazer;

	//칼패턴 변수
	vector<BossSword*> _vBossSword;
	bool			_makeSword;
	bool			_shootSword;
	bool			_readySword;
	int				_readySwordCount;
	float			_firstSwordX;
	float			_firstSwordY;
	int				_makeSwordTimer;
	int				_swordCount;
	int				_shootSwordTimer;
	int				_swordEndCount;
	bool			_playSound;

	bossHands		_leftHandle;
	bossHands		_RightHandle;

	int				_backEffectCount;
	
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void SetAfterSpawn();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	SetPattern();
	virtual void	GetDamage();
	virtual void	GetDamage(int damage);



	float MoveLerp(float y1, float y2, float amount);
	//KNIFE Pattern
	 void	SetSword();
	 void	SwordHit();
	 void	SetSwordAngle();
	 void	SwordPixelCollision();
	 void	EraseSword();

	 void	SetBelial();
	 void	SetHpBar();
};

