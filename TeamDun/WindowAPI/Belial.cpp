#include "stdafx.h"
#include "Belial.h"

HRESULT Belial::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_angle = -1.5;
	_state = ES_IDLE;
	_leftHandle = IMAGEMANAGER->findImage("SkellBossLeftHandIdle");
	_rightHandle = IMAGEMANAGER->findImage("SkellBossRightHandIdle");
	return S_OK;
}

void Belial::SetAfterSpawn()
{
	_leftHandleX = _x - 290;
	_leftHandleY = _y;
	_rightHandleX = _x + 150;
	_rightHandleY = _y;
}

void Belial::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		Animation();
		switch (_state)
		{
		case ES_IDLE:
			Move();
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
		CAMERAMANAGER->FrameRender(hdc, _leftHandle, _leftHandleX, _leftHandleY, 0, 0);

	}
}

void Belial::Move()
{
	_angle += 0.1f;
	_y += sinf(_angle) * 1;
}

void Belial::Attack()
{
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
		_useImage = 0;

		_count++;

		_frameY = 0;
		if (_count % 3 == 0)
		{

			_frameX++;

			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_frameX = 0;
			}
		}

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
