#include "stdafx.h"
#include "Minotaurs.h"

HRESULT Minotaurs::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_body = RectMake(_x, _y, 156, 150);
	_state = ES_IDLE;

	_dashTimer = _movePoint = 0;
	_attackCount = _attackIndexFix = 0;
	_attackCoolTime = 100 + RANDOM->range(40);
	_index = _count = 0;
	_effectTimer = _effect = 0;
	_MoveTimer = 0;
	_frameX, _frameY = 0;
	_initHp = _HP = 80;
	_moveSpeed = 10;
	_gravity = 10.0f;
	_isLeft = _isAttack = _isDash = false;
	_Damage = 14;
	_attackAnimFrame = vector<int>{ 3,3,30,5,5,5,5 };
	_MoveAnimFrame = vector<int>{ 3,3,3,30,5,5,5,5 };
	_dashEffect = nullptr;

	return S_OK;
}

void Minotaurs::update()
{
	Enemy::update();

	if (_isSpawned)
	{
		switch (_state)
		{
		case ES_IDLE:
			

			if (abs(_x - ENTITYMANAGER->getPlayer()->GetX()) < 500 && abs(_y - ENTITYMANAGER->getPlayer()->GetY()) < 100)
			{
				_MoveTimer++;

				if (_MoveTimer > 200)
				{
					if (abs(_x + _vImages[0]->getFrameWidth() / 2 - ENTITYMANAGER->getPlayer()->GetX()) < 85)
					{
						_state = ES_ATTACK;
						if (_isLeft)
						{
							_frameX = 0;
						}
						else
						{
							_frameX = _vImages[2]->getMaxFrameX();
							
						}
					}
					else
					{
						_state = ES_MOVE;
						if (_isLeft)
						{
							_frameX = 0;
						}
						else
						{
							_frameX = _vImages[1]->getMaxFrameX();
						}
					}
					_MoveTimer = 0;

				}
				if (_x < ENTITYMANAGER->getPlayer()->GetX()) { _moveSpeed = 10; _isLeft = true; }
				else if (_x >= ENTITYMANAGER->getPlayer()->GetX()) { _moveSpeed = -10; _isLeft = false; }
			}
			break;
		case ES_MOVE:
			this->Move();
			
			break;
		case ES_ATTACK:
			_body = RectMake(_x, _y, 156, 150);

			_MoveTimer++;
			
			break;
		default:
			break;
		}
		this->Animation();
		this->pixelCollision();
	}

}

void Minotaurs::release()
{
}

void Minotaurs::render(HDC hdc)
{
	if (_isSpawned)
	{
		Enemy::render(hdc);
	}
}

void Minotaurs::Move()
{
	cout << _movePoint << endl;
	Enemy::Move();

	_body = RectMake(_x, _y, 156, 150);

	//이펙트
	_effectTimer++;

	if (_isLeft)
	{
		_effect = -100;
	}
	else
	{
		_effect = 10;
	}
	if (_effectTimer > 10)
	{
		EFFECTMANAGER->AddEffect(_x + _effect, _y + 45, "MinotaursDashEffect", 4, 0, _frameY, false, 150);
		_effectTimer = 0;
	}

	//대쉬
	_movePoint++;
	
	_x += _moveSpeed;


	RECT temp;
	if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
	{
		if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
		{
			float damage;
			float block;
			float evasion;

			damage = 20 * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100; // 대쉬시 충돌하면 기본 20데미지에서 계산
			evasion = RANDOM->range(100);
			block = RANDOM->range(100);
			if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
			{
				if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
				{
					ENTITYMANAGER->getPlayer()->SetIsHit(true);
					ENTITYMANAGER->getPlayer()->SetHitCount(0);
					ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
				}
			}
		}
		_movePoint = 101;
	}

	if (_movePoint > 100) // 혹은 충돌했을떄
	{
		_state = ES_ATTACK;
		if (_isLeft)
		{
			_frameX = 0;
		}
		else
		{
			_frameX = _vImages[2]->getMaxFrameX() ;
		}
		_movePoint = 0;
	}
}

void Minotaurs::Attack()
{
	Enemy::Attack();
}

