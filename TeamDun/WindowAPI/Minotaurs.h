#pragma once
#include "enemy.h"

class Minotaurs : public Enemy
{
private:
	bool _dash;
	float _friction;
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