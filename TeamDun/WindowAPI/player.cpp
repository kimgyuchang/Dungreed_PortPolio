#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{

	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1


	_x = 100;
	_y = WINSIZEY/2;
	_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	
	_useImage = 0;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	
	_frameX = 0;
	_frameY = 0;
	_gravity = 0.1f;
	_jumpPower = 3.0f;
	return S_OK;
	
}

void Player::update()
{
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();

	if (INPUT->GetKey('A'))
	{
		_isLeft = true;
		_state = PS_MOVE;
		_x -= 5;
		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('A'))
	{
	
		_state = PS_IDLE;
	}
	if (INPUT->GetKey('D'))
	{
		_isLeft = false;
		_state = PS_MOVE;
		_x += 5;
		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}
	


	//////////////////////////// 픽셀충돌 //////////////////////////////

	bool isCollide = false; // 충돌 했는지 여부

	for (int i = _probeBottom - 15; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _x+ IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth()/2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255) || (r == 255 && g == 0 && b == 0)) // 땅에 닿았다
		{
			isCollide = true; // 충돌했으면 얘를 ON
			_y = i - IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();// 올라간다
			
			break;
		}
	}
	if (!isCollide)
	{
		
		_y += 5; // 충돌을 안했으면, 땅에 닿지 않았다 생각해서 중력적용 그래비티값과 점프파워 값으로 수정해야합니다`
		_player = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}

	///////////////////////////////////////////////////////////////////////////
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
		_frameTimer++;
		_frameY = 0;
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

void Player::Move()
{
}