void Minotaurs::Animation()
{
	Enemy::Animation();



	switch (_state)
	{
	case ES_IDLE:
		_count++;
		_useImage = 0;
		if (!_isLeft)
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
		_count++;
		_useImage = 1;
		if (_isLeft)
		{
			_frameY = 0;

			if (_frameX == 4)
			{
				if (_count > 5)
				{
					_frameX = 4;
					_count = 0;

					if (_frameX > _vImages[_useImage]->getMaxFrameX())
					{
						_frameX = 0;
					}
				}
			}
			else
			{
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
		}
		else
		{
			_frameY = 1;
			if (_frameX == 3)
			{
				if (_count > 5)
				{
					_count = 0;
					_frameX = 3;

					if (_frameX < 0)
					{
						_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
					}
				}
			}
			else
			{
				if (_count > 5)
				{
					_count = 0;
					_frameX--;

					if (_frameX < 0)
					{
						_frameX = _vImages[_useImage]->getMaxFrameX() - 1;
					}
				}
			}
		}

		break;
	case ES_ATTACK:
		_useImage = 2;
		if (_MoveTimer > 30)
		{
			_count++;
			if (_isLeft)
			{
				_frameY = 0;

				if (_count > _attackAnimFrame[_frameX])
				{
					_count = 0;
					_frameX++;
					if (_frameX == 3)
					{
						RECT temp;
						if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
						{
							if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
							{
								float damage;
								float block;
								float evasion;

								damage = _Damage * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100; // 대쉬시 충돌하면 기본 20데미지에서 계산
								evasion = RANDOM->range(100);
								block = RANDOM->range(100);
								if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
								{
									if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
									{
										ENTITYMANAGER->getPlayer()->SetIsHit(true);
										ENTITYMANAGER->getPlayer()->SetHitCount(0);
										ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
									}
								}
							}
						}
					}
					if (_frameX > _vImages[_useImage]->getMaxFrameX())
					{
						_state = ES_IDLE;
						_MoveTimer = 0;
						_frameX = 0;
					}
				}
			}
			else
			{
				_frameY = 1;
				if (_count > _attackAnimFrame[_vImages[_useImage]->getMaxFrameX() - _frameX])
				{
					_count = 0;
					_frameX--;

					if (_frameX == 3)
					{
						RECT temp;
						if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
						{
							if (ENTITYMANAGER->getPlayer()->GetIsHit() == false)
							{
								float damage;
								float block;
								float evasion;

								damage = _Damage * ENTITYMANAGER->getPlayer()->GetRealDefence() / 100; // 대쉬시 충돌하면 기본 20데미지에서 계산
								evasion = RANDOM->range(100);
								block = RANDOM->range(100);
								if (ENTITYMANAGER->getPlayer()->GetRealEvasion() <= evasion)
								{
									if (ENTITYMANAGER->getPlayer()->GetBlock() <= block)
									{
										ENTITYMANAGER->getPlayer()->SetIsHit(true);
										ENTITYMANAGER->getPlayer()->SetHitCount(0);
										ENTITYMANAGER->getPlayer()->SetHp(ENTITYMANAGER->getPlayer()->GetHP() - damage);
									}
								}
							}
						}
					}
					if (_frameX < 0)
					{
						_frameX = _vImages[_useImage]->getMaxFrameX();
						_state = ES_IDLE;
						_MoveTimer = 0;
						_attackIndexFix = 0;
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void Minotaurs::pixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* MinotaursIdle = IMAGEMANAGER->findImage("MinotaursIdle");

	_probeBottom = _y + MinotaursIdle->getFrameHeight();

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + 11, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			isCollide = true;

			_y = i - _vImages[_useImage]->getFrameHeight();

			break;
		}
		if ((r == 0 && g == 0 && b == 255))
		{
			isCollide = true;

			_y = i - _vImages[_useImage]->getFrameHeight();
			break;
		}
	}
	if (_isLeft)
	{

		for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
		{
			COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + MinotaursIdle->getFrameWidth() - 11, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				isCollide = true;

				_y = i - MinotaursIdle->getFrameHeight();

				break;
			}

			if ((r == 0 && g == 0 && b == 255))
			{
				isCollide = true;

				_y = i - MinotaursIdle->getFrameHeight();
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

			if ((r == 255 && g == 0 && b == 0))
			{
				isCollide = true;

				_y = i - _vImages[_useImage]->getFrameHeight();

				break;
			}

			if ((r == 0 && g == 0 && b == 255))
			{
				isCollide = true;
				
				_y = i - _vImages[_useImage]->getFrameHeight();

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
			_y = i;

			break;
		}
	}
	if (!isCollide)
	{
		_y += _gravity;

		_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	}

	for (int i = _x + MinotaursIdle->getFrameWidth() - 15; i < _x + MinotaursIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 &&_RightCollision2)
			{
				_x = i - MinotaursIdle->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + MinotaursIdle->getFrameWidth() - 15; i < _x + MinotaursIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 40);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - MinotaursIdle->getFrameWidth();
			break;
		}

	}
	for (int i = _x + MinotaursIdle->getFrameWidth() - 15; i < _x + MinotaursIdle->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - MinotaursIdle->getFrameWidth();


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

			if (_leftCollision1 &&_leftCollision2)
			{
				_x = i - _vImages[_useImage]->getFrameWidth();

			}

			break;
		}
	}
	//왼쪽중간
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, _probeBottom - 40);
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