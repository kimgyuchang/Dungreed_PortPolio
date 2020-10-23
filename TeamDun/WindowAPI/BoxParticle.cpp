#include "stdafx.h"
#include "BoxParticle.h"

HRESULT BoxParticle::init(float x, float y, float xSpeed, float ySpeed, image* img)
{
	_x = x;
	_y = y;
	_speedX = xSpeed;
	_speedY = ySpeed;
	_vImages.push_back(img);
	_vImageNames.push_back(img->getFileName());
	_useImage = 0;
	_frameX = 0;
	_frameY = 0;
	_frameTimer = 0;
	
	_type = OBJECTTYPE::OT_ETC;
	_liveTimer = 300;
	_gravity = 0.5f;
	_name = "Box Particle";
	_id = 152523;

	_body = RECT{ 0,0,0,0 };
	_isDead = false;
	_renderOrder = 1;

	return S_OK;
}

void BoxParticle::update()
{
	DropObjs::update();
	CheckLiveTime();
}

void BoxParticle::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
}

void BoxParticle::CheckLiveTime()
{
	_liveTimer--;
	if (_liveTimer < 0)
	{
		_isDead = true;
	}
}
