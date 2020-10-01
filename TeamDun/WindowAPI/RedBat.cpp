#include "stdafx.h"
#include "RedBat.h"

HRESULT RedBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	return S_OK;
}

void RedBat::update()
{
	Enemy::update();

	if (_isSpawned)
	{

	}
}

void RedBat::release()
{
}

void RedBat::render(HDC hdc)
{
	Enemy::render(hdc);
	
	if (_isSpawned)
	{

	}
}

void RedBat::Move()
{
	// 구현
}

void RedBat::Attack()
{
	// 구현
}

void RedBat::Animation()
{
	// 구현
}
