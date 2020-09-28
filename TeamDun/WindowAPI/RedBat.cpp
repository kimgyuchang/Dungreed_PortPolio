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
	// 备泅
}

void RedBat::Move()
{
	// 备泅
}

void RedBat::Attack()
{
	// 备泅
}

void RedBat::Animation()
{
	// 备泅
}
