#include "stdafx.h"
#include "MapObject.h"

HRESULT MapObject::init(int id, float x, float y, int page)
{
	_id = id;
	_x = x;
	_y = y;
	_page = page;
	
	_spawnTime = 0;
	_animationTimer = 0;
	_frameX = 0;
	_frameY = 0;

	_image = DATAMANAGER->GetObjectById(_id)->GetImage(0);
	if (_image->getMaxFrameX() == 0)
	{
		_body = RectMake(_x, _y, _image->getWidth(), _image->getHeight());
	}
	else
	{
		_body = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}

	return S_OK;
}

void MapObject::update()
{
	UpdateBody();
	Animation();
}

void MapObject::render(HDC hdc)
{
	if (_image->getMaxFrameX() == 0)
		CAMERAMANAGER->AlphaRender(hdc, _image, _x, _y, _alpha);
	else
		CAMERAMANAGER->FrameRender(hdc, _image, _x, _y, _frameX, _frameY);
	
	if (INPUT->GetKey('O'))
	{
		CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void MapObject::release()
{
}

void MapObject::UpdateBody()
{
	if (_image->getMaxFrameX() == 0)
	{
		_body = RectMake(_x, _y, _image->getWidth(), _image->getHeight());
	}
	else
	{
		_body = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

void MapObject::Animation()
{
	if (_image->getMaxFrameX() != 0)
	{
		_animationTimer++;

		if (_animationTimer >= 5)
		{
			_animationTimer = 0;
			_frameX++;

			if (_frameX > _image->getMaxFrameX())
			{
				_frameX = 0;
			}
		}
	}
}
