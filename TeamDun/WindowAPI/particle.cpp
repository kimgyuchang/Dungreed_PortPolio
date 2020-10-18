#include "stdafx.h"
#include "particle.h"

void particle::init()
{
}

void particle::release()
{
}

void particle::update()
{
	_time--;

	// 알파 변경
	_alpha -= _alphaChanger;
	if (_alpha < 0) _alpha = 0;
	if (_alpha > 255) _alpha = 255;

	//스피드 변경
	_xSpeed += _speedChangerX;
	_ySpeed += _speedChangerY;

	// 스케일 변경
	_scale += _scaleChanger;

	// X Y 변경
	_x += cos(_angle) * _xSpeed;
	_y += -sin(_angle) * _ySpeed;
}

void particle::render(HDC hdc)
{
	float newX = _x - ((_scale - 1) * _image->getWidth());
	float newY = _y - ((_scale - 1) * _image->getHeight());
	CAMERAMANAGER->StretchAlphaRender(hdc, _image, newX, newY, _scale, _scale, _alpha);
}

void particle::initParticle(float x, float y, float speedChangerX, float speedChangerY, float xSpeed, float ySpeed, float angleChanger, float angle, float alphaChanger, float alpha, float scaleChanger, float scale, float time, string name)
{
	_x = x;
	_y = y;
	_xSpeed = xSpeed;
	_ySpeed = ySpeed;
	_angle = angle;
	_alpha = alpha;
	_scale = scale;
	_scaleChanger = scaleChanger;
	_speedChangerX = speedChangerX;
	_speedChangerY = speedChangerY;
	_angleChanger = angleChanger;
	_alphaChanger = alphaChanger;
	_time = time;

	_image = IMAGEMANAGER->findImage(name);
}
