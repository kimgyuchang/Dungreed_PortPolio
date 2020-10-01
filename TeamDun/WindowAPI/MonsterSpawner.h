#pragma once
#include "Object.h"
#include "FieldMap.h"

class MonsterSpawner : public Object 
{
private :
	bool		_isOff;
	FieldMap*	_belongMap;
public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual void	CheckCollision();
	virtual	void	release();
	virtual void	render(HDC hdc);

	// GETSET //
	FieldMap* GetBelongMap() { return _belongMap; }
	bool GetIsOff() { return _isOff; }
	void SetBelongMap(FieldMap* map) { _belongMap = map; }
	void SetIsOff(bool isOff) { _isOff = isOff; }
};

