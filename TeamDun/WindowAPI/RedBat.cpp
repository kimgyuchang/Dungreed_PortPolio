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
		Animation();
	}
}

void RedBat::release()
{
}

void RedBat::render(HDC hdc)
{
	
	if (_isSpawned)
	{
		Enemy::render(hdc);
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
	_useImage = 0;
	_count++;

	_frameY = 0;
	if (_count % 5 == 0)
		{
		
			_frameX++;

			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_frameX = 0;
			}
		}

}
