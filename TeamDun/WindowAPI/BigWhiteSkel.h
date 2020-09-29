#pragma once
#include "enemy.h"

enum STATE
{
	IDLE,
	MOVE,
	ATTACK
};

class BigWhiteSkel : public Enemy
{
private:
	Enemy* _enemy;
	image* _bigWhiteSkelImg;
	RECT _SkelRc;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
};