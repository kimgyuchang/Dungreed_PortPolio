#include "stdafx.h"
#include "RedBat.h"

HRESULT RedBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	return S_OK;
}

void RedBat::update()
{

}

void RedBat::release()
{
}

void RedBat::render(HDC hdc)
{
	// 구현
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
