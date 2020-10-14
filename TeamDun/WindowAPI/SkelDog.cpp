#include "stdafx.h"
#include "SkelDog.h"

HRESULT SkelDog::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 60, 54);
	_state = ES_IDLE;
	_frameX, _frameY = 0;

	_count = _index = _attackCoolTime = _jumpTimer = _jumpCount = 0;
	_initHp = _HP = 30;
	_gravity = 0.4f;
	_jumpPower = 7.0f;

	_isAttack = _isJump = false;

	return S_OK;
}

void SkelDog::update()
{
	Enemy::update();

	this->Move();
	this->Attack();
	this->Animation();
	this->pixelCollision();

	_attackCoolTime++;
	_jumpTimer++;

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200)
			{
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			_body = RectMake(_x, _y, 60, 54);
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)
			{
				_isLeft = true;
				_x += 4;
			}
			else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)
			{
				_isLeft = false;
				_x -= 4;
			}
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 < _x && ENTITYMANAGER->getPlayer()->GetX() + 70 > _x)
			{
				if (_attackCoolTime % 50 == 0)
				{
					_isAttack = true;
				}
				if (_isAttack)
				{
					_state = ES_ATTACK;

					if (_x < ENTITYMANAGER->getPlayer()->GetX() + 20)
					{
						_isLeft = true;
					}
					else
					{
						_isLeft = false;
					}
				}
			}
			break;
		case ES_ATTACK:
			if (_isLeft && _frameX >= _vImages[_useImage]->getMaxFrameX())
			{
				if (_count % 5 == 0)
				{
					_state = ES_IDLE;
					_isAttack = false;
				}
			}
			else if (!_isLeft && _frameX <= 0)
			{
				if (_count % 5 == 0)
				{
					_state = ES_IDLE;
					_isAttack = false;
				}
			}
			break;
		default:
			break;
		}
	}
}

void SkelDog::release()
{
	Enemy::release();
}

void SkelDog::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void SkelDog::Move()
{
	Enemy::Move();

	_body = RectMake(_x, _y, 60, 54);
}

void SkelDog::Attack()
{
	Enemy::Attack();

	if (abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100 && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && _isAttack)
	{
		if (_jumpTimer > 100)
		{
			_jumpTimer = 0;
			if (_jumpCount == 0)
			{
				_jumpPower = 10;
				_y -= _jumpPower;
				_probeBottom = _y + IMAGEMANAGER->findImage("SkelDogIdle")->getFrameHeight();
				_jumpCount++;
			}
		}
	}
}

void SkelDog::Animation()
{
	Enemy::Animation();
	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;
		if (_isLeft)
		{
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
		else
		{
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
		break;
	case ES_MOVE:
		_useImage = 1;
		if (_isLeft)
		{
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
		_useImage = 1;
		if (_isLeft)
		{
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

void SkelDog::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* SkelDogIdle = IMAGEMANAGER->findImage("SkelDogIdle");

	_probeBottom = _y + SkelDogIdle->getFrameHeight();

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + 11, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			isCollide = true;
			_isJump = false;
			_jumpPower = -2;

			_y = i - _vImages[_useImage]->getFrameHeight();
			_jumpCount = 0;

			break;
		}
		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
		{
			isCollide = true;
			_jumpPower = -2;

			_y = i - _vImages[_useImage]->getFrameHeight();
			_jumpCount = 0;
			break;
		}
	}
	if (_isLeft)
	{

		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + SkelDogIdle->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SkelDogIdle->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SkelDogIdle->getFrameHeight();
				_jumpCount = 0;
				break;
			}
		}
	}
	else
	{
		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + _vImages[_useImage]->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - _vImages[_useImage]->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - _vImages[_useImage]->getFrameHeight() ;
				_jumpCount = 0;
				break;
			}
		}
	}

	for (int i = _y + 15; i > _y - 4; i--)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + _vImages[_useImage]->getFrameWidth() / 2, i);
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

		_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	}

	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 &&_RightCollision2)
			{
				_x = i - SkelDogIdle->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 50);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - SkelDogIdle->getFrameWidth();
			break;
		}

	}
	for (int i = _x + SkelDogIdle->getFrameWidth() - 15; i < _x + SkelDogIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(_vImages[_useImage]->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - SkelDogIdle->getFrameWidth();


			break;
		}
	}

	//¿ÞÂÊ¾Æ·¡
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision1 = true;

			if (_leftCollision1 &&_leftCollision2)
			{
				_x = i;

			}

			break;
		}
	}
	//¿ÞÂÊÁß°£
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 50);
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
	//¿ÞÂÊÀ§
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _y + 2);
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
