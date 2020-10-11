#pragma once
#include "Enemy.h"
struct Bow
{
	image* bowIg;
	int frameX;
	int frameY;
	float angle;
};
class BowSkel : public Enemy
{
private:
	int		_stateTimer;
	bool	_isAtk;
	bool	_leftAtk;
	float	_probeBottom;
	int		_hp;
	Bow		_skelBow;
	vector<Bullet*> _vSkelBullet;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);


	virtual void	Attack();
	virtual void	Animation();
	
};

