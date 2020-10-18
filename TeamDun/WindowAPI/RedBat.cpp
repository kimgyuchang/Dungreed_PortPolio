#include "stdafx.h"
#include "RedBat.h"

HRESULT RedBat::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_state = ES_IDLE;
	_stateTimer = 0;
	_isAtk = false;
	_initHp = _HP = 30;
	_attackCoolTime = 200 + RANDOM->range(150);

	_Damage = 10;
	return S_OK;
}

void RedBat::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		PixelCollision();
		Animation();
		Move();
		Attack();
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)  _isLeft = true;
		else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)  _isLeft = false;
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
		if (INPUT->GetKey(VK_F6)) CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void RedBat::Move()
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
		_x += cosf(_rndAngle*PI / 180)* 2;
		_y += -sinf(_rndAngle*PI / 180) * 2;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("BatRedIdle")->getFrameWidth(), IMAGEMANAGER->findImage("BatRedIdle")->getFrameHeight());
		if (_stateTimer == 300)
		{
			_rndAngle = RANDOM->range(_rndAngle+90, _rndAngle+270);
		}
		
		if (_stateTimer > 500)
		{
			_stateTimer = 0;
			_state = ES_IDLE;
		}
		break;
	case ES_ATTACK:
		break;
	default:
		break;
	}
}

void RedBat::Attack()
{
	if (!_isAtk)
	{
		_attackCoolTime--;
		if (_attackCoolTime < 0)
		{
			_attackCoolTime = 200 + RANDOM->range(150);
			_isAtk = true;	
			_useImage = 1;
			if (_isLeft)
			{
				_frameX = 0;
				_leftAtk = true;
			}
			else
			{
				_frameX = _vImages[_useImage]->getMaxFrameX();
				_leftAtk = false;
			}
			_state = ES_ATTACK;
		}
	}
}

void RedBat::Animation()
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
	case ES_ATTACK:
		
		if (_leftAtk)
		{

			_count++;

			_frameY = 0;
			if (_count % 10 == 0)
			{

				_frameX++;
				if (_frameX == _vImages[_useImage]->getMaxFrameX() / 2)
				{

					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit",BT_NOMAL ,_x, _y,
						getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y),
							CAMERAMANAGER->GetRelativeX(ENTITYMANAGER->getPlayer()->GetX()),  CAMERAMANAGER->GetRelativeY(ENTITYMANAGER->getPlayer()->GetY())), _Damage,
						10, 1000, true);
				}
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
					
					_state = ES_IDLE;
					_isAtk = false;
				}
			}
		}
		else
		{
			_count++;

			_frameY = 1;
			if (_count % 10 == 0)
			{

				_frameX--;
				if (_frameX == _vImages[_useImage]->getMaxFrameX() / 2)
				{

					ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOMAL, _x, _y,
						getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y),
							CAMERAMANAGER->GetRelativeX(ENTITYMANAGER->getPlayer()->GetX() ), CAMERAMANAGER->GetRelativeY(ENTITYMANAGER->getPlayer()->GetY())),_Damage,
						10, 1000, true);
				}
				if (_frameX < 0)
				{
					
					_state = ES_IDLE;
					_isAtk = false;
				}
			}
		}
		break;
	default:
		break;
	}
	
}

void RedBat::PixelCollision()
{
	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* RedBatIg = IMAGEMANAGER->findImage("BatRedIdle");

	_probeBottom = _y + RedBatIg->getFrameHeight();

	
	for (int i = _probeBottom - 2; i < _probeBottom + 1; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + RedBatIg->getFrameWidth()/2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{

			_y = i - RedBatIg->getFrameHeight();


			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{

			_y = i - RedBatIg->getFrameHeight();

			break;
		}
	}
	
	for (int i = _y + 2; i > _y -1; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + RedBatIg->getFrameWidth()/2, i);
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

	for (int i = _x + RedBatIg->getFrameWidth() - 2; i < _x + RedBatIg->getFrameWidth() + 1; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + RedBatIg->getFrameHeight()/2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{

			_x = i - RedBatIg->getFrameWidth();


			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{

			_x = i - RedBatIg->getFrameWidth();

			break;
		}
	}
	for (int i = _x + 2; i > _x - 1; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + RedBatIg->getFrameHeight() / 2);
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
