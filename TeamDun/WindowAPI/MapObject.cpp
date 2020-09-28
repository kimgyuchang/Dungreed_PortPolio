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
	UpdateBody();

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
		CAMERAMANAGER->StretchAlphaRender(hdc, _image, _x, _y,_mapTool->getZoomWidth()/48, _mapTool->getZoomHeight() / 48, _alpha );
	else 
		CAMERAMANAGER->FrameStretchRender(hdc, _image, _x, _y, _frameX, _frameY, _mapTool->getZoomWidth() / 48, _mapTool->getZoomHeight() / 48);
	
	if (INPUT->GetKey('O'))
	{
		CAMERAMANAGER->Rectangle(hdc, _body);
	}
}

void MapObject::release()
{
}

/// <summary>
/// 현재 위치를 기반으로 충돌체 위치를 업데이트한다.
/// </summary>
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

/// <summary>
/// 맵 오브젝트의 애니메이션을 실시한다.
/// </summary>
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

/// <summary>
/// 줌 비율에 따른 위치를 설정한다.
/// </summary>
void MapObject::SetZoomPosition()
{
	_x =_initX*( (_mapTool->getZoomWidth() + (2*_mapTool->getZoomWidth() / 48)) / 48);
	_y =_initY*( (_mapTool->getZoomHeight() + (2*_mapTool->getZoomHeight() / 48)) / 48);

	if (_image->getMaxFrameX() == 0)
	{
		_body = RectMake(_x, _y, _image->getWidth(), _image->getHeight());
	}
	else
	{
		_body = RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}
