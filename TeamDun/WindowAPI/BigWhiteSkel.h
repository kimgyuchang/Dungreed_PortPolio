#pragma once
#include "enemy.h"

class BigWhiteSkel : public Enemy
{
private:
	RECT		_collider[8];
	float		_probeBottom;
	float		_gravity;
	float		_jumpPower;
	bool		_isJump;
	bool		_isAttack;
	bool		_leftBack;
	bool		_rightBack;
	int			_jumpCount;
	int			_downJmpTimer;

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