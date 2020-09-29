#include "stdafx.h"
#include "BigWhiteSkel.h"

HRESULT BigWhiteSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(WINSIZEX / 2, WINSIZEY / 2, 99, 90);

	_state = ES_IDLE;

	return S_OK;
}

void BigWhiteSkel::update()
{
	cout << _state << endl;
	switch (_state)
	{
	case ES_IDLE:
		if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()+ 20) < 100)
		{
			_state = ES_MOVE;
		}
		break;
	case ES_MOVE:
		if (ENTITYMANAGER->getPlayer()->GetX() - 20 > _x)
		{
			_x += 3;
		}
		else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)
		{
			_x -= 3;
		}
		if (ENTITYMANAGER->getPlayer()->GetX() - 20 < _x && ENTITYMANAGER->getPlayer()->GetX() + 70 > _x)
		{
			_state = ES_ATTACK;
		}
		break;
	case ES_ATTACK:
		break;
	default:
		break;
	}
}

void BigWhiteSkel::release()
{
}

void BigWhiteSkel::render(HDC hdc)
{
	Enemy::render(hdc);
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
