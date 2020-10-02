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

    return S_OK;
}

void Object::update()
{
}

void Object::release()
{
}

void Object::render(HDC hdc)
{
    if (_vImages[_useImage]->getMaxFrameX() == 0) CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
    else CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Object::Animation()
{
}

void Object::CheckCollision()
{
}
