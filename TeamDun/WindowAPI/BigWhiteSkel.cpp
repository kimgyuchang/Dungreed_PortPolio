#include "stdafx.h"
#include "BigWhiteSkel.h"

HRESULT BigWhiteSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 99, 120);
	_state = ES_IDLE;

	_index = _count = _jumpCount = _downJmpTimer = _jumpTimer = 0;
	_frameX, _frameY = 0;
	_attackCoolTime = RANDOM->range(40) + 80;
	_gravity = 0.5f;
	_jumpPower = 7.0f;
	_isLeft = _isAttack = _isJump = false;
	_initHp = _hp = 50;
	_attackAnimFrame = vector<int>{ 40,3,5,5,5,5,5,5,5,5,5,5 };
	_randomXPosTimer = RANDOM->range(30) + 70;
	_randomXPos = RANDOM->range(-200, 200);
	_damage = 12;

	return S_OK;
}

void BigWhiteSkel::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100)
			{
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			_body = RectMake(_x, _y, 99, 120);

			_randomXPosTimer--;

			if (abs(ENTITYMANAGER->getPlayer()->GetX() + _randomXPos - _x) < 10 || _randomXPosTimer < 0) // 랜덤 좌표와 거리 10 이하면 랜덤 좌표 재지정
			{
				_randomXPos = RANDOM->range(-200, 200);
				_randomXPosTimer = RANDOM->range(30) + 70;
			}

			else // 거리 10 이상 -> 부호에 따라 좌우 및 이동 지정
			{
				if (ENTITYMANAGER->getPlayer()->GetX() + _randomXPos - _x > 0)
				{
					_isLeft = true;
					_x += 3;
					_body = RectMake(_x, _y, 99, 120);
				}

				else
				{
					_isLeft = false;
					_x -= 3;
					_body = RectMake(_x, _y, 99, 120);
				}
			}

			if (ENTITYMANAGER->getPlayer()->GetX() - 70 <= _x && ENTITYMANAGER->getPlayer()->GetX() + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() + 70 >= _x)
			{
				_attackCoolTime--;

				if (_attackCoolTime < 0)
				{
					_attackCoolTime = RANDOM->range(40) + 80;
					_isAttack = true;
					_state = ES_ATTACK;
					if (_isLeft)
					{
						_frameX = 0;
					}
					if (!_isLeft)
					{
						_x = _x - 95;
						_frameX = 11;
					}
				}
				else
				{
					_isAttack = false;
				}
			}
			break;
		case ES_ATTACK:
			break;
		default:
			break;
		}

		this->Move();
		this->Animation();
		this->pixelCollision();
	}
}

void BigWhiteSkel::release()
{
}

void BigWhiteSkel::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);

		//CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void BigWhiteSkel::Move()
{
	Enemy::Move();

	_jumpTimer++;
	_body = RectMake(_x, _y, 99, 120);

	if (_y > ENTITYMANAGER->getPlayer()->GetY() && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && !_isAttack)
	{
		if (_jumpTimer > 40)
		{
			_jumpTimer = 0;
			if (_jumpCount == 0)
			{
				_jumpPower = 10;
				_y -= _jumpPower;
				_probeBottom = _y + IMAGEMANAGER->findImage("BigWhiteSkelIdle")->getFrameHeight();
				_jumpCount++;
			}
		}
		if (_y + IMAGEMANAGER->findImage("BigWhiteSkelIdle")->getFrameHeight() <= ENTITYMANAGER->getPlayer()->GetY())
		{
			_downJump = true;
			_jumpPower = -1;
			_jumpCount++;
		}
		if (_downJump)
		{
			_downJmpTimer++;
			if (_downJmpTimer > 30)
			{
				_downJmpTimer = 0;
				_downJump = false;
			}
		}
	}
}

void BigWhiteSkel::Attack()
{
	Enemy::Attack();
}

