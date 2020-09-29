#include "stdafx.h"
#include "BigWhiteSkel.h"

HRESULT BigWhiteSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);

	_enemy->Setimage(1, _bigWhiteSkelIdle);
	_SkelRc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 99, 90);

	return S_OK;
}

void BigWhiteSkel::update()
{
	Enemy::update();
}

void BigWhiteSkel::release()
{
	Enemy::release();
}

void BigWhiteSkel::render(HDC hdc)
{
	Enemy::render(hdc);
	Rectangle(hdc, _SkelRc);
}

void BigWhiteSkel::Move()
{
	Enemy::Move();
}

void BigWhiteSkel::Attack()
{
	Enemy::Attack();
}

void BigWhiteSkel::Animation()
{
	Enemy:Animation();
}
