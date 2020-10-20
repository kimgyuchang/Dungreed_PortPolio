#pragma once
#include "Object.h"
class PixieSpawner : public Object
{
private:
	bool		_isOff;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void SpawnPixie();

	// GETSET //
	bool		GetIsOff() { return _isOff; }

	void		SetIsOff(bool isOff) { _isOff = isOff; }
};

