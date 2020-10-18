#pragma once
#include"enemy.h"
class FireBat : public Enemy
{
private:
	int		_stateTimer;
	int		_rndAngle;
	bool	_isAtk;
	bool	_leftAtk;
	float	_probeBottom;
	float	_fireAngle;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	PixelCollision();
};

