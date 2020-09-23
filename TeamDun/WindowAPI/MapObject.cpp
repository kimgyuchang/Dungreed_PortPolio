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
	return S_OK;
}

void MapObject::update()
{
}

void MapObject::render(HDC hdc)
{
	if (_image->getMaxFrameX() == 0)
		_image->alphaRender(hdc, _x, _y, _alpha);
	else
		_image->frameRender(hdc, _x, _y, _frameX, _frameY);
}

void MapObject::release()
{
}

void MapObject::Animation()
{
	
}
