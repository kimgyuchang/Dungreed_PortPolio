#include "stdafx.h"
#include "Effect.h"

HRESULT Effect::init(float x, float y, string imgName, int animSpeed, int frameX, int frameY, bool isLoop)
{
	_x = x;
	_y = y;
	_frameX = frameX;
	_frameY = frameY;
	_image = IMAGEMANAGER->findImage(imgName);
	_initAnimTimer = _animTimer = animSpeed;
	_isLoop = isLoop;
	_isDead = false;

	return S_OK;
}

void Effect::update()
{
	Animation();
}

void Effect::release()
{
}

void Effect::render(HDC hdc)
{
	if (_image->getMaxFrameX() == 0)
	{
		CAMERAMANAGER->Render(hdc, _image, _x, _y);
	}

	else
	{
		CAMERAMANAGER->FrameRender(hdc, _image, _x, _y, _frameX, _frameY);
	}
}

void Effect::Animation()
{
	_animTimer--;

	if (_animTimer < 0)
	{
		_frameX++;
		_animTimer = _initAnimTimer;
		if (_frameX >= _image->getMaxFrameX())
		{
			if (_isLoop) _frameX = 0;
			else DeleteEffect();
		}
	}
}

void Effect::DeleteEffect()
{
	_isDead = true;
}
