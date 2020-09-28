#pragma once

#include "singletonBase.h"
#include "Bullet.h"
#include "player.h"

class EntityManager : public singletonBase<EntityManager>
{
private :
	vector<Object*>		_vObjs;
	vector<Bullet*>		_vBullets;
	Player*				_p;

public :
	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
};

