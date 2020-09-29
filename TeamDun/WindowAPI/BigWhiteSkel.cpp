#include "stdafx.h"
#include "BigWhiteSkel.h"

HRESULT BigWhiteSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	_enemy = new Enemy;

	_enemy->Setimage(1, _bigWhiteSkelImg);
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
	_enemy->Setimage(3, _bigWhiteSkelImg);
}

void BigWhiteSkel::Attack()
{
	Enemy::Attack();
	_enemy->Setimage(3, _bigWhiteSkelImg);
}

void BigWhiteSkel::Animation()
{
	Enemy:Animation();
}
