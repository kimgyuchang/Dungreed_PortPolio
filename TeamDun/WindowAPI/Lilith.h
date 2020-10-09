#pragma once
#include "Enemy.h"

class Lilith : public Enemy
{
private:
	float _probeBottom;
	int _attackTimer;
	bool _isAttack;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
};

