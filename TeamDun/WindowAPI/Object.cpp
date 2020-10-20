#include "stdafx.h"
#include "Object.h"
#include "FieldMap.h"

HRESULT Object::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
    _id = id;
    _name = name;
    _type = type;
    
    for (int i = 0; i < imgNames.size(); i++)
    {
        if (imgNames[i] != ".")
        {
			_vImageNames.push_back(imgNames[i]);
            _vImages.push_back(IMAGEMANAGER->findImage(imgNames[i]));
        }
    }

    _x = 0;
    _y = 0;
    _spawnTime = 0;
    
    _frameX = 0;
    _frameY = 0;
    _useImage = 0;
	_frameTimer = 0;
    _body = RECT{ 0,0,0,0 };
    _isDead = false;
	_renderOrder = 1;
	_viewAlpha = 255;
    return S_OK;
}

void Object::update()
{
	Animation();
}

void Object::release()
{
}

void Object::render(HDC hdc)
{
	if (_vImages[_useImage]->getMaxFrameX() == 0 && _vImages[_useImage]->getMaxFrameY() == 0)
	{
		if (_viewAlpha != 255)
		{
			
			CAMERAMANAGER->AlphaRender(hdc, _vImages[_useImage], _x, _y,_viewAlpha);
		}
		else
		{
			CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
		}
	}
	else
	{
		if (_viewAlpha != 255)
		{
			
			CAMERAMANAGER->FrameAlphaRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY,_viewAlpha);
		}
		else
		{
			CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
		}
	}
}

void Object::Animation()
{
	_frameTimer++;
	_frameY = 0;

	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX > _vImages[_useImage]->getMaxFrameX())
		{
			_frameX = 0;  //¿©±â¶û
		}
	}
}

void Object::CheckCollision()
{

}

void Object::GetDamage()
{
	if (_hp <= 0)
	{
		SetIsDead(true);
	}
}

void Object::GetDamage(int damage)
{
	if (_hp <= 0)
	{
		SetIsDead(true);
	}
}
