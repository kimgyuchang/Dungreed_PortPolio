#pragma once
#include "Object.h"
class Coin : public Object
{
private :
	float _speedX;
	float _speedY;
	float _angle;
	float _gravity;

public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	void SetCoin(float x, float y, float speedX, float speedY);
	void Move();
	virtual void CheckCollision();
	void PixelCollision();
};

