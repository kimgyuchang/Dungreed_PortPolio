#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	
	return S_OK;
}

void Enemy::update()
{
	Object::update();
}

void Enemy::release()
{
	Object::release();
}

void Enemy::render(HDC hdc)
{
	Object::render(hdc);
}

void Enemy::Move()
{
}

void Enemy::Attack()
{
}

void Enemy::Animation()
{
}
