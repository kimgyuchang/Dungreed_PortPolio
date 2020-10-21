#include "stdafx.h"
#include "Effect.h"

HRESULT Effect::init(float x, float y, string imgName, int animSpeed, int frameX, int frameY, bool isLoop, int alpha, float angle, float scaleX, float scaleY, bool isAlpha, bool useCamera, bool isFirstViewing)
{
	_x = x;
	_y = y;
	_frameX = frameX;
	_frameY = frameY;
	_image = IMAGEMANAGER->findImage(imgName);
	_initAnimTimer = _animTimer = animSpeed;
	_body = RECT{0, 0, 0, 0};
	_isLoop = isLoop;
	_isDead = false;
	_alpha = alpha;
	_angle = angle;
	_scaleX = scaleX;
	_scaleY = scaleY;
	_isAlpha = isAlpha;
	_useCamera = useCamera;
	_isFirstViewing = isFirstViewing;
	return S_OK;
}

void Effect::update()
{
	Animation();
	AlphaDeleteEffect();
}

void Effect::release()
{
}

void Effect::render(HDC hdc)
{

	if (_image->getMaxFrameX() == 0)
	{
		if (_useCamera)
		{
			if (_scaleX != 1 || _scaleY != 1) _image->stretchAlphaRender(hdc, _x, _y, _scaleX, _scaleY, _alpha, _angle);
			else _image->alphaRender(hdc, _x, _y, _alpha, _angle);
		}
		else
		{
			if (_scaleX != 1 || _scaleY != 1) CAMERAMANAGER->StretchAlphaRender(hdc, _image, _x, _y, _scaleX, _scaleY, _alpha, _angle);
			else CAMERAMANAGER->AlphaRender(hdc, _image, _x, _y, _alpha, _angle);
		}
	}

	else
	{
		if (_useCamera)
		{
			if (_scaleX != 1 || _scaleY != 1) _image->frameStretchAlphaRender(hdc, _x, _y,_frameX,_frameY, _scaleX, _scaleY, _alpha, _angle);
			else _image->frameAlphaRender(hdc, _x, _y, _frameX, _frameY, _alpha, _angle);
		}
		else
		{
			if (_scaleX != 1 || _scaleY != 1) CAMERAMANAGER->FrameStretchAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _scaleX, _scaleY, _alpha, _angle);
			else CAMERAMANAGER->FrameAlphaRender(hdc, _image, _x, _y, _frameX, _frameY, _alpha, _angle);
		}
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

void Effect::AlphaDeleteEffect()
{
	if (_isAlpha)
	{
		_alpha -= 3;

		if (_alpha < 0)
		{
			DeleteEffect();
		}
	}
}
