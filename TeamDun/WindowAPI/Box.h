#pragma once
#include "Object.h"

enum BOXTYPE
{
	BOX_SMALLBOX, BOX_BIGBOX, BOX_ORC
};

class Box : public Object
{
private :
	BOXTYPE			_boxType;
	vector<image*>	_vParticles;

public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	GetDamage();

	void SetParticle();
	void SetBoxType(BOXTYPE type) { _boxType = type; }
};

