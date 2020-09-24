#include "stdafx.h"
#include "MapObject.h"
#include "MapTool.h"

HRESULT MapObject::init(int id, float x, float y, int page)
{
	
	_id = id;
	_x = x;
	_y = y;
	_initX = _x;
	_initY = _y;
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
		CAMERAMANAGER->stretchAlphaRender(hdc, _image, _x, _y,_mapTool->getZoomWidth()/48, _mapTool->getZoomHeight() / 48, _alpha );
	else 
		CAMERAMANAGER->frameStretchRender(hdc, _image, _x, _y, _frameX, _frameY, _mapTool->getZoomWidth() / 48, _mapTool->getZoomHeight() / 48);
	
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

void MapObject::SetZoomPosition()
{
	
	_x =_initX*( _mapTool->getZoomWidth() / 48);
	_y =_initY*( _mapTool->getZoomHeight() / 48);

	if (_image->getMaxFrameX() == 0)
	{
		_body = RectMake(_x, _y, _image->getWidth(), _image->getHeight());
	}
	else
	{
		_body = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
	
}
