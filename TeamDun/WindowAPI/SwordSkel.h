#pragma once
#include "Enemy.h"

class SwordSkel : public Enemy
{
private:
	float		_probeBottom;
	float		_gravity;
	float		_jumpPower;
	bool		_isJump;
	bool		_isAttack;
	bool		_downJump;
	int			_jumpCount;
	int			_jumpTimer;
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

