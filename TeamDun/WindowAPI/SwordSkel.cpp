#include "stdafx.h"
#include "SwordSkel.h"

HRESULT SwordSkel::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 42, 57);
	_frameX = _frameY = 0;

	_count = _index = _jumpTimer = _downJmpTimer = _attackTimer = _effectTimer = _effect = 0;
	_attackCoolTime = 40 + RANDOM->range(20);
	_gravity = 0.5;
	_jumpPower = 10.0f;
	_moveSpeed = 3;
	_initHp = _hp = 50;

	_Damage = 10;
	_swordX = _x;
	_swordY = _y;

	_isJump = _downJump = _isAttack = _isLeft = false;

	_skelSword.swordIg = IMAGEMANAGER->findImage("SkelSword");
	_skelSword.frameX = 0;
	_skelSword.frameY = 0;
	_skelSword.angle = PI;


	_state = ES_IDLE;
	_effectGenerated = false;

	return S_OK;
}

void SwordSkel::update()
{
	Enemy::update();
	_swordX = _x;
	_swordY = _y;
	if (_isSpawned)
	{
		this->Animation();
		this->pixelCollision();

		switch (_state)
		{
		case ES_IDLE:
			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 150 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 250)
			{
				if (_isLeft)
				{
					_skelSword.angle = 0;
				}
				if (!_isLeft)
				{
					_skelSword.angle = PI;
				}
				_moveSpeed = 3;
				_state = ES_MOVE;
			}
			break;
		case ES_MOVE:
			this->Move();
			if (ENTITYMANAGER->getPlayer()->GetX() > _x && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 250)
			{
				_skelSword.angle = 0;
				_isLeft = true;
				_x += _moveSpeed;
			}
			if (ENTITYMANAGER->getPlayer()->GetX()+70 <= _x && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 250)
			{
				_skelSword.angle = PI;
				_isLeft = false;
				_x -= _moveSpeed;
			}
			if (ENTITYMANAGER->getPlayer()->GetX() - 50 < _x &&
				ENTITYMANAGER->getPlayer()->GetX() + 50 + IMAGEMANAGER->findImage("SwordSkelIdle")->getFrameWidth() > _x)
			{
				_attackCoolTime--;
				_isAttack = true;
				_skelSword.angle = PI / 2;
				if (_attackCoolTime < 0)
				{
					_state = ES_ATTACK;
					_attackCoolTime = _attackCoolTime = 40 + RANDOM->range(20);
				}
			}
			break;
		case ES_ATTACK:

			this->Attack();
			_attackTimer++;
			_swordX = _x - 10;
			_swordY = _y - 5;
			if (_isLeft)
			{
				if (_attackTimer == 3)
				{

					if (UTIL::interactRectArc(ENTITYMANAGER->getPlayer()->GetBody(), POINT{ _swordX ,_swordY },_skelSword.swordIg->getWidth() ,0 ,PI/2 ,10))
					{
						ENTITYMANAGER->getPlayer()->GetHitDamage(_Damage);
					}
				}
				if (_attackTimer < 5)
				{
					_skelSword.angle -= 0.7f;
				}

			}
			if (!_isLeft)
			{
				if (_attackTimer == 3)
				{

					if (UTIL::interactRectArc(ENTITYMANAGER->getPlayer()->GetBody(), POINT{ _swordX ,_swordY }, _skelSword.swordIg->getWidth(), PI / 2, PI, 10))
					{
						ENTITYMANAGER->getPlayer()->GetHitDamage(_Damage);
					}
				}
				if (_attackTimer < 5)
				{
					_skelSword.angle += 0.7f;	
				}
			}
			if (_attackTimer > 50)
			{
				_state = ES_IDLE;
				_attackTimer = 0;
				_effectGenerated = false;
			}
			break;
		default:
			break;
		}
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
		if (_isLeft)
		{
			CAMERAMANAGER->FrameRender(hdc, _skelSword.swordIg, _swordX, _swordY, _skelSword.frameX, _skelSword.frameY, _skelSword.angle);
		}
		else
		{
			_swordX = _x - 45;
			CAMERAMANAGER->FrameRender(hdc, _skelSword.swordIg, _swordX, _swordY, _skelSword.frameX, _skelSword.frameY, _skelSword.angle);
		}
	}
}

void SwordSkel::Move()
{
	Enemy::Move();
	_body = RectMake(_x, _y, 42, 57);
	_jumpTimer++;
	if (abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 250 && abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 150 && !_isAttack)
	{
		if (_y - 20 > ENTITYMANAGER->getPlayer()->GetY())
		{
			if (_jumpTimer > 50)
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
		}
		if (_y + IMAGEMANAGER->findImage("SwordSkelIdle")->getFrameHeight() < ENTITYMANAGER->getPlayer()->GetY() && !_isAttack)
		{
			_downJump = true;
			_jumpPower = -1;
			_jumpCount++;
		}
		if (_downJump)
		{
			_downJmpTimer++;
			if (_downJmpTimer > 50)
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

	//ÀÌÆåÆ®
	_effectTimer++;

	if (_isLeft)
	{
		_effect = 70;
	}
	else
	{
		_effect = -90;
	}
	if (_effectTimer > 10 && !_effectGenerated)
	{
		if (_isLeft)
		{
			EFFECTMANAGER->AddEffect(_swordX + _effect, _swordY - 20, "SkelSwordEffect", 10, 0, 0, false, 200, 0, 1.3, 1.3);
		}
		if (!_isLeft)
		{
			EFFECTMANAGER->AddEffect(_swordX + _effect, _swordY - 20, "SkelSwordEffect", 10, 0, 0, false, 200, PI, 1.3, 1.3);
		}

		_effectGenerated = true;
	}
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
			_frameY = 0;
			_frameX = 0;
		}
		else
		{
			_frameY = 1;
			_frameX = 1;
		}
		break;
	case ES_MOVE:
		_useImage = 0;
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
		_useImage = 0;
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
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + 11, i);
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
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + SwordSkelIdle->getFrameWidth() - 11, i);
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
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _vImages[_useImage]->getFrameWidth() - 11, i);
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

				_y = i - _vImages[_useImage]->getFrameHeight();
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

		_body = RectMake(_x, _y, 42, 57);
	}

	for (int i = _x + SwordSkelIdle->getFrameWidth() - 4; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
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
				_x = i - SwordSkelIdle->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + SwordSkelIdle->getFrameWidth() - 4; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 50);
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
	for (int i = _x + SwordSkelIdle->getFrameWidth() - 4; i < _x + SwordSkelIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
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
	for (int i = _x + 4; i > _x - 5; i--)
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
				_x = i - _vImages[_useImage]->getFrameWidth();

			}

			break;
		}
	}
	//¿ÞÂÊÁß°£
	for (int i = _x + 4; i > _x - 5; i--)
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
	//¿ÞÂÊÀ§
	for (int i = _x + 4; i > _x - 5; i--)
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