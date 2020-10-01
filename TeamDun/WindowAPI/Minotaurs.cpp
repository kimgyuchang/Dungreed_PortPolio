#include "stdafx.h"
#include "Minotaurs.h"

HRESULT Minotaurs::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 156, 114);

	_state = ES_IDLE;
	return S_OK;
}

void Minotaurs::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			break;
		case ES_MOVE:
			break;
		case ES_ATTACK:
			break;
		default:
			break;
		}
	}
}

void Minotaurs::release()
{
}

void Minotaurs::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Minotaurs::Move()
{
	Enemy::Move();
}

void Minotaurs::Attack()
{
	Enemy::Attack();
}

void Minotaurs::Animation()
{
	Enemy::Animation();
}
