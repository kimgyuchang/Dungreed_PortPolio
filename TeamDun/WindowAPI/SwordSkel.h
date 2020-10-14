#pragma once
#include "Enemy.h"
#define PI 3.141592

struct Sword
{
	image*		 swordIg;
	int			 frameX;
	int			 frameY;
	float		 angle;
};

class SwordSkel : public Enemy
{
private:
	float		_probeBottom;
	float		_gravity;
	float		_jumpPower;
	bool		_isJump;
	bool		_isAttack;
	bool		_downJump;
	bool		_effectGenerated;
	int			_jumpCount;
	int			_jumpTimer;
	int			_downJmpTimer;
	int			_attackTimer;
	int			_effectTimer;
	int			_effect;
	int			_swordX, _swordY;
	Sword		_skelSword;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	pixelCollision();
};

