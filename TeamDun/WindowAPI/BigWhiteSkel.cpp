#include "stdafx.h"
#include "BigWhiteSkel.h"

HRESULT BigWhiteSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 99, 90);
	_state = ES_IDLE;

	_index = _count = _jumpCount = _downJmpTimer = _attackCoolTime = _jumpTimer = 0;
	_frameX, _frameY = 0;

	_gravity = 0.4f;
	_jumpPower = 7.0f;

	_isLeft = _isAttack = false;

	return S_OK;
}

void BigWhiteSkel::update()
{
	Enemy::update();

	this->Move();
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
			if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x)
			{
				_isLeft = true;
				_x += 3;
			}
			else if (ENTITYMANAGER->getPlayer()->GetX() + 70 < _x)
			{
				_isLeft = false;
				_x -= 3;
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
						_x = _x - 65;
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
					_x = _x + 65;
				}
			}
			break;
		default:
			break;
		}
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
	}
}

void BigWhiteSkel::Move()
{
	Enemy::Move();

	if (_y > ENTITYMANAGER->getPlayer()->GetY() && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 200 && !_isAttack)
	{
		if (_jumpTimer % 40 == 0)
		{
			if (_jumpCount == 0)
			{
				_jumpPower = 10;
				_y -= _jumpPower;
				_probeBottom = _y + IMAGEMANAGER->findImage("BigWhiteSkelIdle")->getFrameHeight();
				_jumpCount++;
			}
		}
		if (_y < ENTITYMANAGER->getPlayer()->GetY())
		{
			_downJump = true;
			_jumpPower = -1;
			_jumpCount++;
		}
		if (_downJump)
		{
			_downJmpTimer++;
			if (_downJmpTimer > 20)
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
		_useImage = 2;
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

void BigWhiteSkel::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	COLORREF colorRightBottom1;
	COLORREF colorRightBottom2;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* skelIdleImg = IMAGEMANAGER->findImage("BigWhiteSkelIdle");

	_probeBottom = _y + skelIdleImg->getFrameHeight();

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x +11, i);
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
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + skelIdleImg->getFrameWidth()-11, i);
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

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - _vImages[_useImage]->getFrameHeight() +10;
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

	for (int i = _x + skelIdleImg->getFrameWidth() - 15; i < _x + skelIdleImg->getFrameWidth() + 5; i++)
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
				_x = i - skelIdleImg->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + skelIdleImg->getFrameWidth() - 15; i < _x + skelIdleImg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 50);
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
		COLORREF color = GetPixel(_vImages[_useImage]->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - skelIdleImg->getFrameWidth();


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
				_x = i - _vImages[_useImage]->getFrameWidth();

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