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

	// GETSET //
	vector<Object*>&	getVObjs()		{ return _vObjs; }
	vector<Bullet*>&	getVBullets()	{ return _vBullets; }
	Player*				getPlayer()		{ return _p; }
	void				setPlayer(Player* p) { _p = p; }

	Bullet* makeBullet(const char* imageName, string effectIgName, BULLETTYPE type, float x, float y, float angle, float speed, float maxDis, bool isFrame);
	void eraseBullet();
};

