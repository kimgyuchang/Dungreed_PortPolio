#pragma once
#include "enemy.h"


class RedGiantBat : public Enemy
{
private:
	int		_stateTimer;
	int		_rndAngle;
	bool	_isAtk;
	bool	_leftAtk;
	bool    _ReadyBullet;
	bool	_bulletStop;

	int		_ReadyBulletTime;
	int		_bulletCount;
	int		_shootCount;
	float	_probeBottom;
	float	_angle;

	vector<Bullet*> _vBatBullet;


public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);


	virtual void	Attack();
	virtual void	Animation();
	virtual void	SetIsDead(bool isDead);
};

