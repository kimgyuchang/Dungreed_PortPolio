#include "stdafx.h"
#include "Coin.h"

HRESULT Coin::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	return S_OK;
}

void Coin::update()
{
	Object::update();
	
	Move();
	PixelCollision();
	CheckCollision();
}

void Coin::release()
{
	Object::release();
}

void Coin::render(HDC hdc)
{
	Object::render(hdc);
}

void Coin::Animation()
{
	Object::Animation();
}

void Coin::SetCoin(float x, float y, float speedX, float speedY)
{
	_x = x;
	_y = y;
	_speedX = speedX;
	_speedY = speedY;
	_gravity = 0.5f;
}

void Coin::Move()
{
	float _moveX = cos(PI / 4) * _speedX;
	float _moveY = -sin(PI / 4) * _speedY;
	_x += _moveX;
	_y += _moveY;

	_speedY -= _gravity;
}

void Coin::CheckCollision()
{
}

void Coin::PixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* coinImg = _vImages[_useImage];

	float _probeBottom = _y + coinImg->getFrameHeight();

	for (int i = _probeBottom - 5; i < _probeBottom + 5; i++)
	{
		COLORREF color =  GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + coinImg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 || (r == 0 && g == 0 && b ==255))
		{
			isCollide = true;
			_y = i - _vImages[_useImage]->getFrameHeight();
			_speedY = _speedY / 10 * 9;
			//_speedX = _speedX / 10 * 9;
			break;
		}
	}

	// ¿À¸¥ÂÊ
	for (int i = _x + coinImg->getFrameWidth() - 5; i < _x + coinImg->getFrameWidth(); i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, coinImg->getFrameHeight() / 2 + _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i - coinImg->getFrameWidth();
			break;
		}
	}

	// ¿ÞÂÊ
	for (int i = _x + 5; i > _x; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, coinImg->getFrameHeight() / 2 + _y);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i + 5;
			break;
		}
	}
}