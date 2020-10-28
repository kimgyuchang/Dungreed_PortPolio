#include "stdafx.h"
#include "PurpleBat.h"

HRESULT PurpleBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_isAtk = false;
	_initHp = _hp = 30;
	_attackCoolTime = 0;
	_damage = 0;

	return S_OK;
}

void PurpleBat::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		PixelCollision();
		Animation();
		Move();
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
		else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
	}
}

void PurpleBat::release()
{
}

void PurpleBat::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
		if (INPUT->GetKey(VK_F6)) CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void PurpleBat::Move()
{
	switch (_state)
	{
	case ES_IDLE:
		_stateTimer++;

		if (_stateTimer > 100)
		{
			_rndAngle = RANDOM->range(1, 359);
			_stateTimer = 0;
			_state = ES_MOVE;
		}
		break;
	case ES_MOVE:
		_stateTimer++;
		_x += cosf(_rndAngle * PI / 180) * 2;
		_y += -sinf(_rndAngle * PI / 180) * 2;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("BatIdle")->getFrameWidth(), IMAGEMANAGER->findImage("BatIdle")->getFrameHeight());
		if (_stateTimer == 300)
		{
			_rndAngle = RANDOM->range(_rndAngle + 90, _rndAngle + 270);
		}

		if (_stateTimer > 500)
		{
			_stateTimer = 0;
			_state = ES_IDLE;
		}
		break;
	default:
		break;
	}
}

void PurpleBat::Animation()
{
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{

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
		else
		{
			_count++;

			_frameY = 1;
			if (_count % 5 == 0)
			{

				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}

		break;
	case ES_MOVE:
		_useImage = 0;
		if (_isLeft)
		{

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
		else
		{
			_count++;

			_frameY = 1;
			if (_count % 5 == 0)
			{

				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}

		break;
	default:
		break;
	}

}

void PurpleBat::PixelCollision()
{
	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* purpleBatIg = IMAGEMANAGER->findImage("BatIdle");

	_probeBottom = _y + purpleBatIg->getFrameHeight();

	for (int i = _probeBottom - 2; i < _probeBottom + 1; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + purpleBatIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_y = i - purpleBatIg->getFrameHeight();
			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i - purpleBatIg->getFrameHeight();
			break;
		}
	}

	for (int i = _y + 2; i > _y - 1; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + purpleBatIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_y = i;
			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{
			_y = i;
			break;
		}
	}

	for (int i = _x + purpleBatIg->getFrameWidth() - 2; i < _x + purpleBatIg->getFrameWidth() + 1; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + purpleBatIg->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_x = i - purpleBatIg->getFrameWidth();
			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i - purpleBatIg->getFrameWidth();
			break;
		}
	}
	for (int i = _x + 2; i > _x - 1; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + purpleBatIg->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_x = i;
			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{
			_x = i;
			break;
		}
	}
}
