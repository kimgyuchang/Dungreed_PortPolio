#pragma once
#include "enemy.h"

enum BELIALPATTERN
{
	RAZER, KNIFE, BULLET
};

class Belial : public Enemy
{
private:
	BELIALPATTERN _BelialPattern;
	float _angle;

	image* _leftHandle;
	image* _rightHandle;
	float _leftHandleX;
	float _leftHandleY;
	float _rightHandleX;
	float _rightHandleY;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void SetAfterSpawn();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
};

