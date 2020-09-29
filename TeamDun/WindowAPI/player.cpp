#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{

	_player = RectMake(100, WINSIZEX / 2, 50, 50);
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1

	_useImage = 0;
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_frameX = 0;
	_frameY = 0;

	return S_OK;
	
}

void Player::update()
{
	if (INPUT->GetKey('A'))
	{
		_isLeft = true;
		_state = PS_MOVE;
		_x -= 5;
		//_player= RectMake(100, WINSIZEX / 2, 50, 50);
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
	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
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
		IMAGEMANAGER->findImage("baseCharIdle")->frameRender(hdc, _x, _y,_frameX,_frameY);
		break;
	case PS_JUMP:
		break;
	case PS_MOVE:
		IMAGEMANAGER->findImage("baseCharRun")->frameRender(hdc, _x, _y,_frameX,_frameY);
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
				_frameX = _vImages[_useImage]->getMaxFrameX();  //¿©±â¶û
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

