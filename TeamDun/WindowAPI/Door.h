#pragma once
#include "Object.h"
class Door : public Object
{
private :
	DIRECTION	_dir;
public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();

	void		SetDirection(DIRECTION dir) { _dir = dir; }
	DIRECTION	GetDirection() { return _dir; }

};

