#pragma once
#include "DropObjs.h"
class Coin : public DropObjs
{
private :

public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void SetCoin(float x, float y, float speedX, float speedY);
	virtual void CheckCollision();
};

