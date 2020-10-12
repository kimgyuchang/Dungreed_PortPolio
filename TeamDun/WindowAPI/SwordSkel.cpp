#include "stdafx.h"
#include "SwordSkel.h"

HRESULT SwordSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 42, 57);
	_frameX = _frameY = 0;

	_count = _index = _jumpTimer = _downJmpTimer = 0;
	_gravity = 0.5;
	_jumpPower = 10.0f;
	_moveSpeed = 3;

	_isJump = _downJump = _isAttack = false;

	_state = ES_IDLE;

	return S_OK;
}

void SwordSkel::update()
{
	Enemy::update();

	this->Move();
	this->Animation();
	this->pixelCollision();

	switch (_state)
	{
	case ES_IDLE:
		if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 300 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 300)
		{
			_moveSpeed = 3;
			_state = ES_MOVE;
		}
		break;
	case ES_MOVE:
		_body = RectMake(_x, _y, 42, 57);
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 > _x && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100)
		{
			_isLeft = true;
			_x += _moveSpeed;
		}
		else if (ENTITYMANAGER->getPlayer()->GetX() + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() + 70 < _x)
		{
			_isLeft = false;
			_x -= _moveSpeed;
		}
		if (ENTITYMANAGER->getPlayer()->GetX() - 70 <= _x && ENTITYMANAGER->getPlayer()->GetX() + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() + 70 >= _x)
		{
		}
		break;
	case ES_ATTACK:
		break;
	default:
		break;
	}
}

void SwordSkel::release()
{
	Enemy::release();
}

void SwordSkel::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void SwordSkel::Move()
{
	Enemy::Move();

	_jumpTimer++;
	_body = RectMake(_x, _y, 42, 57);

	if (abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 300 && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 300 && !_isAttack)
	{
		if (_jumpTimer > 70)
		{
			_jumpTimer = 0;
			if (_jumpCount == 0)
			{
				_jumpPower = 10;
				_y -= _jumpPower;
				_probeBottom = _y + IMAGEMANAGER->findImage("SwordSkelIdle")->getFrameHeight();
				_jumpCount++;
			}
		}
		if (_y + IMAGEMANAGER->findImage("SwordSkelIdle")->getFrameHeight() <= ENTITYMANAGER->getPlayer()->GetY() && !_isAttack)
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

void SwordSkel::Attack()
{
	Enemy::Attack();
}

void SwordSkel::Animation()
{
	Enemy::Animation();

	_count++;

	switch (_state)
	{
	case ES_IDLE:
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 1;
			_frameX = 1;
		}
		else
		{
			_frameY = 0;
			_frameX = 0;
		}
		break;
	case ES_MOVE:
		_useImage = 0;
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
		_useImage = 0;
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

void SwordSkel::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* SwordSkelIdle = IMAGEMANAGER->findImage("SwordSkelIdle");

	_probeBottom = _y + SwordSkelIdle->getFrameHeight();

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
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + SwordSkelIdle->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SwordSkelIdle->getFrameHeight();
				_jumpCount = 0;

				break;
			}

			if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false)
			{
				isCollide = true;
				_jumpPower = -2;

				_y = i - SwordSkelIdle->getFrameHeight();
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

				_y = i - _vImages[_useImage]->getFrameHeight() + 10;
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

		_body = RectMake(_x, _y, 42, 57);
	}

	for (int i = _x + SwordSkelIdle->getFrameWidth() - 15; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
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
				_x = i - SwordSkelIdle->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + SwordSkelIdle->getFrameWidth() - 15; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 50);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - SwordSkelIdle->getFrameWidth();
			break;
		}

	}
	for (int i = _x + SwordSkelIdle->getFrameWidth() - 15; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(_vImages[_useImage]->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - SwordSkelIdle->getFrameWidth();


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