void BigWhiteSkel::Animation()
{
	_count++;
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		break;
	case ES_MOVE:
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		break;
	case ES_ATTACK:
		_useImage = 2;
		if (_isLeft)
		{
			_frameY = 0;
			if (_count > _attackAnimFrame[_frameX])
			{
				_count = 0;
				_frameX++;

				if (_frameX == 3)
				{

					if (UTIL::interactRectArc(ENTITYMANAGER->getPlayer()->GetBody(), POINT{(LONG)_x+100 , (LONG)_y+70 }, _vImages[2]->getFrameWidth()-_vImages[1]->getFrameWidth()+20, 0, PI / 2, 10))
					{
						ENTITYMANAGER->getPlayer()->GetHitDamage(_damage);
					}
				}
				if (_frameX > _vImages[_useImage]->getMaxFrameX() - 1)
				{
					_state = ES_MOVE;
					_isAttack = false;
					_frameX = 0;
					_useImage = 1;
				}
			}
		}
		else
		{
			_body = RectMake(_x + 95, _y, 99, 120);
			_frameY = 1;
			if (_count > _attackAnimFrame[_vImages[_useImage]->getMaxFrameX() - _frameX])
			{
				_count = 0;
				_frameX--;
				if (_frameX == 9)
				{

					if (UTIL::interactRectArc(ENTITYMANAGER->getPlayer()->GetBody(), POINT{(LONG) _x + 100 , (LONG)_y + 70 }, _vImages[2]->getFrameWidth() - _vImages[1]->getFrameWidth() + 20, PI/2, PI , 10))
					{
						ENTITYMANAGER->getPlayer()->GetHitDamage(_damage);
					}
				}
				if (_frameX < 0)
				{
					_state = ES_MOVE;
					_isAttack = false;
					_frameX = 0;
					_x = _x + 95;
					_useImage = 1;
				}
			}
		}
		break;
	default:
		break;
	}
}

void BigWhiteSkel::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* skelIdleImg = IMAGEMANAGER->findImage("BigWhiteSkelIdle");

	_probeBottom = _y + skelIdleImg->getFrameHeight();

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + 11, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			isCollide = true;
			_isJump = false;
			_jumpPower = -2;

			_y = i - skelIdleImg->getFrameHeight();
			_jumpCount = 0;

			break;
		}
		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
		{
			isCollide = true;
			_jumpPower = -2;

			_y = i - skelIdleImg->getFrameHeight();
			_jumpCount = 0;
			break;
		}
	}
	if (_isLeft)
	{

		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + skelIdleImg->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - skelIdleImg->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - skelIdleImg->getFrameHeight();
				_jumpCount = 0;
				break;
			}
		}
	}
	else
	{
		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _vImages[_useImage]->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - skelIdleImg->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - skelIdleImg->getFrameHeight();
				_jumpCount = 0;
				break;
			}
		}
	}

	for (int i = _y + 15; i > _y - 4; i--)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _vImages[_useImage]->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);


		if ((r == 255 && g == 0 && b == 0))
		{
			_jumpPower = -2;
			_y = i + 5;

			break;
		}
	}
	if (!isCollide)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;

		_body = RectMake(_x, _y, skelIdleImg->getFrameWidth(), skelIdleImg->getFrameHeight());
	}

	for (int i = _x + skelIdleImg->getFrameWidth() - 15; i < _x + skelIdleImg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 && _RightCollision2)
			{
				_x = i - skelIdleImg->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + skelIdleImg->getFrameWidth() - 15; i < _x + skelIdleImg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 50);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - skelIdleImg->getFrameWidth();
			break;
		}

	}
	for (int i = _x + skelIdleImg->getFrameWidth() - 15; i < _x + skelIdleImg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - skelIdleImg->getFrameWidth();

			break;
		}
	}

	//왼쪽아래
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision1 = true;

			if (_leftCollision1 && _leftCollision2)
			{
				_x = i - skelIdleImg->getFrameWidth();

			}

			break;
		}
	}
	//왼쪽중간
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 50);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision2 = true;
			_x = i;

			break;
		}
	}
	//왼쪽위
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i;

			break;
		}
	}
}