#pragma once
#include "enemy.h"

class SkelDog : public Enemy
{
private:
	float		_probeBottom;
	float		_gravity;
	float		_jumpPower;
	bool		_isAttack;
	bool		_isJump;
	int			_jumpTimer;
	int			_jumpCount;
	int			_randomXPos;
	int			_randomXPosTimer;
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

