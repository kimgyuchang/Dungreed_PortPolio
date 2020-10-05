#pragma once
#include "enemy.h"

class LittleGhost : public Enemy
{
private:
	int _attackTime;
	int _moveTimer;
	int _moveCoolTime;
	float _realMoveX, _realMoveY;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	void GetNewMoveXY();

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	pixelCollision();
};

