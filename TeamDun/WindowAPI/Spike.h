#pragma once
#include "Object.h"
class Spike : public Object
{
private :
	
public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	CheckCollision();
};

