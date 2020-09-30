#pragma once
#include "enemy.h"

enum BELIALPATTERN
{
	RAZER, KNIFE, BULLET
};

class Belial : public Enemy
{
private:
	BELIALPATTERN _BelialPattern;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
};

