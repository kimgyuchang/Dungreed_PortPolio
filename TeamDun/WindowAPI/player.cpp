#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{

	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1


	_x = 300;
	_y = WINSIZEY/2;
	_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	
	_useImage = 0;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	
	_frameX = 0;
	_frameY = 0;
	_gravity = 0.4f;
	_jumpPower = 7.0f;
	_jumpCount = 0;
	_downJmpTimer = 0;
	_dashTimer = 0;
	_dashSpeed = 0;

	_isDash = false;
	_leftBack = false;
	_rightBack = false;
	_bottomCol = false;


	_dashEffect = nullptr;
	return S_OK;
	
}

void Player::update()
{

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		_isDash = true;
		_dashPoint = _ptMouse;
		_jumpPower = 0;

		

	}

	if (INPUT->GetKeyDown('X'))
	{
		ENTITYMANAGER->makeBullet("BatBullet", _x,_y, getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _ptMouse.x, _ptMouse.y), 10,600, true);
	}

	if (CAMERAMANAGER->GetRelativeX(_x+ IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth()/2) >= _ptMouse.x)
	{
		_isLeft = true;
	}
	else
	{
		_isLeft = false;
	}


	
	this->pixelCollision();
	if (_isDash)
	{
		this->dash();
	}
	else
	{	
		this->Move();
	}
	
	Animation();
}

void Player::release()
{
}

void Player::render(HDC hdc)
{
	switch (_state)
	{
	case PS_IDLE:
		CAMERAMANAGER->FrameRender(hdc,IMAGEMANAGER->findImage("baseCharIdle"), _x, _y,_frameX,_frameY);
		break;
	case PS_JUMP:
		CAMERAMANAGER->FrameRender(hdc, IMAGEMANAGER->findImage("baseCharIdle"), _x, _y, _frameX, _frameY);
		break;
	case PS_MOVE:
		CAMERAMANAGER->FrameRender(hdc,IMAGEMANAGER->findImage("baseCharRun"), _x, _y,_frameX,_frameY);
		break;
	case PS_DIE:
		break;
	default:
		break;
	}
	//CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Player::Animation()
{
	switch (_state)
	{
	case PS_IDLE:
		_useImage = 0;

		break;
	case PS_JUMP:
		_useImage = 1;
		break;
	case PS_MOVE:
		_useImage = 1;
		
		break;
	case PS_DIE:
		break;
	default:
		break;
	}

	if (_isLeft)
	{
		_frameTimer++;
		_frameY = 1;
		if (!_leftBack)
		{

			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();  //여기랑
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
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
		_frameTimer++;
		_frameY = 0;
		if (!_rightBack)
		{

			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();  //여기랑
				}
			}
		}

	}
	
}

void Player::Move()
{
	_isJump = false;
	if (INPUT->GetKey('A'))
	{
		_leftBack = false;
		if (!_isLeft)
		{
			_rightBack = true;
		}

		_state = PS_MOVE;
		_x -= 5;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('A'))
	{
		_state = PS_IDLE;
	}
	if (INPUT->GetKey('D'))
	{
		if (_isLeft)
		{
			_leftBack = true;
		}
		_rightBack = false;
		_state = PS_MOVE;
		_x += 5;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}

	if (_jumpCount == 0 || _jumpCount ==1)
	{

		if (INPUT->GetKeyDown(VK_SPACE) && !_downJump)
		{
			_isJump = true;
			_jumpPower = 13;
			_y -= _jumpPower;
			_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
			_jumpCount++;
		}
		if (INPUT->GetKey('S') && _isJump)
		{
			_downJump = true;
			_jumpPower = -2;
			_jumpCount++;
		}
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

void Player::pixelCollision()
{
	//////////////////////////// 픽셀충돌 //////////////////////////////

	bool isCollide = false; // 충돌 했는지 여부
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;
	_bottomCol = false;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	
	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");

	

	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
		{
			isCollide = true; // 충돌했으면 얘를 ON
			_bottomCol = true; // 아래 충돌해있다
			_jumpPower = -2;	  // 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화

		
			_y = i - baseCharIg->getFrameHeight();// 올라간다
			_jumpCount = 0;
			break;
		}

		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false &&_isDash==false) // 파란색 픽셀충돌용 땅에 닿았고 떨어지는 상태라면
		{
			isCollide = true;		// 충돌했으면 얘를 ON
			_jumpPower = -2;		// 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화

			_y = i - baseCharIg->getFrameHeight();// 올라간다
			_jumpCount = 0;
			break;
		}
	}
	if (_bottomCol == false)
	{

		for (int i = _y + 15; i > _y - 4; i--)
		{
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if ((r == 255 && g == 0 && b == 0)) // 빨간색 픽셀충돌용 땅에 닿았다
			{
				_jumpPower = -2;
				_y = i + 5;

				break;
			}
		}
	}
	if (!isCollide) //충돌해있지 않다면
	{
		_y -= _jumpPower;			//중력적용
		_jumpPower -= _gravity;
		
		if (_jumpPower < -20)
		{
			_jumpPower = -20;
		}
		_body = RectMake(_x, _y, baseCharIg->getFrameWidth(), baseCharIg->getFrameHeight());
	}

	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
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
				_x = i - baseCharIg->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 40);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - baseCharIg->getFrameWidth();
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - baseCharIg->getFrameWidth();


			break;
		}
	}

	//왼쪽아래
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
				_x = i - baseCharIg->getFrameWidth();

			}

			break;
		}
	}
	//왼쪽중간
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 40);
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
	///////////////////////////////////////////////////////////////////////////
}

void Player::dash()
{
	
		_dashTimer++;
		
		_x += cosf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
		_y += -sinf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
		_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();


		image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
		image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");



		for (int i = _probeBottom - 20; i < _probeBottom + 5; i++)
		{
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
			{

				_y = i - baseCharIg->getFrameHeight();// 올라간다
				break;
			}

			
		}
		if (_dashTimer == 3)
		{
			EFFECTMANAGER->AddEffect(_x  , _y , "monsterSpawnEffect", 2);
		}
		if (_dashTimer == 5)
		{
			EFFECTMANAGER->AddEffect(_x  , _y , "monsterSpawnEffect", 2);
		}
		if (_dashTimer == 7)
		{
			EFFECTMANAGER->AddEffect(_x  , _y , "monsterSpawnEffect", 2);
		}
		if (_dashTimer >= 10)
		{
			_dashTimer = 0;
			_jumpPower = 0;
			_isDash = false;
			
		}
}
