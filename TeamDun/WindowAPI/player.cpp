#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{

	_player = RectMake(100, WINSIZEX / 2, 50, 50);
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun"));
	_useImage = 1;
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
	}
	if (INPUT->GetKey('D'))
	{

	}
	Animation();
}

void Player::release()
{
}

void Player::render(HDC hdc)
{
	CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Player::Animation()
{
	switch (_state)
	{
	case PS_IDLE:
		break;
	case PS_JUMP:
		break;
	case PS_MOVE:
		if (_isLeft)
		{
			_frameTimer++;
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;
			}
			
		}
		break;
	case PS_DIE:
		break;
	default:
		break;
	}
	_frameTimer++;

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

