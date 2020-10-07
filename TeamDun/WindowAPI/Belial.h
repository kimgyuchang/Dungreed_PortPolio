#pragma once
#include "enemy.h"

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
	RECT body;
	int Timer;
	int frameX;
	int frameY;
	
};
class Belial : public Enemy
{
private:
	image*		_bossBack;
	BELIALPATTERN _BelialPattern;
	float		 _angle;
	float		_PatternTime;
	float		_fireAngle;
	int			_bulletFireTimer;
	int			_bulletEndTimer;
	
	
	vector<BossSword*> _vBossSword;
	bool _makeSword;
	bool _shootSword;
	float _firstSwordX;
	float _firstSwordY;
	int _makeSwordTimer;
	int _swordCount;
	int _shootSwordTimer;
	int _swordEndCount;


	bossHands _leftHandle;
	bossHands _RightHandle;


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

	//KNIFE Pattern
	virtual void	SetSword();
	virtual void	SwordAniMation();
	virtual void	SetSwordAngle();
	virtual void	SwordPixelCollision();
	virtual void	EraseSword();
};

