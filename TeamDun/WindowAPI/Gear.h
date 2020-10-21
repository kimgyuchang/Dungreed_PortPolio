#pragma once
#include "Obstacle.h"
class Gear : public Obstacle
{
private:
	float _angle;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	CheckCollision();
};

