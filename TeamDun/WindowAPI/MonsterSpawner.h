#pragma once
#include "Object.h"
#include "FieldMap.h"

class MonsterSpawner : public Object 
{
private :
	bool		_isOff;
public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual void	CheckCollision();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void SetToSpawnMonsters();

	// GETSET //
	bool		GetIsOff()		{ return _isOff; }

	void		SetIsOff(bool isOff)		{ _isOff = isOff; }
};

