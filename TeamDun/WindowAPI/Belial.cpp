#include "stdafx.h"
#include "Belial.h"

HRESULT Belial::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	return S_OK;
}

void Belial::update()
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
			switch (_BelialPattern)
			{
			case RAZER:
				break;
			case KNIFE:
				break;
			case BULLET:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Belial::release()
{
}

void Belial::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Belial::Move()
{
	Enemy::Move();
}

void Belial::Attack()
{
	Enemy::Attack();

	switch (_BelialPattern)
	{
	case RAZER:
		break;
	case KNIFE:
		break;
	case BULLET:
		break;
	default:
		break;
	}
}

void Belial::Animation()
{
	switch (_state)
	{
	case ES_IDLE:
		break;
	case ES_MOVE:
		break;
	case ES_ATTACK:
		switch (_BelialPattern)
		{
		case RAZER:
			break;
		case KNIFE:
			break;
		case BULLET:
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
