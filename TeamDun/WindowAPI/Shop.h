#pragma once
#include "NPC.h"
class Shop : public NPC
{
protected :

public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();

};

