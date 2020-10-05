#pragma once
#include "enemy.h"

class Minotaurs : public Enemy
{
private:
	bool		_isDash;
	bool		_isAttack;
	int			_dashTimer;
	int			_movePoint;
	int			_attackCount;
	int			_attackIndexFix;
	vector<int>	_attackAnimFrame;

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